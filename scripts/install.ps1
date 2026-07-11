<#
.SYNOPSIS
  Installs Aether (https://github.com/Shoyeb45/aether-lang) on Windows.

.USAGE
  iwr https://raw.githubusercontent.com/Shoyeb45/aether-lang/main/install.ps1 -useb | iex
  # or, for a specific version:
  & ([scriptblock]::Create((iwr https://raw.githubusercontent.com/Shoyeb45/aether-lang/main/install.ps1 -useb).Content)) -Version v0.1.0
#>

param(
    [string]$Version = "latest"
)

$ErrorActionPreference = "Stop"

$Repo        = "Shoyeb45/aether-lang"
$BinaryName  = "aether.exe"
$InstallDir  = "$env:LOCALAPPDATA\Aether\bin"

function Write-Info($msg)  { Write-Host "[info] $msg" -ForegroundColor Cyan }
function Write-Err($msg)   { Write-Host "[error] $msg" -ForegroundColor Red; exit 1 }

# --- 1. Resolve version -----------------------------------------------------
if ($Version -eq "latest") {
    Write-Info "Fetching latest release info..."
    try {
        $release = Invoke-RestMethod -Uri "https://api.github.com/repos/$Repo/releases/latest" -Headers @{ "User-Agent" = "aether-installer" }
        $Version = $release.tag_name
    } catch {
        Write-Err "Could not determine latest release version: $_"
    }
}
Write-Info "Installing version: $Version"

# --- 2. Build download URL --------------------------------------------------
$Asset = "aether-$Version-windows.zip"
$Url   = "https://github.com/$Repo/releases/download/$Version/$Asset"

$TmpDir = Join-Path $env:TEMP ([System.Guid]::NewGuid().ToString())
New-Item -ItemType Directory -Path $TmpDir | Out-Null

$ZipPath = Join-Path $TmpDir $Asset

Write-Info "Downloading $Asset..."
try {
    Invoke-WebRequest -Uri $Url -OutFile $ZipPath -UseBasicParsing
} catch {
    Remove-Item -Recurse -Force $TmpDir -ErrorAction SilentlyContinue
    Write-Err "Failed to download $Url`nCheck that a release '$Version' exists with asset '$Asset' at:`nhttps://github.com/$Repo/releases"
}

# --- 3. Extract --------------------------------------------------------------
Write-Info "Extracting..."
Expand-Archive -Path $ZipPath -DestinationPath $TmpDir -Force

$ExtractedBinary = Get-ChildItem -Path $TmpDir -Recurse -Filter $BinaryName | Select-Object -First 1
if (-not $ExtractedBinary) {
    Remove-Item -Recurse -Force $TmpDir -ErrorAction SilentlyContinue
    Write-Err "Binary '$BinaryName' not found inside the downloaded archive."
}

# --- 4. Install ----------------------------------------------------------------
New-Item -ItemType Directory -Path $InstallDir -Force | Out-Null
Copy-Item -Path $ExtractedBinary.FullName -Destination (Join-Path $InstallDir $BinaryName) -Force
Write-Info "Installed binary to $InstallDir\$BinaryName"

Remove-Item -Recurse -Force $TmpDir -ErrorAction SilentlyContinue

# --- 5. Add to PATH (User scope, persistent) -----------------------------------
$CurrentUserPath = [Environment]::GetEnvironmentVariable("Path", "User")
if ($CurrentUserPath -notlike "*$InstallDir*") {
    $NewPath = if ([string]::IsNullOrEmpty($CurrentUserPath)) { $InstallDir } else { "$CurrentUserPath;$InstallDir" }
    [Environment]::SetEnvironmentVariable("Path", $NewPath, "User")
    Write-Info "Added $InstallDir to your User PATH."
} else {
    Write-Info "PATH already contains $InstallDir"
}

# Make it usable in the *current* session too, without needing a new terminal
if ($env:Path -notlike "*$InstallDir*") {
    $env:Path = "$env:Path;$InstallDir"
}

Write-Info "Done! Open a new terminal (or use this one) and try: aether --version"