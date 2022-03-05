#include "scanner.h"
#include "parser.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

int main(int agrc, char** agrv) {
  std::string infilePath = agrv[1];
  std::string outfilePath = agrv[2];
  std::ifstream asmCode(infilePath);
  std::ofstream binCode(outfilePath, std::ios::trunc);

  std::string current;

  while (getline(asmCode, current)) {
    read_line(current);
  }

  for (int i=0;i<pureCodes.size();i++) {
    for (int j=0;j<pureCodes[i].size();j++) {
      std::cout << pureCodes[i][j] << " | ";
    }
    std::cout << std::endl;
  }
  std::cout << labelStorage["fibonacciExit"] << std::endl;

  return 0;
}