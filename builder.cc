#include <iostream>
#include <sstream>
#include <memory>
#include <string>

class CodeBuilder;


struct Member {
    std::string member_name_;
    std::String member_type_;

    Member(const std::string& name, const std::string type): 
    member_name_(name), member_type_(type) {}
};

struct Class {
    std::string class_name_;
    std::vector<Member> members_;

    Class(const std::string& name): class_name_(name) {}

    static CodeBuilder create(const std::string& name) {
        return {name};
    }
};

class CodeBuilder {
    private:

    Class class_;

    std::string ClassNameStr() const {
        std::string class_name{"class"};
        class_name.append(" ").append(class_.class_name_);
    }

public:

    CodeBuilder(const std::string& class_name){
        class_{class_name};
    }

    CodeBuilder& add_field (const std::string& name, const std::string& type) {
        class_.members_.push_back({name, type});
        return *this;
    }

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj){

    }
};