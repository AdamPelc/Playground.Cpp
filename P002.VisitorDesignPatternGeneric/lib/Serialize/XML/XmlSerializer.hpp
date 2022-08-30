#pragma once
#ifndef PLAYGROUND_CPP_XMLSERIALIZER_HPP
#define PLAYGROUND_CPP_XMLSERIALIZER_HPP

#include "Serialize/Serializer.hpp"

class XmlSerializer : public Serializer {
    [[nodiscard]] std::string Serialize( const Cat& cat ) const override;
    [[nodiscard]] std::string Serialize( const Dog& dog ) const override;
    [[nodiscard]] std::string Serialize( const Parrot& parrot ) const override;
};

#endif// PLAYGROUND_CPP_XMLSERIALIZER_HPP
