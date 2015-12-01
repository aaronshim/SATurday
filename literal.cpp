class Literal {
public:
  Literal(int index, int positive)
    : index(index), positive(positive) {};
  string toString();

private:
  int index;
  bool positive;
};

string Literal::toString() {
  ostringstream os;

  if (!positive) {
    os << "-";
  }
  os << index;

  return os.str();
}