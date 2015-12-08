class Clause {
public:
  ~Clause();
  void addLiteral(int vari, bool isSet);
  void addLiteral(Literal *literal);
  int getFirstLiteralIndex();
  Literal *getFirstLiteral();
  int getNumLiterals();
  bool checkSat(Model *model);
  bool deleteOffendingLiterals(Model *model);

  Clause *clone();
  string toString();

private:
  int nLiterals = 0;
  vector<Literal *> literals;
};

Clause::~Clause() {
  for (auto l : literals) {
    delete l;
  }
}

void Clause::addLiteral(int vari, bool isSet) {
  literals.push_back(new Literal(vari, isSet));
  nLiterals ++;
}

void Clause::addLiteral(Literal *literal) {
  literals.push_back(literal);
  nLiterals ++;
}

int Clause::getNumLiterals() {
  return nLiterals;
}

int Clause::getFirstLiteralIndex() {
  invariant(literals.size() > 0, 9348);
  return literals[0]->getIndex();
}

Literal *Clause::getFirstLiteral() {
  invariant(literals.size() > 0, 9349);
  return literals[0];
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

// For simplification, if there are literals in the clause that
// cannot be satisfied given the current model, we remove them
// from the clause.
// Returns true if we have end up with unsatisfiable empty clause.
bool Clause::deleteOffendingLiterals(Model *model) {
  for (int i = 0; i < nLiterals; i ++) {
    int vari = literals[i]->getIndex();
    bool varPos = literals[i]->getIsSet();

    if (!model->isAssigned(vari)) continue;

    if (model->checkVar(vari) != varPos) {
      delete literals[i];
      literals.erase(literals.begin() + i);

      i --;
      nLiterals --;
    }
  }

  return literals.size() == 0;
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
