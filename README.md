# Recursive Descent Parser in C
Parser calculates arithmetic expressions and includes:
    - Lexer (Tokenizer)
    - Recursive syntax analizator
    - Left recursion eliminating
    - Expressions calculator
    - Support for the characters +, -, ()


# Grammar
## Rules
Expr  => Term Expr'
Expr' => + Term Expr' | eps
Term  => Fact Term'
Term' => * Fact Term' | eps
Fact  => number | '(' Expr ')'

## Examples 
 1 + 2 * 3
 (15 * 3) + 20
 (20 + 8 * (2 + 3)) + 1

# Project tree
.
├── CMakeLists.txt
├── LICENSE
├── README.md
├── build
├── inc
│   ├── lexer.h
│   ├── logger.h
│   ├── parser.h
│   ├── parser_structures.h
│   └── utils.h
└── src
    ├── lexer.c
    ├── logger.c
    ├── main.c
    └── parser.c

4 directories, 12 files

# Build and Run
Requires GCC or Clang, CMake

Build: `build/cmake ..`
Run: `./parser`