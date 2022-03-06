#include "scanner.h"
#include "parser.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

int main(int argc, char** argv) {
  std::string infilePath = argv[1];
  std::string outfilePath = argv[2];
  std::string basefilePath = argv[3];

  std::ifstream asmCode(infilePath);
  std::ifstream baseCode(basefilePath);
  std::ofstream binCode(outfilePath, std::ios::trunc);
  std::string currentLine;
  std::string expectedResult;
  std::string tmp;

  Scanner MipsScanner;
  Parser MipsParser;

  while (getline(asmCode, currentLine)) {
    MipsScanner.read_line(currentLine);
  }
  MipsParser.labelTable = MipsScanner.labelTable;
  MipsParser.pureCodes = MipsScanner.pureCodes;
  std::string result = MipsParser.parse_pure_code();
  binCode << result;

  while (getline(baseCode, tmp)) {
    expectedResult = expectedResult + tmp + '\n';
  }
  if (expectedResult != result) {
    std::cout << "YOU DID SOMETHING WRONG :(" << std::endl;
  }
  else {
    std::cout << "ALL PASSED! CONGRATS :)" << std::endl;
  }

  return 0;
}