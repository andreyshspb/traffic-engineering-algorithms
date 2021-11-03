#pragma once

#include <vector>
#include <map>


namespace TrafficEngineering {

    class Network {
    public:
        size_t getSize() const;
        std::vector<int> getNeighborsIds(int switchId) const;
        size_t getBandwidth(int fromSwitchId, int toSwitchId) const;
        size_t getQueueSize(int fromSwitchId, int toSwitchId) const;
        size_t getMinDelay(int fromSwitchId, int toSwitchId) const;
        size_t getMaxJitter(int fromSwitchId, int toSwitchId) const;

    private:
        size_t size;
        std::map<int, std::vector<int>> neighbors;
        std::map<std::pair<int, int>, size_t> bandwidth;
        std::map<std::pair<int, int>, size_t> queueSize;
        std::map<std::pair<int, int>, size_t> minDelay;
        std::map<std::pair<int, int>, size_t> maxJitter;

    };

} // namespace TrafficEngineering
