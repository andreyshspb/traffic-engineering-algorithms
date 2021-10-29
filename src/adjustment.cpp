#include "adjustment.h"

#include <map>


namespace TrafficEngineering {

    std::map<int, size_t> minLatency;
    std::map<int, size_t> maxLatency;
    std::map<std::pair<int, int>, size_t> summaryTime;

    void summaryTimeDfs(int curSwitchId, const Tunnel& tunnel, const Network& network) {
        for (auto next : tunnel.getNextSwitchIds(curSwitchId)) {
            summaryTime[{curSwitchId, next}] += tunnel.getPacketSize() / network.getBandwidth(curSwitchId, next);
            summaryTimeDfs(next, tunnel, network);
        }
    }

    void calculateSummaryTime(const std::vector<Tunnel>& tunnels, const Network& network) {
        summaryTime.clear();
        for (const auto& tunnel : tunnels) {
            summaryTimeDfs(tunnel.getSenderSwitchId(), tunnel, network);
        }
    }

    void adjustmentDfs(int curSwitchId, const Tunnel& tunnel, const Network& network) {
        maxLatency[curSwitchId] = 0;
        minLatency[curSwitchId] = SIZE_MAX;
        for (auto next : tunnel.getNextSwitchIds(curSwitchId)) {
            adjustmentDfs(next, tunnel, network);

            size_t curMaxLatency = 0;
            curMaxLatency += maxLatency[next];
            curMaxLatency += network.getMinDelay(curSwitchId, next);
            curMaxLatency += network.getMaxJitter(curSwitchId, next);
            curMaxLatency += summaryTime[{curSwitchId, next}];
            maxLatency[curSwitchId] = std::max(maxLatency[curSwitchId], curMaxLatency);

            size_t curMinLatency = 0;
            curMinLatency += minLatency[next];
            curMinLatency += network.getMinDelay(curSwitchId, next);
            curMinLatency += tunnel.getPacketSize() / network.getBandwidth(curSwitchId, next);
            minLatency[curSwitchId] = std::max(minLatency[curSwitchId], curMinLatency);
        }

        if (tunnel.isReceiver(curSwitchId)) {
            maxLatency[curSwitchId] = 0;
            minLatency[curSwitchId] = 0;
        }
    }

    void adjustment(const Network& network, std::vector<Tunnel>& tunnels) {
        calculateSummaryTime(tunnels, network);

        for (auto& tunnel: tunnels) {
            minLatency.clear();
            maxLatency.clear();

            int sender = tunnel.getSenderSwitchId();
            adjustmentDfs(sender, tunnel, network);
            tunnel.setMinLatency(minLatency[sender]);
            tunnel.setMaxJitter(maxLatency[sender] - minLatency[sender]);
        }
    }

} // namespace TrafficEngineering
