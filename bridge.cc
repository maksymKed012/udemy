#include <string>
using namespace std;

class Renderer {
    public:
    virtual std::string what_to_render_as() const {return "";}
};

class RasterRenderer : public Renderer {
    std::string what_to_render_as() const override {
        return "pixels";
    }
};

class VectorRenderer : public Renderer {
    std::string what_to_render_as() const override {
        return std::string("lines");
    }
};

struct Shape
{
    Renderer* renderer_;
    string name;

    Shape(Renderer& renderer)
    {
        *renderer_ = renderer;
    }

    virtual std::string str() const {};
};

struct Triangle : Shape
{
    Triangle(Renderer renderer) : Shape(renderer)
    {
        name = "Triangle";
    }

    virtual std::string str() const override {
        return std::string("Drawing Triangle as ")
        .append(renderer_->what_to_render_as());
    }
};

struct Square : Shape
{
    Square(Renderer renderer) : Shape(renderer)
    {
        name = "Square";
    }

    virtual std::string str() const override {
        return std::string("Drawing Square as ")
        .append(renderer_->what_to_render_as());
    }
};

#include <iostream>

int main () {
    std::cout << Square{VectorRenderer{}}.str() << std::endl;

    return 0;
}

