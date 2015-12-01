class Clause {
public:
  void addLiteral(int vari, bool positive);
  string toString();

private:
  int nLiterals = 0;
  vector<Literal *> literals;
};

void Clause::addLiteral(int vari, bool positive) {
  literals.push_back(new Literal(vari, positive));
  nLiterals ++;
}

string Clause::toString() {
  ostringstream os;

  for (int i = 0; i < nLiterals; i ++) {
    os << literals[i]->toString() << " ";
  }

  return os.str();
}