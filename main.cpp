#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <string.h>
using namespace std;

#include "literal.cpp"
#include "clause.cpp"
#include "formula.cpp"
#include "parser.cpp"
#include "model.cpp"
#include "solver.cpp"

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
  fclose(file);

  cout << formula->toString();

  // model testing code
  Model *testModel = new Model(5);
  testModel->setVar(1);
  testModel->setVar(2);
  testModel->clearVar(2);
  cout << testModel->toString() << endl;

  Model *model = Solver::solve(formula);

  if (model == NULL) {
    cout << "s UNSATISFIABLE" << endl;
  } else {
    cout << "s SATISFIABLE" << endl;
    cout << "v " << model->toString() << endl;
  }

  return 0;
}
