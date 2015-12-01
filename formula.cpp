class Formula {
public:
  Formula(int nVars)
    : nVars(nVars) {};
  void addClause(Clause *clause);
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

string Formula::toString() {
  ostringstream os;

  os << "nClauses: " << nClauses << endl
     << "nVars: " << nVars;

  for (int i = 0; i < nClauses; i ++) {
    os << clauses[i]->toString() << endl;
  }

  return os.str();
}