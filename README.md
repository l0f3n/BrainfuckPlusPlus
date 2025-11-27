# Brainfuck++

A Brainfuck interpreter implemented in C++ using operator overloading.

## Overview

Each Brainfuck command is represented by a C++ operator:

| Brainfuck | C++ Operator | Description |
|-----------|--------------|-------------|
| `>` | `++` | Move pointer right |
| `<` | `--` | Move pointer left |
| `+` | `+` | Increment value |
| `-` | `-` | Decrement value |
| `.` | `!` | Output value |
| `,` | `*` | Input value |
| `[` | `&` | Loop start |
| `]` | `~` | Loop end |

## Example

A simple Brainfuck program that counts down from 3 to 1:

```brainfuck
+++[.-]
```

The equivalent C++ code looks like:

```cpp
#include "brainfuck.hpp"

int main() {
    Brainfuck bf;
    + + + & ! - ~ bf;
    return 0;
}
```

## Usage

```bash
make
./examples/hello_world
```
