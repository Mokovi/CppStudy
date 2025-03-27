#include "compositePattern.h"

void Directory::display(int indent) const {
    std::cout << std::string(indent, ' ') << "📁 " << name << std::endl;
    for (const auto& child : children) {
        child->display(indent + 2);
    }
}

void File::display(int indent) const{
    std::cout << std::string(indent, ' ') << "📄 " << name << std::endl;
}