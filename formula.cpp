class Formula {
public:
  Formula(int nVars) : nVars(nVars) {};
  ~Formula();
  void addClause(Clause *clause);
  const vector<Clause *>& getClauses();
  int getNVars();
  bool checkSat(Model *model);
  bool checkUnsat(Model *model);
  void simplify(Model *model);

  int nextVar(); // Gets the index of the next unassigned var.

  Formula *clone();
  string toString();

private:
  int nClauses = 0;
  int nVars;
  void unitPropagate(Model *model);
  void deleteSatisfied(Model *model);
  void removeAllEmptyClauses();
  vector<Clause *> clauses;
};

Formula::~Formula() {
  for (auto c : clauses) {
    delete c;
  }
}

const vector<Clause *>& Formula::getClauses() {
  return clauses;
}

// Our attempt at unit-propagation pre-processing simplification.
// The theory is to see what literals there are and then simplify
//  each clause based on whether they contain that literal or not.
void Formula::unitPropagate(Model *model) {
  // TODO: MAKE THIS DECIDE THE ACTUAL VARIABLE IN THE MODEL

  // For all singule-literal clauses, decide for that variable.
  for (auto c : clauses) {
    if (c->getNumLiterals() > 1) continue;

    Literal *literal = c->getFirstLiteral();
    int vari = literal->getIndex();
    if (literal->getIsSet()) {
      model->setVar(vari);
    } else {
      model->clearVar(vari);
    }
  }
}

// If entire clause is satisfied, drop it
// If not, find the unsatisfied literals and drop those
void Formula::deleteSatisfied(Model *model) {
  for (auto c : clauses) {
    if (c->checkSat(model)) {
      c->deleteAllLiterals();
    } else {
      c->deleteOffendingLiterals(model);
    }
  }
}

// This should be the one method that the solver calls
void Formula::simplify(Model *model) {
  unitPropagate(model);
  deleteSatisfied(model);
  removeAllEmptyClauses();
}

// For cleanup during simplification procedure
void Formula::removeAllEmptyClauses() {
  for (int i = 0; i < nClauses; ++i) {
    if (clauses[i]->getNumLiterals() <= 0) {
      clauses.erase(clauses.begin() + i);
      --i;
      --nClauses;
    }
  }
}

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

int Formula::nextVar() {
  // Find the clause with lowest number of undecided literals.
  Clause *minClause = NULL;
  for (auto c : clauses) {
    if (!minClause || c->getNumLiterals() < minClause->getNumLiterals()) {
      minClause = c;
    }
  }
  invariant(minClause, 4939);

  // Use first literal?
  int vari = minClause->getFirstLiteralIndex();

  return vari;
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
