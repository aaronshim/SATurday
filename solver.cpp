class Solver {
public:
  static Model *solve(Formula *formula);
private:
  static Model *solveR(Formula *formula, Model *model);
};

Model *Solver::solve(Formula *formula) {
  // // This is just testing code.
  // model->setVar(0);
  // model->setVar(1);
  // model->clearVar(2);
  // cout << model->toString() << endl;

  return solveR(formula, new Model(formula->getNVars()));
}

Model *Solver::solveR(Formula *formula, Model *model) {
  // Check if model satisfies formula, and if so, return it.
  if (formula->checkSat(model)) {
    return model;
  }

  return NULL;
}
