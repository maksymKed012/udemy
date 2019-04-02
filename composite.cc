#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct ContainsIntegers {
    virtual int getSum() const = 0;
};

struct SingleValue : ContainsIntegers
{
  int value{ 0 };

  SingleValue() = default;

  explicit SingleValue(const int value)
    : value{value}
  {
  }

  int getSum() const override {
      return value;
  }
  // TODO
};

struct ManyValues : vector<int> , ContainsIntegers
{
  void add(const int value)
  {
    push_back(value);
  }

  int getSum() const override {
      return std::accumulate(begin(), end(), 0);
  }
};

int sum(const vector<ContainsIntegers*> items)
{
    int sum = 0;
    for(const auto item : items) {
        sum += item->getSum;
    }
}