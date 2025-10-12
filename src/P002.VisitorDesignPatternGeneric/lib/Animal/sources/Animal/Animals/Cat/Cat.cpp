#include "Animal/Animals/Cat/Cat.hpp"

Cat::Cat(std::string_view name, std::size_t age) : name(name), age(age) {}

std::string Cat::GetName() const { return {name}; }

std::size_t Cat::GetAge() const { return age; }
