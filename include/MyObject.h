#ifndef MyObject_h
#define MyObject_h

#include <string>
#include <vector>

class MyObject {
public:
  void setName(const std::string& name) { name_ = name; }
  const std::string& name() const { return name_; }

  void setA(double a) { a_ = a; }
  double a() const { return a_; }

  void setB(const std::vector<int>& b) { b_ = b; }
  const std::vector<int> b() const { return b_; }
  int bSum() const;

private:
  std::string name_{"MyObjectName"};
  double a_{3.14};
  std::vector<int> b_{1, 2, 3, 5, 8};
};

#endif
