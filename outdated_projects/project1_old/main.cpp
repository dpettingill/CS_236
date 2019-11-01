#include <stdio.h>
#include <string>
#include <iostream>
#include "Scanner.h"

using namespace std;

//Scanner my_scanner;

int main(int argc, char* argv[]) {
   // for (int i = 0; i < *argv.size(); i++) {}
    //my_scanner = new Scanner();
    Scanner my_scanner(argv[1]);
    my_scanner.readFile(); //reads the file and parses the tokens
    my_scanner.printTokenVector(); //prints out the tokens
}