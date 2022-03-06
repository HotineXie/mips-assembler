cmake_minimum_required (VERSION 3.16)
project (mips-assembler)

include_directories(include)
add_executable(mips-assembler src/main.cc src/scanner.cc src src/parser.cc)
