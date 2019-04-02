#include <string>
using namespace std;

struct Person
{
  int id;
  string name;

  Person(const int id, const string& name): id(id), name(name) {}
};

class PersonFactory
{
    int person_id_counter = 0;
public:
  Person create_person(const string& name)
  {
     return {person_id_counter++, name};
  }
};

int main () {
    return 0;
}