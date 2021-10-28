#pragma once

#include <vector>
#include <map>


namespace TrafficEngineering {

    class Network {
    public:
        size_t getSize() const;
        std::vector<int> getNeighborsIds(int switchId);
        size_t getBandwidth(int fromSwitchId, int toSwitchId);
        size_t getQueueSize(int fromSwitchId, int toSwitchId);

    private:
        size_t size;
        std::map<int, std::vector<int>> neighbors;
        std::map<std::pair<int, int>, size_t> bandwidth;
        std::map<std::pair<int, int>, size_t> queue_size;

    };

} // namespace TrafficEngineering
