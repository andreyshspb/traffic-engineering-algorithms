#pragma once

#include "network.h"
#include "tunnel.h"

#include <vector>


namespace TrafficEngineering {

    struct AdjustmentResult {
        size_t min_latency = SIZE_MAX;
        size_t max_jitter = 0;
    };

    AdjustmentResult adjustment(const Network& network, const std::vector<Tunnel>& tunnels);

} // namespace TrafficEngineering
