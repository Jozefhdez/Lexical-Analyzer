# Lexical Analyzer

This project implements a simple lexical analyzer (lexer) in C++. It reads mathematical expressions from a `.txt` file, tokenizes each line, and classifies each token according to its type (integer, float, operator, variable, or parenthesis).

## Project Structure

- **main.cpp**: Entry point. Handles file selection, reads expressions, and prints tokenization results.
- **Automaton.h**: Defines the `Automaton` class, which manages the finite automaton logic for tokenization.
- **State.h**: Defines the `State` class, representing states in the automaton and their transitions.
- **expressions.txt**: Example input file containing mathematical expressions to be analyzed.
- **README.md**: Project documentation.

## How It Works

1. **File Selection**:  
   On startup, the program lists all `.txt` files in the current directory and prompts the user to select one.

2. **Tokenization**:  
   The selected file is read line by line. Each line (expression) is processed by the lexer, which uses a deterministic finite automaton (DFA) to identify tokens.

3. **Token Types**:  
   The lexer recognizes the following token types:
   - **Integer**: Sequence of digits (e.g., `123`)
   - **Float**: Digits with a decimal point (e.g., `10.5`)
   - **Operator**: `+`, `-`, `*`, `/`, `=`
   - **Variable**: Sequence of lowercase letters (e.g., `tmp`)
   - **Parenthesis**: `(` or `)`

4. **Output**:  
   For each expression, the program prints a table with the tokens and their types.

## Example

Given the following line in `expressions.txt`:

```
a = 5 + 3
```

The output will be:

```
Expression 1: a = 5 + 3
-------------------------
Token    Type
-------------------------
a        Variable
=        Assignment
5        Integer
+        Sum
3        Integer
```

## How to Build and Run

1. **Requirements**:
   - C++17 or later (for `<filesystem>`)
   - A C++ compiler (e.g., g++, clang++)

2. **Build**:

   g++ -std=c++17 main.cpp -o lexer

3. **Run**:

   ./lexer

   Follow the prompts to select an input `.txt` file.

## Customization

- **Adding More Expressions**:  
  Edit `expressions.txt` or add your own `.txt` files with mathematical expressions.

- **Modifying Token Types**:  
  Update the DFA logic in `main.cpp` and `Automaton.h` to recognize new token types or symbols.

## File Reference

- `main.cpp`: Main logic, file handling, and lexer invocation.
- `Automaton.h`: Automaton class for DFA-based tokenization.
- `State.h`: State class for DFA states and transitions.
- `expressions.txt`: Example expressions for testing.

## License

This project is provided for educational purposes.