#include <iostream>
#include <string>
#include <functional>

using namespace std;



struct Flower
{
  virtual string str() = 0;
};

struct Rose : Flower
{
  string str() override {
    return "A rose";
  }
};

struct FlowerDecorator : Flower {

    Flower& flower_;

    FlowerDecorator(Flower& flower) : flower_(flower) {}

    string decorated_str() = 0;

    string str() final {
        ostringstream oss;
        auto conj = conjunction();
        auto dec_str = conj == "" ? "" : decorated_str();
        oss << conj << dec_str;
        return oss.str();
    }

    string conjunction() {
        if(flower_.str() == "A rose"){
            return " that is";
        } else if(flower_.str().find_first_of(decorated_str()) == string::npos) {
            return " and";
        } else {
            return "";
        }
    }
};

struct RedFlower : FlowerDecorator
{   
    RedFlower( Flower& flower) : FlowerDecorator(flower) {} 

    string decorated_str() override {
        return " red";
    }
};

struct BlueFlower : FlowerDecorator
{   
    BlueFlower( Flower& flower) : FlowerDecorator(flower) {}

    string decorated_str() override {
       return " blue";
    }
};

int main (int argc, char** argv) {
    return 0;
}

