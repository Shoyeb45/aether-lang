#!/usr/bin/env bash
#
# Install script for Aether (https://github.com/Shoyeb45/aether-lang)
# Detects OS (Linux/macOS), downloads the matching release asset,
# installs the binary, and adds it to PATH.
#
# Usage:
#   curl -fsSL https://raw.githubusercontent.com/Shoyeb45/aether-lang/main/scripts/install.sh | bash
#   curl -fsSL https://raw.githubusercontent.com/Shoyeb45/aether-lang/main/scripts/install.sh | bash -s -- v0.1.0

set -euo pipefail

REPO="Shoyeb45/aether-lang"
INSTALL_DIR="$HOME/.aether/bin"
BINARY_NAME="aether"
VERSION="${1:-latest}"

info()  { printf '\033[1;34m[info]\033[0m %s\n' "$1"; }
error() { printf '\033[1;31m[error]\033[0m %s\n' "$1" >&2; exit 1; }

# --- 1. Detect OS ---------------------------------------------------------
OS_RAW="$(uname -s)"
case "$OS_RAW" in
  Linux*)  PLATFORM="linux" ;;
  Darwin*) PLATFORM="macos" ;;
  *) error "Unsupported OS: $OS_RAW. This script supports Linux and macOS only." ;;
esac
info "Detected platform: $PLATFORM"

# --- 2. Resolve version ----------------------------------------------------
if [ "$VERSION" = "latest" ]; then
  info "Fetching latest release info..."
  VERSION="$(curl -fsSL "https://api.github.com/repos/${REPO}/releases/latest" \
    | grep -m1 '"tag_name"' | sed -E 's/.*"tag_name": *"([^"]+)".*/\1/')"
  [ -n "$VERSION" ] || error "Could not determine latest release version."
fi
info "Installing version: $VERSION"

# --- 3. Build download URL -------------------------------------------------
ASSET="aether-${VERSION}-${PLATFORM}.tar.gz"
URL="https://github.com/${REPO}/releases/download/${VERSION}/${ASSET}"

TMP_DIR="$(mktemp -d)"
trap 'rm -rf "$TMP_DIR"' EXIT

info "Downloading ${ASSET}..."
if ! curl -fsSL "$URL" -o "$TMP_DIR/$ASSET"; then
  error "Failed to download $URL
Check that a release named '$VERSION' exists with an asset '$ASSET' at:
https://github.com/${REPO}/releases"
fi

# --- 4. Extract & install ---------------------------------------------------
info "Extracting..."
tar -xzf "$TMP_DIR/$ASSET" -C "$TMP_DIR"

if [ ! -f "$TMP_DIR/$BINARY_NAME" ]; then
  error "Binary '$BINARY_NAME' not found inside the downloaded archive."
fi

mkdir -p "$INSTALL_DIR"
cp "$TMP_DIR/$BINARY_NAME" "$INSTALL_DIR/$BINARY_NAME"
chmod +x "$INSTALL_DIR/$BINARY_NAME"
info "Installed binary to $INSTALL_DIR/$BINARY_NAME"

# --- 5. Add to PATH ----------------------------------------------------------
add_path_line() {
  local rc_file="$1"
  local line="export PATH=\"\$PATH:$INSTALL_DIR\""
  if [ -f "$rc_file" ] && grep -qF "$INSTALL_DIR" "$rc_file" 2>/dev/null; then
    info "PATH entry already present in $rc_file"
  else
    echo "" >> "$rc_file"
    echo "# Added by aether install script" >> "$rc_file"
    echo "$line" >> "$rc_file"
    info "Added $INSTALL_DIR to PATH in $rc_file"
  fi
}

CURRENT_SHELL="$(basename "${SHELL:-bash}")"
case "$CURRENT_SHELL" in
  zsh)  add_path_line "$HOME/.zshrc" ;;
  bash)
    if [ "$PLATFORM" = "macos" ]; then
      add_path_line "$HOME/.bash_profile"
    else
      add_path_line "$HOME/.bashrc"
    fi
    ;;
  fish)
    mkdir -p "$HOME/.config/fish"
    FISH_CONF="$HOME/.config/fish/config.fish"
    if [ -f "$FISH_CONF" ] && grep -qF "$INSTALL_DIR" "$FISH_CONF" 2>/dev/null; then
      info "PATH entry already present in $FISH_CONF"
    else
      echo "" >> "$FISH_CONF"
      echo "# Added by aether install script" >> "$FISH_CONF"
      echo "set -gx PATH \$PATH $INSTALL_DIR" >> "$FISH_CONF"
      info "Added $INSTALL_DIR to PATH in $FISH_CONF"
    fi
    ;;
  *)
    add_path_line "$HOME/.profile"
    ;;
esac

info "Done! Restart your terminal (or run: source ~/.$(basename "$CURRENT_SHELL")rc) then try: aether version"