class Clause {
public:
  void addLiteral(int vari, bool isSet);
  void addLiteral(Literal *literal);
  bool checkSat(Model *model);
  bool checkUnsat(Model *model);

  Clause *clone();
  string toString();

private:
  int nLiterals = 0;
  vector<Literal *> literals;
};

void Clause::addLiteral(int vari, bool isSet) {
  literals.push_back(new Literal(vari, isSet));
  nLiterals ++;
}

void Clause::addLiteral(Literal *literal) {
  literals.push_back(literal);
  nLiterals ++;
}

bool Clause::checkSat(Model *model) {
  // Check each literal for true.
  for (int i = 0; i < nLiterals; i ++) {
    int vari = literals[i]->getIndex();
    bool varPos = literals[i]->getIsSet();
    if (!model->isAssigned(vari)) continue;
    bool varSet = model->checkVar(vari);
    if (varSet == varPos) return true;
  }

  return false;
}

bool Clause::checkUnsat(Model *model) {
  // Check each literal for true.
  for (int i = 0; i < nLiterals; i ++) {
    int vari = literals[i]->getIndex();
    bool varPos = literals[i]->getIsSet();
    if (!model->isAssigned(vari)) return false;
    bool varSet = model->checkVar(vari);
    if (varSet == varPos) return false;
  }

  return true;
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