class Parser {
public:
  static Formula *parse(FILE *file);
  static FILE *open(char *fname);
};

Formula *Parser::parse(FILE *file) {
  int nClauses, nVars;
  fscanf(file, "p cnf %d %d", &nVars, &nClauses);

  Formula *formula = new Formula(nVars);

  for (int i = 0; i < nClauses; i ++) {
    Clause *clause = new Clause();
    formula->addClause(clause);

    // Get next literal.
    while (1) {
      int literal;
      int nScanned = fscanf(file, "%d", &literal);

      if (nScanned == 0 || literal == 0) break;

      clause->addLiteral(abs(literal), literal > 0);
    }
  }

  return formula;
}

FILE *Parser::open(char *fname) {
  FILE *file = fopen(fname, "r");

  if (file == NULL) {
    return NULL;
  }

  return file;
}

// p cnf 3 4
// 1 -2 0
// -1 2 -3 0
// -3 -2 0
// 1 3 0