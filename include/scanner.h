#include <fstream>
#include <string>
#include <vector>
#include <map>

extern std::map<std::string, int> labelStorage;
extern std::vector<std::vector<std::string>> pureCodes;

void read_line(std::string current);
bool is_empty(char currentChar);
bool is_token_end(char currentChar);
bool annotation_start(char currentChar);
