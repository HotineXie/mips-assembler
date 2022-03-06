#include <fstream>
#include <string>
#include <vector>
#include <map>

class Scanner {
 public:
  std::map<std::string, int> labelTable;
  std::vector<std::vector<std::string>> pureCodes;
  void read_line(std::string current);

 private:
  bool is_token_empty(char currentChar);
  bool is_token_end(char currentChar);
  bool annotation_start(char currentChar);
};
