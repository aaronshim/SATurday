class Model {
  private:
    int nVars;
    int literals[];
  public:
    Model(int nVars);
    void setLiterals(int newLiterals[]);
    Model *clone();
    string toString();
};

Model::Model(int nVars) : nVars(nVars) {
  // make new array and set it all to 0 (default unset value)
  literals = new int[nVars];
  memset(literals, 0, sizeof(int)*nVars);
}

// we really hope that the newLiterals array is the same size
void Model::setLiterals(int newLiterals[]) {
  for(int i = 0; i < nVars; ++i) {
    literals[i] = newLiterals[i];
  }
}

string Model::toString() {
  ostringstream os;
  for(int i = 0; i < nVars; ++i) {
    int lit = i*literals[i];
    os << lit  << " ";
  }
  return os.str();
}

Model *Model::clone() {
  Model *newModel = new Model(nVars);
  newModel->setLiterals(literals);
}

