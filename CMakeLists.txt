cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 99)
project(Top-Down-Experessions-Parser VERSION 1.0.0 LANGUAGES C)

set(SRC_FILES
    src/main.c
    src/parser.c
    src/lexer.c
    src/ast.c)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE inc)

target_compile_options(${PROJECT_NAME} PRIVATE -O2 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wpointer-arith -Wtype-limits -Wempty-body -Wno-logical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -Wno-unused-result)

target_link_libraries(${PROJECT_NAME})