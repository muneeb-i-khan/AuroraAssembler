#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

enum InstructionType { IS_LABEL, IS_OPCODE, IS_OPERAND, IS_INVALID };

struct Instruction {
  std::string text;
  InstructionType type;
  unsigned int address;

  // Instruction() : address(0) {}
};

InstructionType classify(const std::string &token) {
  if (token.back() == ':' &&
      std::all_of(token.begin(), token.end() - 1, [](unsigned char c) {
        return std:: // Instruction() : address(0) {}
            isupper(c);
      })) {
    return IS_LABEL;
  }

  if (token.size() == 3 &&
      std::all_of(token.begin(), token.end(),
                  [](unsigned char c) { return std::islower(c); })) {
    return IS_OPCODE;
  }

  if ((token == "a") || (std::all_of(token.begin(), token.end(), ::isdigit))) {
    return IS_OPERAND;
  }

  return IS_INVALID;
}

std::vector<Instruction> classifier(const std::vector<std::string> &tokens) {
  std::vector<Instruction> classifiedInstructions;

  for (unsigned int i = 0; i < tokens.size(); ++i) {
    InstructionType type = classify(tokens[i]);
    Instruction instr;
    instr.text = tokens[i];
    instr.type = type;
    instr.address = i * 8;

    classifiedInstructions.push_back(instr);
  }

  return classifiedInstructions;
}

std::string hex_to_binary(const std::string &hexString) {
  unsigned int intValue = std::stoi(hexString, nullptr, 16) & 0xFF;
  return std::bitset<8>(intValue).to_string();
}

bool isValidDecimal(const std::string& str) {
    return !str.empty() && str.find_first_not_of("0123456789") == std::string::npos;
}

std::string dec_to_binary(const std::string &decimalString) {
    int decimalValue = std::stoi(decimalString);

    decimalValue &= 0xFF;

    return std::bitset<8>(decimalValue).to_string();

}
#endif
