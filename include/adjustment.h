#pragma once

#include "network.h"
#include "tunnel.h"

#include <vector>


namespace TrafficEngineering {

    void adjustment(const Network& network, std::vector<Tunnel>& tunnels);

} // namespace TrafficEngineering
