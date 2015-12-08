class Solver {
public:
  static Model *solve(Formula *f);

private:
  static Model *solveR(Model *model, int backtrackDepth);
  static Model *solveRClone(Model *model, int index, int setVar, int backtrackDepth);

  static Formula *formula;
  static int maxDepth;
};

Formula *Solver::formula = NULL;
int Solver::maxDepth = 0;

Model *Solver::solve(Formula *f) {
  Model *model = new Model(f->getNVars());

  // // This is just testing code.
  // model->setVar(0);
  // model->setVar(1);
  // model->clearVar(2);
  // cout << model->toString() << endl;

  // Setup.
  formula = f;
  srand(time(NULL));

  return solveR(model, 0);
}

Model *Solver::solveR(Model *model, int backtrackDepth) {
  invariant(formula != NULL, 2331);

  // have to clone formula to use unitPropagate()
  //formula->unitPropogate();

  // Check if model unsatisfies formula, and if so, return null.
  if (formula->checkUnsat(model)) {
    if (DEBUG >= 5)
      cout << "Unsatisfied model: " << model->toString() << endl;
    delete model;
    return NULL;
  }

  // Check if model satisfies formula, and if so, return it.
  if (formula->checkSat(model)) return model->complete();

  int nextIndex = model->nextVar();
  if (nextIndex == -1) return NULL;

  // Should we try setting the literal or clearing the literal first?
  int firstSet = rand() % 2;

  if (DEBUG >= 5)
    cout << "firstSet = " << firstSet << endl;

  Model *retModel;

  if (DEBUG >= 5) {
    cout << "Trying a value for " << nextIndex + 1 << " at depth " <<
      backtrackDepth << "..." << endl;
  }
  if (DEBUG >= 2) {
    if (backtrackDepth > maxDepth) {
      maxDepth = backtrackDepth;
    }
    cout << "progress: " << backtrackDepth << "/" << formula->getNVars() << endl;
  }

  if ((retModel = solveRClone(model, nextIndex, firstSet, backtrackDepth + 1))) {
    return retModel;
  }

  if (DEBUG >= 5) {
    cout << "Backtracking... depth=" << backtrackDepth << endl;
  }

  if ((retModel = solveRClone(model, nextIndex, !firstSet, backtrackDepth + 1))) {
    return retModel;
  }

  delete model;
  return NULL;
}

Model *Solver::solveRClone(Model *model, int index, int setVar, int backtrackDepth) {
  Model *modelClone = model->clone();
  if (setVar) {
    modelClone->setVar(index);
  } else {
    modelClone->clearVar(index);
  }
  return solveR(modelClone, backtrackDepth + 1);
}
