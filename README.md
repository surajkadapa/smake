# smake

**smake** is a minimal, dependency-aware C++ build tool designed to automate compilation and linking in multi-file projects. It replicates the core behavior of traditional tools like `make`—parsing a custom `smakefile`, resolving dependencies, and rebuilding only when necessary—while remaining lightweight, readable, and educational.

---

## Key Features

- Dependency tracking via timestamp comparison.
- Topological sorting of build targets with cycle detection.
- Custom `smakefile` syntax similar to GNU Make.
- Executes shell commands specified per target.
- Written entirely in C++ (no external libraries).
- Clear separation of parsing, graph resolution, and execution phases.

---

## smakefile Format

A `smakefile` defines rules in the format:

```make
target: dep1 dep2
    build command

Example:

myapp: main.o util.o
    g++ main.o util.o -o myapp

main.o: main.cpp
    g++ -c main.cpp -o main.o

util.o: util.cpp
    g++ -c util.cpp -o util.o
```
Commands must be indented by 4 spaces.

## Usage
Write a smakefile in your project root.

Build using:

`./smake <target>`

Example:
    `./smake myapp`

Only targets that are missing or out-of-date will be rebuilt.

## Internals

- `parser.cpp`: Parses the smakefile into a dependency graph.

- `graph.cpp`: Performs DFS-based topological sort and cycle detection.

- `executor.cpp`: Handles timestamp checks and command execution.

- `main.cpp`: Entry point; validates input and invokes build pipeline.

## Build & Run

`g++ -std=c++17 -o smake src/main.cpp src/parser.cpp src/graph.cpp src/executor.cpp` \
`./smake <target>`

## Design Goals

This project was built from scratch to explore:

- Custom build system design.

- Graph algorithms in real-world tooling.

- File system interaction (stat), command execution (system()), and timestamp-based rebuild logic.

- Fine-grained control over C++ compilation behavior.

