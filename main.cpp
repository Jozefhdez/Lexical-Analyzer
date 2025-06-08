#include <iostream>
#include <fstream>
#include "State.h"
#include "Automaton.h"
#include "string"

void lexer(std::string filepath) {
  std::string numbers = "0123456789";
  std::string letters = "abcdefghijklmnopqrstuvwxyz";
  std::string symbols = "+-=*/";
  std::string space = " ";
  std::string dot = ".";
  std::string parenthesis = "()";

  std::string alphabet = "0123456789abcdefghijklmnopqrstuvwxyz+-=*/ .()";

  State Q0("Q0", false, false);
  State Q1("Q1", true, false);
  State Q2("Q2", false, false);
  State Q3("Q3", true, false);
  State Q4("Q4", true, false);
  State Q5("Q5", true, false);
  State Q6("Q6", true, false);
  
  std::map<State*, std::string> types = {
    {&Q1, "Integer"},
    {&Q3, "Float"},
    {&Q4, "Operator"},
    {&Q5, "Variable"},
    {&Q6, "Parenthesis"}
  };

  // Q0 Transitions
  Q0.addTransition(space, &Q0);
  
  for(int i = 0; i < numbers.length(); i++){
    Q0.addTransition(std::string(1, numbers[i]), &Q1);
  }

  for(int i = 0; i < symbols.length(); i++){
    Q0.addTransition(std::string(1, symbols[i]), &Q4);
  }

  for(int i = 0; i < letters.length(); i++){
    Q0.addTransition(std::string(1, letters[i]), &Q5);
  }

  for(int i = 0; i < parenthesis.length(); i++){
    Q0.addTransition(std::string(1, parenthesis[i]), &Q6);
  }

  // Q1 Transitions
  for(int i = 0; i < numbers.length(); i++){
    Q1.addTransition(std::string(1, numbers[i]), &Q1);
  }
  
  Q1.addTransition(dot, &Q2);

  // Q2 Transitions
  for(int i = 0; i < numbers.length(); i++){
    Q2.addTransition(std::string(1, numbers[i]), &Q3);
  }

  // Q3 Transitions
  for(int i = 0; i < numbers.length(); i++){
    Q3.addTransition(std::string(1, numbers[i]), &Q3);
  }
  
  // Q5 Transitions
  for(int i = 0; i < letters.length(); i++){
    Q5.addTransition(std::string(1, letters[i]), &Q5);
  }

  Automaton automaton(&Q0, alphabet, types);
  
  // Open the file
  std::ifstream file(filepath);
  
  if (!file.is_open()) {
    std::cerr << "Error: Could not open expressions.txt" << std::endl;
  }
  
  std::string line;
  int expressionNumber = 1;
  
  // Process each line in the file
  while (std::getline(file, line)) {
    std::cout << "Expression " << expressionNumber << ": " << line << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Token" << "    Type" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    std::vector<std::pair<std::string, std::string>> tokens = automaton.tokens(line);
    
    if(tokens.empty()) {
      std::cout << "No valid tokens found in this expression." << std::endl;
    }
    else {
      for(const auto& token : tokens){
        if(token.second == ""){
          std::cout << "No valid tokens found in this expression." << std::endl;
        }
        else{
          std::cout << token.first << "        " << token.second << std::endl;
        }
      }
    }
    
    std::cout << "\n\n";
    expressionNumber++;
  }
  
  file.close();
  
}

int main(){

    std::vector<std::filesystem::path> txtFiles;

    for (auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path())) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            txtFiles.push_back(entry.path());
        }
    }

    if (txtFiles.empty()) {
        std::cout << "No .txt files found in the current directory." << std::endl;
        return 1;
    }

    std::cout << "Select a file by entering the corresponding number:" << std::endl;
    for (size_t i = 0; i < txtFiles.size(); ++i) {
        std::cout << i + 1 << ": " << txtFiles[i].filename().string() << std::endl;
    }

    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    if (choice < 1 || choice > txtFiles.size()) {
        std::cout << "Invalid choice." << std::endl;
        return 1;
    }

    std::filesystem::path selectedFile = txtFiles[choice - 1];
    std::cout << "You selected: " << selectedFile << std::endl;

    lexer(selectedFile);

}
