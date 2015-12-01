#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

#include "literal.cpp"
#include "clause.cpp"
#include "formula.cpp"
#include "parser.cpp"

int main(int argc, char **argv) {
  if (argc != 2) {
    cerr << "usage: saturday <filename>" << endl;
    return 1;
  }

  // Get file pointer for <filename>.
  char *fname = argv[1];
  FILE *file = Parser::open(fname);
  if (file == NULL) {
    cerr << "File '" << fname << "' failed to open!" << endl;
    return 1;
  }

  // Parse the file.
  Formula *formula = Parser::parse(file);
  cout << formula->toString();

  fclose(file);

  return 0;
}