#ifndef PLAYGROUND_CPP_VISITABLEANIMAL_HPP
#define PLAYGROUND_CPP_VISITABLEANIMAL_HPP

#include "AnimalVisitor.hpp"

class IVisitableAnimal {
public:
    virtual void Accept(AnimalVisitor& serializer) const = 0;
};

template <typename Derived>
class VisitableAnimal : public IVisitableAnimal {
public:
    void Accept(AnimalVisitor& serializer) const override {
        return serializer.Visit(*static_cast<const Derived*>(this));
    }
};

#endif  // PLAYGROUND_CPP_VISITABLEANIMAL_HPP
