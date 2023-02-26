cmake_minimum_required(VERSION 3.23)

project(evaluator)

set(SOURCE_FILES
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/expression.cpp
    src/token.cpp
)

add_executable(main ${SOURCE_FILES})

set_target_properties(main PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)