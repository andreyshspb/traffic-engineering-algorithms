#include "adjustment.h"

#include <map>
#include <limits>


namespace TrafficEngineering {

    class AdjustmentHelper {
    public:
        AdjustmentHelper(const Network &network, std::vector<Tunnel> &tunnels)
                : network(network), tunnels(tunnels) {
            calculateSummaryTime();
            for (auto &tunnel: tunnels) {
                int sender = tunnel.getSenderSwitchId();
                adjustmentDfs(sender, tunnel);

                tunnel.setMinLatency(minLatency[sender]);
                tunnel.setMaxJitter(maxLatency[sender] - minLatency[sender]);
                tunnel.setPeriod(std::max(periodLowerBound[sender], tunnel.getPeriod()));

                minLatency.clear();
                maxLatency.clear();
                periodLowerBound.clear();
            }
        }

    private:
        const Network &network;
        std::vector<Tunnel> &tunnels;

        std::map<std::pair<int, int>, size_t> summaryTime;

        std::map<int, size_t> minLatency;
        std::map<int, size_t> maxLatency;
        std::map<int, size_t> periodLowerBound;

        void calculateSummaryTime() {
            for (const auto &tunnel: tunnels) {
                summaryTimeDfs(tunnel.getSenderSwitchId(), tunnel);
            }
        }

        void summaryTimeDfs(int curSwitchId, const Tunnel &tunnel) {
            for (auto next: tunnel.getNextSwitchIds(curSwitchId)) {
                summaryTime[{curSwitchId, next}] += tunnel.getPacketSize() / network.getBandwidth(curSwitchId, next);
                summaryTimeDfs(next, tunnel);
            }
        }

        void adjustmentDfs(int curSwitchId, const Tunnel &tunnel) {
            maxLatency[curSwitchId] = 0;
            minLatency[curSwitchId] = std::numeric_limits<size_t>::max();
            periodLowerBound[curSwitchId] = 0;
            for (auto next: tunnel.getNextSwitchIds(curSwitchId)) {
                adjustmentDfs(next, tunnel);
                relaxMaxLatency(curSwitchId, next, tunnel);
                relaxMinLatency(curSwitchId, next, tunnel);
                relaxPeriodLowerBound(curSwitchId, next, tunnel);
            }
            if (tunnel.isReceiver(curSwitchId)) {
                maxLatency[curSwitchId] = 0;
                minLatency[curSwitchId] = 0;
                periodLowerBound[curSwitchId] = 0;
            }
        }

        void relaxMaxLatency(int from, int to, const Tunnel &tunnel) {
            size_t curMaxLatency = 0;
            curMaxLatency += maxLatency[to];
            curMaxLatency += network.getMinDelay(from, to);
            curMaxLatency += network.getMaxJitter(from, to);
            curMaxLatency += summaryTime[{from, to}];
            maxLatency[from] = std::max(maxLatency[from], curMaxLatency);
        }

        void relaxMinLatency(int from, int to, const Tunnel &tunnel) {
            const auto transfer_time = tunnel.getPacketSize() / network.getBandwidth(from, to);
            size_t curMinLatency = 0;
            curMinLatency += minLatency[to];
            curMinLatency += network.getMinDelay(from, to);
            curMinLatency += transfer_time;
            minLatency[from] = std::min(minLatency[from], curMinLatency);
        }

        void relaxPeriodLowerBound(int from, int to, const Tunnel &tunnel) {
            const auto transfer_time = tunnel.getPacketSize() / network.getBandwidth(from, to);
            size_t curPeriod = 0;
            curPeriod += summaryTime[{from, to}] - transfer_time;
            curPeriod += std::max(transfer_time, periodLowerBound[to] + network.getMaxJitter(from, to));
            periodLowerBound[from] = std::max(periodLowerBound[from], curPeriod);
        }
    };

    void adjustment(const Network &network, std::vector<Tunnel> &tunnels) {
        AdjustmentHelper adjustmentAlgorithm(network, tunnels);
    }

} // namespace TrafficEngineering
