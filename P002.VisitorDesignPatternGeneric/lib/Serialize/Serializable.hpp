#pragma once
#ifndef PLAYGROUND_CPP_SERIALIZABLE_HPP
#define PLAYGROUND_CPP_SERIALIZABLE_HPP

#include "Serializer.hpp"

#include <string>

class ISerializable {
public:
    [[nodiscard]] virtual std::string Serialize( const Serializer& serializer ) const = 0;
};

template<typename Derived>
class Serializable : public ISerializable {
public:
    [[nodiscard]] std::string Serialize( const Serializer& serializer ) const override {
        return serializer.Serialize( *static_cast<const Derived *>( this ) );
    }
};

#endif// PLAYGROUND_CPP_SERIALIZABLE_HPP
