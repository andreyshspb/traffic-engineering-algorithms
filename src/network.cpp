#include "network.h"


namespace TrafficEngineering {

    size_t Network::getSize() const {
        return size;
    }

    std::vector<int> Network::getNeighborsIds(int switchId) {
        return neighbors[switchId];
    }

    size_t Network::getBandwidth(int fromSwitchId, int toSwitchId) {
        return bandwidth[{fromSwitchId, toSwitchId}];
    }

    size_t Network::getQueueSize(int fromSwitchId, int toSwitchId) {
        return queue_size[{fromSwitchId, toSwitchId}];
    }

}
