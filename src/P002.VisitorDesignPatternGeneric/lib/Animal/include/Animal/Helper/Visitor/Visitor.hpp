#ifndef PLAYGROUND_CPP_VISITOR_HPP
#define PLAYGROUND_CPP_VISITOR_HPP

template <typename... Types>
class Visitor;

template <typename T>
class Visitor<T> {
public:
    virtual void Visit(const T& obj) = 0;
};

template <typename T, typename... Types>
class Visitor<T, Types...> : public Visitor<Types...> {
public:
    using Visitor<Types...>::Visit;
    virtual void Visit(const T& obj) = 0;
};

#endif  // PLAYGROUND_CPP_VISITOR_HPP
