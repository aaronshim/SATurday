class Model {
  private:
    int nVars;
    int* literals;
  public:
    Model(int nVars);
    void setLiterals(int newLiterals[]);
    // WARNING: THE FOLLOWING METHODS ARE INDEXED AT 0
    void setVar(int i); // sets our variable positive
    void clearVar(int i); // sets our variable negative
    bool getVar(int i); // will be problematic if variable is unset default value
    bool isVarSet(int i); // will say whether the variable is set or not
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

void Model::setVar(int i) {
  literals[i] = 1;
}

void Model::clearVar(int i) {
  literals[i] = -1;
}

bool Model::getVar(int i) {
  if (literals[i] == 1) {
    return true;
  }
  
  if (literals[i] == -1) {
    return false;
  }

  throw 1337; // value was not originally set
}

bool Model::isVarSet(int i) {
  return literals[i] != 0;
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
  return newModel;
}

