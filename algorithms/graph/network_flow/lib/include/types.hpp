#pragma once

#include "helper/named_type.hpp"

using node_t = int;
using source_node_t = named_type_t<node_t, struct source_node_parameter_t>;
using destination_node_t = named_type_t<node_t, struct destination_node_parameter_t>;

using capacity_t = named_type_t<int, struct capacity_parameter_t>;
using flow_t = named_type_t<int, struct flow_parameter_t>;
