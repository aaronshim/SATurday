class Formula {
public:
  Formula(int nVars) : nVars(nVars) {};
  ~Formula();
  void addClause(Clause *clause);
  int getNVars();
  bool checkSat(Model *model);
  bool checkUnsat(Model *model);
  void unitPropagate();
  void removeAllEmptyClauses();

  Formula *clone();
  string toString();

private:
  int nClauses = 0;
  int nVars;
  vector<Clause *> clauses;
};

Formula::~Formula() {
  for (auto c : clauses) {
    delete c;
  }
}

// Our attempt at unit-propagation pre-processing simplification.
// The theory is to see what literals there are and then simplify
//  each clause based on whether they contain that literal or not.
void Formula::unitPropagate() {
  //cout << "\nUNIT PROPOGATION STARTED\n" << toString();

  // in order to prevent this algorithm from running quadratic
  //  we first should keep a tally of which literals appear in
  //  which clauses (for easier simplification)
  vector<vector<Clause *>> lookup;
  for (int i = 0; i < nVars; ++i) {
    vector<Clause *> foo;
    lookup.push_back(foo);
  }
  vector<Literal *> literals; // and find all literals too
  // iterate through everything
  for (auto c : clauses) {
    if (c->getNumLiterals() == 1) {
      // collect clauses of just one literal
      literals.push_back(c->getLiterals().front()->clone());
      // save a copy so that we don't have to mess with the
      // actual literals when we modify
    }
    for (auto l : c->getLiterals()) {
     // and mark which literals are seen in which clauses
     lookup[l->getIndex()].push_back(c);
     // (we want to save exact pointers for editing clauses)
    }
  }

/*
  // optional structure print-and-test
  cout << "\nOur tally structure:\n";
  for (int i = 0; i < nVars; ++i) {
    cout << "For literal " << i + 1 << " we have ";
    for (auto c : lookup[i]) {
      cout << "(" << c->toString() << ") ";
    }
    cout << "\n";
  }
  cout << endl;
*/

 // now for the real fun-- for each literal, fix every clause
 for (auto l : literals) {
   for (auto c : lookup[l->getIndex()]) {
     //cout << "Looking for literal " << l->toString() << " in (" << c->toString() << ")" << endl;
     int contains = c->containsLiteral(l);
     //cout << "Result: " << contains << endl;
     if (contains == 1) {
        // contains exactly that literal
        // (we will remove the entire clause)
        //cout << "Deleting clause (" << c->toString() << ")" << endl;
        c->deleteAllLiterals();
     }
     else if (contains == -1) {
       // contains negation of that literal
       // (we will remove the literal from the clause)
       l->flipIsSet();
       //cout << "Deleting the literal " << l->toString() << " from clause (" << c->toString() << ")" << endl;
       c->deleteExactLiteral(l);
       l->flipIsSet(); // put it back to the state we found it in
                       // for the rest of the loop
     }
     else {
       // should never get here, because this is the list of clauses
       // that contain this literal, but I suppose we will do nothing
     }
   }
 }
 removeAllEmptyClauses();
 //cout << "UNIT PROPOGATION FINISHED\n" << toString();
}

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
