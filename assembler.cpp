#include "instrmap.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> tokeniser(string line) {
  vector<string> tokens;
  string tmp = "";
  for (char c : line) {
    if (c != ' ') {
      tmp.push_back(c);
    } else {
      tokens.push_back(tmp);
      tmp = "";
    }
  }
  if (!tmp.empty()) {
    tokens.push_back(tmp);
  }
  return tokens;
}

int main() {
  // Tokenise
  ifstream from_file("test.asm");
  if (!from_file) {
    cout << "Cannot open file - test.asm";
    exit(1);
  }
  vector<string> tokens;
  string temp_str;
  while (getline(from_file, temp_str)) {
    vector<string> line_tokens = tokeniser(temp_str);
    tokens.insert(tokens.end(), line_tokens.begin(), line_tokens.end());
  }
  from_file.close();

  for (const string &token : tokens) {
    cout << token << endl;
  }

  vector<Instruction> classifiedInstructions = classifier(tokens);

  for (const Instruction &instr : classifiedInstructions) {
    cout << "Token: " << instr.text << ", Type: ";
    switch (instr.type) {
    case IS_LABEL:
      cout << "Label";
      break;
    case IS_OPCODE:
      cout << "Opcode";
      break;
    case IS_OPERAND:
      cout << "Operand";
      break;
    case IS_INVALID:
      cout << "Invalid";
      break;
    }
    cout << ", Address: " << instr.address << endl;
  }

  map<string, string> mp = gen_instr_map();

  vector<string> machine_array;

  map<string, string> omp = gen_opcode_map();


  for (const Instruction &instr : classifiedInstructions) {

    if (mp.find(instr.text) != mp.end()) {
      machine_array.push_back(mp[instr.text]);
    } else if(omp.find(instr.text) != omp.end()){
        machine_array.push_back(omp[instr.text]);
    }
    else{
        if(instr.text.back() == 'H'){
            string temp = hex_to_binary(instr.text);
            machine_array.push_back(temp);
        }
        // else{
        //     string temp = dec_to_binary(instr.text);
        //     machine_array.push_back(temp);
        // }
    }
  }

  ofstream to_file("machine.txt");
  for (const string &str : machine_array) {
    to_file << str;
    to_file << " ";
  }
  to_file.close();
  return 0;
}
