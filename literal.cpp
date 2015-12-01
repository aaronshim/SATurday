class Literal {
public:
  Literal(int index, int isSet)
    : index(index), isSet(isSet) {};
  int getIndex() { return index; };
  bool getIsSet() { return isSet; };

  Literal *clone();
  string toString();

private:
  int index;
  bool isSet;
};

Literal *Literal::clone() {
  return new Literal(index, isSet);
}

string Literal::toString() {
  ostringstream os;

  if (!isSet) {
    os << "-";
  }
  os << index + 1;

  return os.str();
}