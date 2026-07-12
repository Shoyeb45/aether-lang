# Aether Language Guide

This guide covers Aether's syntax and semantics as of **v0.1.0**. It assumes no prior knowledge of the language.

## Table of Contents
- [Basics](#basics)
- [Data Types](#data-types)
- [Variables](#variables)
- [Operators](#operators)
- [Comments](#comments)
- [Control Flow](#control-flow)
- [Loops](#loops)
- [Functions](#functions)
- [Closures](#closures)
- [Classes](#classes)
- [Scoping Rules](#scoping-rules)
- [Error Messages](#error-messages)

---

## Basics

Every statement ends with a semicolon `;`. Blocks are delimited with `{ }`.

```
print "Hello, Aether!";
```

Run a file:
```bash
aether run hello.ae
```

---

## Data Types

Aether has four primitive types:

| Type | Examples |
|---|---|
| `number` | `1`, `3.14`, `-7` |
| `string` | `"hello"`, `"multi word"` |
| `boolean` | `true`, `false` |
| `nil` | `nil` (absence of a value) |

```
var age = 25;
var pi = 3.14159;
var name = "Aether";
var isReady = true;
var nothing = nil;
```

---

## Variables

Declared with `var`. Uninitialized variables default to `nil`.

```
var x = 10;
var y;        // y is nil
y = 5;        // assignment
```

---

## Operators

### Arithmetic
```
+   -   *   /
```
```
print 3 + 4;   // 7
print 10 / 3;  // 3.333...
```

### Comparison
```
==  !=  <  >  <=  >=
```
```
print 5 == 5;   // true
print 5 != 3;   // true
```

### Logical
```
and     or
```
```
print true AND false;  // false
print true OR false;   // true
```

### Unary
```
-x    // arithmetic negation
!x    // logical not
```

---

## Comments

```
// this is a single-line comment
```

---

## Control Flow

```
// with or without parentheses, both works
if age >= 18 {
  print "adult";
} else if (age >= 13) {
  print "teen";
} else {
  print "child";
}

```

---

## Loops

### `while`
```
var i = 0;
while (i < 5) {
  print i;
  i = i + 1;
}
```

### `for`
```
for (var i = 0; i < 5; i = i + 1) {
  print i;
}
```

---

## Functions

Declared with `fun`. Functions are first-class values — they can be passed around, returned, and stored in variables.

```
fun add(a, b) {
  return a + b;
}

print add(2, 3); // 5
print add;       // <fn add>
```

### Higher-order functions
```
fun applyTwice(fn, x) {
  return fn(fn(x));
}

fun increment(n) {
  return n + 1;
}

print applyTwice(increment, 5); // 7
```

### Native functions
Aether ships with built-in native functions, including:
```
print clock(); // current time in milliseconds, useful for benchmarking
```

---

## Closures

Functions capture the environment they were defined in.

```
fun makeCounter() {
  var count = 0;
  fun counter() {
    count = count + 1;
    return count;
  }
  return counter;
}

var counter = makeCounter();
print counter(); // 1
print counter(); // 2
print counter(); // 3
```

---

## Classes

Classes are declared with `class`, instantiated by calling the class name, and use `this` to reference the current instance.

```
class Animal {
  init(name) {
    this.name = name;
  }

  speak() {
    print this.name + " makes a sound.";
  }
}

var a = Animal("Generic Animal");
a.speak(); // Generic Animal makes a sound.
```

### Inheritance

Use `<` to inherit from a parent class. Override methods by redefining them; use `super` to call the parent's implementation.

```
class Dog < Animal {
  speak() {
    super.speak();
    print this.name + " barks.";
  }
}

var d = Dog("Rex");
d.speak();
// Rex makes a sound.
// Rex barks.
```

---

## Scoping Rules

Aether uses **lexical (static) scoping** with three levels:

- **Global scope** — top-level declarations, visible everywhere
- **Local scope** — variables declared inside a function
- **Block scope** — variables declared inside `{ }` (including `if`/`while`/`for` bodies) are only visible within that block

```
var x = "global";

{
  var x = "block";
  print x; // block
}

print x; // global
```

---

## Error Messages

Aether reports syntax and runtime errors with the line number and a description of what went wrong, e.g.:

```
hello.ae:1:7: Error Expected ;
    1 | print "Hi"
              ^
```

---

More runnable examples are in [`examples/`](../examples/).