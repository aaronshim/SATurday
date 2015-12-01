class Literal {
public:
  Literal(int index, int positive)
    : index(index), positive(positive) {};
  Literal *clone();
  string toString();

private:
  int index;
  bool positive;
};

Literal *Literal::clone() {
  return new Literal(index, positive);
}

string Literal::toString() {
  ostringstream os;

  if (!positive) {
    os << "-";
  }
  os << index;

  return os.str();
}