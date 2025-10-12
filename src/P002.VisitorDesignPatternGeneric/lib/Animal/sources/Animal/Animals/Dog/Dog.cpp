#include "Animal/Animals/Dog/Dog.hpp"

Dog::Dog(std::string_view name, std::size_t age) : name(name), age(age) {};

std::string Dog::GetName() const { return {name}; }

std::size_t Dog::GetAge() const { return age; }
