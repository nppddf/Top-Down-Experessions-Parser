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
 `1 + 2 * 3`  
 Result: 7  
 `(15 * 3) + 20`  
 Result: 65  
 `(20 + 8 * (2 + 3)) + 1`  
 Result: 61  

# Project tree
├── CMakeLists.txt  
├── LICENSE  
├── README.md  
├── build  
├── inc  
│   ├── ast.h  
│   ├── lexer.h  
│   ├── parser.h  
│   └── utils.h  
└── src  
    ├── ast.c  
    ├── lexer.c  
    ├── main.c  
    ├── parser.c  
    └── utils.c  

4 directories, 12 files  


# Build and Run
Requires GCC or Clang, CMake

Build: `build/cmake ..`  
Run: `./parser`