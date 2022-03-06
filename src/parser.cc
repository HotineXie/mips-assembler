#include "parser.h"

extern std::map<std::string, int> labelStorage;
extern std::vector<std::vector<std::string>> pureCodes;

std::string Parser::trans_reg_int_to_bin(int regNum) {
  std::bitset<5> bin(regNum);
  return bin.to_string();
}

std::string Parser::trans_sa_to_bin(std::string sa) {
  std::bitset<5> bin(std::stoi(sa));
  return bin.to_string();
}

std::string Parser::trans_imm_to_bin(int imm) {
  std::bitset<16> bin(imm);
  return bin.to_string();
}

std::string Parser::trans_addr_to_long_bin(int addr) {
  std::bitset<26> bin(addr);
  return bin.to_string();
}

std::string Parser::get_imm_in_immrs(std::string immrs) {
  std::string result;
  for (int i=0;i<immrs.size();i++) {
    if (immrs[i] == '(') break;
    result = result + immrs[i];
  }
  return result;
}

std::string Parser::get_rs_in_immrs(std::string immrs) {
  std::string result;
  bool start = false;
  for (int i=0;i<immrs.size();i++) {
    if (immrs[i] == ')') break;
    if (start) {
      result = result + immrs[i];
    }
    if (!start && immrs[i] == '(') {
      start = true;
    }
  }
  return result;
}

std::string Parser::parse_pure_code() {
  std::string binCode;
  for (int line=0;line<pureCodes.size();line++) {
    std::vector<std::string> currentLine = pureCodes[line];
    
    // r type
    if (currentLine[0] == "add") {
      binCode = binCode + "000000" 
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "100000\n";
    }
    if (currentLine[0] == "addu") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "100001\n";
    }
    if (currentLine[0] == "and") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "100100\n";
    }
    if (currentLine[0] == "div") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + "00000"
                + "00000" + "011010\n";
    }
    if (currentLine[0] == "divu") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + "00000"
                + "00000" + "011011\n";
    }
    if (currentLine[0] == "jalr") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + "00000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "001001\n";
    }
    if (currentLine[0] == "jr") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + "00000" // rt
                + "00000" // rd
                + "00000" + "001000\n";
    }
    if (currentLine[0] == "mfhi") {
      binCode = binCode + "000000"
                + "00000" // rs
                + "00000" // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "010000\n";
    }
    if (currentLine[0] == "mflo") {
      binCode = binCode + "000000"
                + "00000" // rs
                + "00000" // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "010010\n";
    }
    if (currentLine[0] == "mthi") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + "00000" // rt
                + "00000" // rd
                + "00000" + "010001\n";
    }
    if (currentLine[0] == "mtlo") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + "00000" // rt
                + "00000" // rd
                + "00000" + "010011\n";
    }
    if (currentLine[0] == "mult") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + "00000" // rd
                + "00000" + "011000\n";
    }
    if (currentLine[0] == "multu") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + "00000" // rd
                + "00000" + "011001\n";
    }
    if (currentLine[0] == "nor") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "100111\n";
    }
    if (currentLine[0] == "or") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "100101\n";
    }
    if (currentLine[0] == "sllv") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "000100\n";
    }
    if (currentLine[0] == "slt") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "101010\n";
    }
    if (currentLine[0] == "sltu") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "101011\n";
    }
    if (currentLine[0] == "srav") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "000111\n";
    }
    if (currentLine[0] == "srlv") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "000110\n";
    }
    if (currentLine[0] == "sub") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "100010\n";
    }
    if (currentLine[0] == "subu") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "100011\n";
    }
    if (currentLine[0] == "xor") {
      binCode = binCode + "000000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[3]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + "00000" + "100110\n";
    }
    if (currentLine[0] == "sll") {
      binCode = binCode + "000000"
                + "00000" // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + Parser::trans_sa_to_bin(currentLine[3]);
                + "000000\n";
    }
    if (currentLine[0] == "sra") {
      binCode = binCode + "000000"
                + "00000" // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + Parser::trans_sa_to_bin(currentLine[3]);
                + "000011\n";
    }
    if (currentLine[0] == "srl") {
      binCode = binCode + "000000"
                + "00000" // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rd
                + Parser::trans_sa_to_bin(currentLine[3]);
                + "000010\n";
    }
    if (currentLine[0] == "syscall") {
      binCode = binCode + "0000000000000000000000000000110";
    }

    // I type
    if (currentLine[0] == "beq") {
      int imm =  labelStorage[currentLine[3]] - line - 1;
      binCode = binCode + "000100"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "bgez") {
      int imm =  labelStorage[currentLine[2]] - line - 1;
      binCode = binCode + "000001"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + "00001" // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "bgtz") {
      int imm =  labelStorage[currentLine[2]] - line - 1;
      binCode = binCode + "000111"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + "00000" // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "blez") {
      int imm =  labelStorage[currentLine[2]] - line - 1;
      binCode = binCode + "000110"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + "00000" // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "bltz") {
      int imm =  labelStorage[currentLine[2]] - line - 1;
      binCode = binCode + "000001"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + "00000" // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "bne") {
      int imm =  labelStorage[currentLine[3]] - line - 1;
      binCode = binCode + "000101"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }

    if (currentLine[0] == "addi") {
      int imm = stoi(currentLine[3]);
      binCode = binCode + "001000"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]])
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]])
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "addiu") {
      int imm = stoi(currentLine[3]);
      binCode = binCode + "001001"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]])
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]])
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "andi") {
      int imm = stoi(currentLine[3]);
      binCode = binCode + "001100"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]])
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]])
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "lb") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "100000"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "lbu") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "100100"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "lh") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "100001"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "lhu") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "100101"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "lui") {
      int imm = stoi(currentLine[2]);
      binCode = binCode + "001111"
                + "00000" //rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) //rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "lw") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "100011"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "ori") {
      int imm = stoi(currentLine[3]);
      binCode = binCode + "001101"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) //rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) //rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "sb") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "101000"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "slti") {
      int imm = stoi(currentLine[3]);
      binCode = binCode + "001010"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) //rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) //rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "sltiu") {
      int imm = stoi(currentLine[3]);
      binCode = binCode + "001011"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) //rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) //rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "sh") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "101001"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "sw") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "101011"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "xori") {
      int imm = stoi(currentLine[3]);
      binCode = binCode + "001110"
                + Parser::trans_reg_int_to_bin(regMap[currentLine[2]]) //rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) //rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "lwl") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "100010"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "lwr") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "100110"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "swl") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "101010"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }
    if (currentLine[0] == "swr") {
      std::string rs = Parser::get_rs_in_immrs(currentLine[2]);
      int imm = stoi(Parser::get_imm_in_immrs(currentLine[2]));
      binCode = binCode + "101110"
                + Parser::trans_reg_int_to_bin(regMap[rs]) // rs
                + Parser::trans_reg_int_to_bin(regMap[currentLine[1]]) // rt
                + Parser::trans_imm_to_bin(imm) + "\n";
    }

    // j type
    if (currentLine[0] == "j") {
      int imm = labelStorage[currentLine[1]] + 0x100000;
      binCode = binCode + "000010"
                + trans_addr_to_long_bin(imm) + "\n";
    }
    if (currentLine[0] == "jal") {
      int imm = labelStorage[currentLine[1]] + 0x100000;
      binCode = binCode + "000011"
                + trans_addr_to_long_bin(imm) + "\n";
    }
  }
  return binCode;
}