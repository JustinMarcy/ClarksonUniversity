#ifndef PAIR_H
#define PAIR_H

template <typename T>
class BTPair {
 public:
  BTPair(T first, T second);

  void setFirst(T new_val);
  void setSecond(T new_val);

  T getFirst();
  T getSecond();

  void print();

 private:
  T first;
  T second;
};

#endif
