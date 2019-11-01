#include <stdio.h>
#include <string>
#include <iostream>
#include "Scanner.h"
#include "Token.h"

//Scanner my_scanner;

int main(int argc, char* argv[]) {
   // for (int i = 0; i < *argv.size(); i++) {}
    //my_scanner = new Scanner();
    Scanner my_scanner;
    std::string filename = argv[1]; //takes in the new filename
    my_scanner.setFilename(filename); //sets filename to my_scanner object
    my_scanner.readFile(); //reads the file and parses the tokens
    my_scanner.printTokenVector(); //prints out the tokens
}