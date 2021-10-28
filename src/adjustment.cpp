#include "adjustment.h"


namespace TrafficEngineering {

    std::vector<size_t> min_latency;
    std::vector<size_t> max_latency;

    void dfs(int curSwitchId, const Tunnel &tunnel) {}

    AdjustmentResult adjustment(const Network &network, const std::vector<Tunnel> &tunnels) {
        min_latency = std::vector<size_t>(network.getSize());
        max_latency = std::vector<size_t>(network.getSize());

        AdjustmentResult result;
        for (const auto &tunnel: tunnels) {
            int sender = tunnel.getSenderSwitchId();
            dfs(sender, tunnel);
            result.min_latency = std::min(result.min_latency, min_latency[sender]);
            result.max_jitter = std::min(result.max_jitter, max_latency[sender]) -min_latency[sender];
        }

        return result;
    }

} // namespace TrafficEngineering
