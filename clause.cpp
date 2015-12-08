class Clause {
public:
  ~Clause();
  void addLiteral(int vari, bool isSet);
  void addLiteral(Literal *literal);
  vector<Literal *> getLiterals();
  int getNumLiterals();
  bool checkSat(Model *model);
  bool checkUnsat(Model *model);
  int containsLiteral(Literal *literal);
  bool deleteAllLiterals();
  bool deleteExactLiteral(Literal *literal);

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

vector<Literal *> Clause::getLiterals() {
  return literals;
}

bool Clause::checkSat(Model *model) {
  // edge casing: empty clauses are always satisfiable
  if (nLiterals <= 0) return true;

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
  // edge casing
  // (empty clause is inherently satisfiable)
  if (nLiterals <= 0) return false;

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

// 1 if literal matches, 0 if literal not there
//  -1 if reverse literal there
//  (exact literals take precedence if both exact and negation exist)
int Clause::containsLiteral(Literal *literal) {
  int returnVal = 0;
  for (int i = 0; i < nLiterals; ++i) {
    if (literals[i]->getIndex() == literal->getIndex()) {
      if (literals[i]->getIsSet() == literal->getIsSet()) {
        return 1;
      }
      // exact match has to take precedence, so only return if no
      // exact match is found later on
      returnVal = -1;
    }
  }
  return returnVal;
}

// return value is true for success
bool Clause::deleteAllLiterals() {
  // don't touch clauses of one literal
  if (nLiterals <= 1) return false;
  nLiterals = 0;
  // hopefully shouldn't touch the literals data itself
  // because we only had them in the vector through pointers
  literals.clear();
  return true;
}

// return value is true for success
// (return value is false if literal does not exist)
bool Clause::deleteExactLiteral(Literal* literal) {
  // should not touch clauses of one literal
  if (nLiterals <= 1) return false;
  bool deleted = false;
  for (int i = 0; i < nLiterals; ++i) {
    if (literal->getIndex() == literals[i]->getIndex() && literal->getIsSet() == literals[i]->getIsSet()) {
      literals.erase(literals.begin() + i);
      --i; // gotta keep looking in case multiple literals here
      --nLiterals;
      deleted = true;
    }
  }
  return deleted;
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
