#include "scanner.h"
#include <iostream>

std::map<std::string, int> labelStorage;
std::vector<std::vector<std::string>> pureCodes;
bool start_text = false;

void read_line(std::string current) {
  std::vector<std::string> codeInLine;
  std::string token = "";
  for (int i=0;i<current.size();i++) {
    if (token == "") {
      if (is_empty(current[i])) {
        continue;
      }
      else if (annotation_start(current[i])) {
        break;
      }
      else {
        token = token + current[i];
        if (i == current.size()-1) {
          codeInLine.push_back(token);
        }
      }
    } // have NOT start to write to token

    else {
      if (current[i] == ':') {
        labelStorage[token] = pureCodes.size();
        token = "";
        continue;
      }
      if (annotation_start(current[i])) {
        break;
      }
      else if (is_token_end(current[i])) {
        codeInLine.push_back(token);
        token = "";
      }
      else {
        token = token + current[i];
      }
      
      if (i == current.size()-1) {
          codeInLine.push_back(token);
      }
    } // start to write in token
  } // end loop for reading code line
  if (!codeInLine.empty() && start_text) {
    pureCodes.push_back(codeInLine);
  }
  if (!start_text) {
    if (!codeInLine.empty()) {
      if (codeInLine[0] == ".text") {
        start_text = true;
      }
    }
  }

}

bool is_empty(char currentChar) {
  if (currentChar == ' ' || currentChar == '\t') {
    return true;
  }
  return false;
}

bool is_token_end(char currentChar) {
  if (is_empty(currentChar) || currentChar == '\t' || currentChar == ',' || currentChar == '\0') {
    return true;
  }
  return false;
}

bool annotation_start(char currentChar) {
  if (currentChar == '#') {
    return true;
  }
  return false;
}
