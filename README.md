# The Aether Programming Language

**Aether** is a dynamically-typed, tree-walking interpreted programming language, written from scratch in modern C++23.

It supports closures, first-class functions, and full class-based OOP with inheritance — built as a from-the-ground-up exploration of how interpreters work, from scanning raw source text to executing an AST.


<p align="center">
  <img src="docs/assets/aether-demo.gif" alt="Aether classes demo" width="700"/>
  <i>Demo</i>
</p>

---

## Features

- Primitive types: `number`, `boolean`, `string`, `nil`
- Arithmetic (`+ - * /`), comparison (`== != < > <= >=`), and logical (`AND`, `OR`) operators
- Unary negation (`-`) and logical not (`!`)
- Lexical scoping — global, local, and block scope
- Control flow: `if` / `else` / `else if`, `while`, `for`
- Functions: custom, higher-order, and native (`clock()`)
- Closures
- Classes: instantiation, methods, constructors, inheritance, method overriding, `super`, `this`
- Clean, readable syntax error messages

See the [full language guide](docs/LANGUAGE_GUIDE.md) for syntax and examples.

---

## Installation

### Option 1 — Prebuilt binaries (recommended)

Grab the latest release for your OS from the [Releases page](https://github.com/Shoyeb45/aether-lang/releases), or run the install script:

**Linux / macOS**
```bash
curl -fsSL https://raw.githubusercontent.com/Shoyeb45/aether-lang/main/install.sh | bash
```

**Windows (PowerShell)**
```powershell
iwr https://raw.githubusercontent.com/Shoyeb45/aether-lang/main/install.ps1 -useb | iex
```

Verify it worked:
```bash
aether version
```

---

## Quick Start

Run a script:
```bash
aether run path/to/script.ae
```

A quick taste:
```
fun greet(name) {
  print "Hello, " + name + "!";
}

greet("world");

class Animal {
  init(name) {
    this.name = name;
  }

  speak() {
    print this.name + " makes a sound.";
  }
}

class Dog < Animal {
  speak() {
    print this.name + " barks.";
  }
}

var d = Dog("Rex");
d.speak();
```

More examples live in [`examples/`](examples/).

---

## Documentation

| Doc | Description |
|---|---|
| [Language Guide](docs/LANGUAGE_GUIDE.md) | Syntax, statements, expressions, and semantics |
| [Architecture](docs/ARCHITECTURE.md) | How the interpreter is structured internally |
| [Roadmap](docs/ROADMAP.md) | What's done and what's coming |

---

## Roadmap

See [docs/ROADMAP.md](docs/ROADMAP.md) for the full, up-to-date list.

---

## License

This project is licensed under the terms of the [LICENSE](./LICENSE) file in this repository.
