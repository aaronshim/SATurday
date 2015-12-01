class Formula {
public:
  Formula(int nVars)
    : nVars(nVars) {};
  void addClause(Clause *clause);
  int getNVars();
  bool checkSat(Model *model);
  bool checkUnsat(Model *model);

  Formula *clone();
  string toString();

private:
  int nClauses = 0;
  int nVars;
  vector<Clause *> clauses;
};

void Formula::addClause(Clause *clause) {
  clauses.push_back(clause);
  nClauses ++;
}

int Formula::getNVars() {
  return nVars;
}

bool Formula::checkSat(Model *model) {
  // Check each clause against model.
  for (int i = 0; i < nClauses; i ++) {
    if (!clauses[i]->checkSat(model)) return false;
  }

  return true;
}

bool Formula::checkUnsat(Model *model) {
  // Check each clause against model.
  for (int i = 0; i < nClauses; i ++) {
    if (clauses[i]->checkUnsat(model)) return true;
  }

  return false;
}

Formula *Formula::clone() {
  Formula *newFormula = new Formula(nVars);

  for (int i = 0; i < nClauses; i ++) {
    newFormula->addClause(clauses[i]->clone());
  }

  return newFormula;
}

string Formula::toString() {
  ostringstream os;

  os << "nClauses: " << nClauses << endl
     << "nVars: " << nVars << endl;

  for (int i = 0; i < nClauses; i ++) {
    os << clauses[i]->toString() << endl;
  }

  return os.str();
}