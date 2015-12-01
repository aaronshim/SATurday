class Formula {
public:
  Formula(int nVars)
    : nVars(nVars) {};
  void addClause(Clause *clause);
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