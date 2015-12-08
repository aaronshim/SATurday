class Solver {
public:
  static Model *solve(Formula *formula);

private:
  static Model *solveR(Formula *formula, Model *model, int backtrackDepth);
  static Model *solveRClone(Formula *formula, Model *model, int index, int setVar, int backtrackDepth);

  static int maxDepth;
  static int nodesFailed;
  static int CUTOFF;
};

int Solver::maxDepth = 0;
int Solver::CUTOFF = GLOBAL_CUTOFF;
int Solver::nodesFailed = Solver::CUTOFF;

Model *Solver::solve(Formula *formula) {
  Model *model = new Model(formula->getNVars());

  // // This is just testing code.
  // model->setVar(0);
  // model->setVar(1);
  // model->clearVar(2);
  // cout << model->toString() << endl;

  // Setup.
  srand(time(NULL));

  Model *solvedModel;

  // If nodes failed was surpassed, we restart.
  while (nodesFailed >= CUTOFF) {
    nodesFailed = 0;
    CUTOFF += GLOBAL_CUTOFF;
    solvedModel = solveR(formula, model, 0);
  }

  return solvedModel;
}

Model *Solver::solveR(Formula *formula, Model *model, int backtrackDepth) {
  invariant(formula != NULL, 2331);

  // Restart solver if nodes failed is above cutoff.
  if (nodesFailed >= CUTOFF) {
    return NULL;
  }

  int state = formula->simplify(model);
  switch (state) {
    case -1: // If unsat, return null.
      if (DEBUG >= 5)
        cout << "Unsatisfied model: " << model->toString() << endl;
      return NULL;
    case 1: // If sat, return the model.
      model->complete();
      return model->clone();
  }

  int nextIndex = formula->nextVar();
  invariant(!model->isAssigned(nextIndex), 1940);

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
    cout << "progress: " << backtrackDepth << "/" << formula->getNVars() <<
            "\tnodes failed: " << nodesFailed << endl;
  }

  if ((retModel = solveRClone(formula, model, nextIndex, firstSet, backtrackDepth))) {
    nodesFailed = 0;
    return retModel;
  }

  if (DEBUG >= 5) {
    cout << "Backtracking... depth=" << backtrackDepth << endl;
  }

  if ((retModel = solveRClone(formula, model, nextIndex, !firstSet, backtrackDepth))) {
    nodesFailed = 0;
    return retModel;
  }

  nodesFailed ++;

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
  delete modelClone;
  return retModel;
}
