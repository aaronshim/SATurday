class Solver {
public:
  static Model *solve(Formula *formula);
private:
  static Model *solveR(Formula *formula, Model *model);
};

Model *Solver::solve(Formula *formula) {
  Model *model = new Model(formula->getNVars());

  // // This is just testing code.
  // model->setVar(0);
  // model->setVar(1);
  // model->clearVar(2);
  // cout << model->toString() << endl;

  return solveR(formula, model);
}

Model *Solver::solveR(Formula *formula, Model *model) {
  formula->unitPropagate();
  // Check if model unsatisfies formula, and if so, return null.
  if (formula->checkUnsat(model)) {
    cout << "Unsatisfied model: " << model->toString() << endl;
    free(model);
    return NULL;
  }

  // Check if model satisfies formula, and if so, return it.
  if (formula->checkSat(model)) return model->complete();

  int nextIndex = model->nextVar();
  if (nextIndex == -1) return NULL;

  Model *retModel;

  Model *modelCloneSet = model->clone();
  modelCloneSet->setVar(nextIndex);
  retModel = solveR(formula, modelCloneSet);
  if (retModel) return retModel;

  Model *modelCloneClear = model->clone();
  modelCloneClear->clearVar(nextIndex);
  retModel = solveR(formula, modelCloneClear);
  if (retModel) return retModel;

  free(model);
  return NULL;
}
