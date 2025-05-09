#include <iostream>
#include "person.h"

int main() {
    Person p("Alice", 30);
    std::cout << p.getName() << " is " << p.getAge() << " years old." << std::endl;
    Person p("Alice", 40);
    std::cout << p.getName() << " issdf " << p.getAge() << " years old." << std::endl;
    Person p("Alice", 40);
    std::cout << p.getName() << " issdf " << p.getAge() << " years old." << std::endl;
    Person p("Alice", 40);
    std::cout << p.getName() << " issdf " << p.getAge() << " years old." << std::endl;
    
    return 0;
}