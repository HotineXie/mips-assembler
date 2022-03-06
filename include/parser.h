#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <bitset>
#include <regex>

class Parser {
 public:
  std::map<std::string, int> labelTable;
  std::vector<std::vector<std::string>> pureCodes;
  std::string parse_pure_code();
 private:
  std::map<std::string, int>regMap = {
    {"$zero", 0}, {"$at", 1}, {"$v0", 2},{"$v1", 3},
    {"$a0", 4}, {"$a1", 5}, {"$a2", 6}, {"$a3", 7},
    {"$t0", 8}, {"$t1", 9}, {"$t2", 10}, {"$t3", 11},
    {"$t4", 12}, {"$t5", 13}, {"$t6", 14}, {"$t7", 15},
    {"$s0", 16}, {"$s1", 17}, {"$s2", 18}, {"$s3", 19},
    {"$s4", 20}, {"$s5", 21}, {"$s6", 22}, {"$s7", 23},
    {"$t8", 24}, {"$t9", 25}, {"$k0", 26}, {"$k1", 27},
    {"$gp", 28}, {"$sp", 29}, {"$fp", 30}, {"$ra", 31}
  };
  std::string trans_reg_int_to_bin(int regNum);
  std::string trans_sa_to_bin(std::string sa);
  std::string trans_imm_to_bin(int imm);
  std::string trans_addr_to_long_bin(int addr);
  std::string get_imm_in_immrs(std::string immrs);
  std::string get_rs_in_immrs(std::string immrs);
};
