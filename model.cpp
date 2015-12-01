class Model {
  private:
    int nVars;
    int* vars;
  public:
    Model(int nVars);
    void setVars(int newVars[]);
    // WARNING: THE FOLLOWING METHODS ARE INDEXED AT 0
    void setVar(int i); // sets our variable positive
    void clearVar(int i); // sets our variable negative
    bool checkVar(int i); // will be problematic if variable is unset default value
    bool isAssigned(int i); // will say whether the variable is assigned or not
    Model *clone();
    string toString();
};

Model::Model(int nVars) : nVars(nVars) {
  // make new array and set it all to 0 (default unset value)
  vars = new int[nVars];
  memset(vars, 0, sizeof(int)*nVars);
}

// we really hope that the newVars array is the same size
void Model::setVars(int newVars[]) {
  for(int i = 0; i < nVars; ++i) {
    vars[i] = newVars[i];
  }
}

void Model::setVar(int i) {
  vars[i] = 1;
}

void Model::clearVar(int i) {
  vars[i] = -1;
}

bool Model::checkVar(int i) {
  if (vars[i] == 1) {
    return true;
  }

  if (vars[i] == -1) {
    return false;
  }

  throw 1337; // value was not originally set
}

bool Model::isAssigned(int i) {
  return vars[i] != 0;
}

string Model::toString() {
  ostringstream os;
  for(int i = 0; i < nVars; ++i) {
    int lit = (i + 1)*vars[i];
    os << lit  << " ";
  }
  return os.str();
}

Model *Model::clone() {
  Model *newModel = new Model(nVars);
  newModel->setVars(vars);
  return newModel;
}

