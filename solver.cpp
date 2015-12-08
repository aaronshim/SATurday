class Solver {
public:
  static Model *solve(Formula *formula);

private:
  static Model *solveR(Formula *formula, Model *model, int backtrackDepth);
  static Model *solveRClone(Formula *formula, Model *model, int index, int setVar, int backtrackDepth);

  static int maxDepth;
};

int Solver::maxDepth = 0;

Model *Solver::solve(Formula *formula) {
  Model *model = new Model(formula->getNVars());

  // // This is just testing code.
  // model->setVar(0);
  // model->setVar(1);
  // model->clearVar(2);
  // cout << model->toString() << endl;

  // Setup.
  srand(time(NULL));

  return solveR(formula, model, 0);
}

Model *Solver::solveR(Formula *formula, Model *model, int backtrackDepth) {
  invariant(formula != NULL, 2331);

  //formula->unitPropagate();
  formula->simplify(model);

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
  //int firstSet = 0;

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

  if ((retModel = solveRClone(formula, model, nextIndex, firstSet, backtrackDepth))) {
    return retModel;
  }

  if (DEBUG >= 5) {
    cout << "Backtracking... depth=" << backtrackDepth << endl;
  }

  if ((retModel = solveRClone(formula, model, nextIndex, !firstSet, backtrackDepth))) {
    return retModel;
  }

  delete model;
  return NULL;
}

Model *Solver::solveRClone(Formula *formula, Model *model, int index, int setVar, int backtrackDepth) {
  Model *modelClone = model->clone();
  Formula *formulaClone = formula->clone();
  if (setVar) {
    modelClone->setVar(index);
  } else {
    modelClone->clearVar(index);
  }
  Model *retModel = solveR(formulaClone, modelClone, backtrackDepth + 1);
  delete formulaClone;
  return retModel;
}
