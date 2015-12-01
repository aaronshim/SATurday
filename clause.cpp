class Clause {
public:
  void addLiteral(int vari, bool positive);
  void addLiteral(Literal *literal);
  Clause *clone();
  string toString();

private:
  int nLiterals = 0;
  vector<Literal *> literals;
};

void Clause::addLiteral(int vari, bool positive) {
  literals.push_back(new Literal(vari, positive));
  nLiterals ++;
}

void Clause::addLiteral(Literal *literal) {
  literals.push_back(literal);
  nLiterals ++;
}

Clause *Clause::clone() {
  Clause *newClause = new Clause();

  for (int i = 0; i < nLiterals; i ++) {
    newClause->addLiteral(literals[i]->clone());
  }

  return newClause;
}

string Clause::toString() {
  ostringstream os;

  for (int i = 0; i < nLiterals; i ++) {
    os << literals[i]->toString() << " ";
  }

  return os.str();
}