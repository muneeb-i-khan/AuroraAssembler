#include <iostream>
#include <map>
#include <string>
using namespace std;

map<string, string> gen_instr_map() {
  map<string, string> mp;
  mp["add"] = "00000010";
  mp["sub"] = "00000110";
  mp["lda"] = "00001110";
  mp["str"] = "00001110";
  mp["jmp"] = "00010010";
  mp["cmp"] = "00010110";
  mp["cal"] = "00011010";
  mp["not"] = "00011110";
  mp["hlt"] = "00100010";
  mp["mov"] = "00100110";
  mp["xor"] = "00101110";
  mp["and"] = "00101110";
  mp["or"] = "00110010";
  return mp;
}

map<string, string> gen_opcode_map() {
  map<string, string> mp;
  mp["a"] = "00000000";
  return mp;
}


