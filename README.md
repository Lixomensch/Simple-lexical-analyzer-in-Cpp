# Simple Compiler in C++

## Overview

This project implements a Simple Compiler in C++ for a fictional programming language. The analyzer reads source code, identifies tokens, and classifies them according to predefined rules.

## Features

- Identifies keywords, identifiers, operators, punctuation, integers, floats, and strings.
- Ignores whitespace and comments.
- Processes multi-character operators (`!=`, `<=`, `>=`).
- Reads input from a file.

## Installation

Ensure you have `g++` installed and run the following command:

```sh
make
```

## Usage

Run the analyzer by providing a source code file:

```sh
./lexer tests/test1.txt
```

## Cleanup

To remove compiled files, run:

```sh
make clean
```

## License

This project is open-source and free to use under the MIT License.
