# MiniC: x86_64 Systems Compiler

A lightweight, multi-stage compiler written in C that translates a subset of C-style syntax into native x86_64 Assembly. Developed to explore the intersection of language design, resource management, and low-level hardware mapping.

---

## 🛠 Technical Overview
* **Language:** C (C11)
* **Architecture:** x86_64 (Linux ABI)
* **Build System:** Makefile
* **Target:** Intel Syntax Assembly

---

## 🏗 Compiler Pipeline
The project implements a classic four-stage compilation toolchain:

1.  **Lexical Analysis:** A hand-written scanner that tokenizes source input using a transition-based approach, handling identifiers, literals, and keywords.
2.  **Recursive Descent Parsing:** A predictive parser that enforces operator precedence and validates program syntax.
3.  **Abstract Syntax Tree (AST):** A tree-based intermediate representation (IR) used to model the hierarchical structure of the logic.
4.  **Code Generation:** A stack-based backend that maps AST nodes directly to x86_64 instructions (Push/Pop/Mov/Arithmetic).

---

## 🚀 Quick Start
```bash
# Build the compiler
make

# Compile a sample script
./minicc test.c > output.s

# Launch interactive REPL mode
./minicc