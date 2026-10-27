/**
 * @author alvaro.zurinaga
 * @brief Implement the component base supplied with the assignment
 */

#include <iostream>
#include "component.hh"


Component::Component(const char* name) {
    this->name = name;
}

const char* Component::getName() {
    return this->name;
}

Entity* Component::getOwner() {
    return mOwner;
}

void Component::setOwner(Entity* owner) {
    mOwner = owner;
}

