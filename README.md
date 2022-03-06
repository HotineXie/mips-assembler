# mips-assembler

run program:
1. create and cd to a empty folder build
2. run cmake ..
3. run make
4. run ./mips-assembler [input assembler file path] [output file path] [expected bin file path]
e.g.
```
mkdir build
cd build
cmake ..
make
./mips-assembler ../test/testfile.asm ../test/out ../test/expectedoutput.txt
```