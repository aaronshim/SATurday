class Solver {
public:
  Model *solve(Formula *formula);
private:
  Model *solveR(Formula *formula, Model *model);
};

Model *Solver::solve(Formula *formula) {
  return solveR(formula, new Model());
}

Model *Solver::solveR(Formula *formula, Model *model) {

  return NULL;
}
