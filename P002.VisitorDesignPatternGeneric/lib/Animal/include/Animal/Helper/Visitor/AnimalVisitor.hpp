#ifndef PLAYGROUND_CPP_ANIMAL_VISITOR_HPP
#define PLAYGROUND_CPP_ANIMAL_VISITOR_HPP

#include "Animal/Helper/Visitor/Visitor.hpp"

using AnimalVisitor = Visitor<class Dog, class Cat, class Parrot>;

#endif// PLAYGROUND_CPP_ANIMAL_VISITOR_HPP
