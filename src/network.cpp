#include "network.h"


namespace TrafficEngineering {

    size_t Network::getSize() const {
        return size;
    }

    std::vector<int> Network::getNeighborsIds(int switchId) const {
        return neighbors.at(switchId);
    }

    size_t Network::getBandwidth(int fromSwitchId, int toSwitchId) const {
        return bandwidth.at({fromSwitchId, toSwitchId});
    }

    size_t Network::getQueueSize(int fromSwitchId, int toSwitchId) const {
        return queueSize.at({fromSwitchId, toSwitchId});
    }

    size_t Network::getMinDelay(int fromSwitchId, int toSwitchId) const {
        return minDelay.at({fromSwitchId, toSwitchId});
    }

    size_t Network::getMaxJitter(int fromSwitchId, int toSwitchId) const {
        return maxJitter.at({fromSwitchId, toSwitchId});
    }

}
