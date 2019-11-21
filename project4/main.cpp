#include <stdio.h>
#include <string>
#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#include "Interpreter.h"
#include "DatalogProgram.h"

using namespace std;

//Scanner my_scanner;

int main(int argc, char* argv[]) {
   Scanner my_scanner(argv[1]);
   my_scanner.readFile(); //reads the file and parses the tokens
   Parser my_parser(my_scanner.getTokenVect());
   my_parser.parse(); //parse the vector of Tokens.
   Interpreter my_interp = Interpreter(my_parser.getDatalogProgram());
   return 0;
}