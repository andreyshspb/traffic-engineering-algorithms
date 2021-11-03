#include "tunnel.h"


namespace TrafficEngineering {

    int Tunnel::getSenderSwitchId() const {
        return senderSwitchId;
    }

    size_t Tunnel::getPacketSize() const {
        return packetSize;
    }

    // TODO: return const std::vector<int>&
    std::vector<int> Tunnel::getNextSwitchIds(int switchId) const {
        return next.at(switchId);
    }

    // TODO: check the next case:
    //       the specified switch does not belong to the tunnel
    bool Tunnel::isReceiver(int switchId) const {
        return next.count(switchId) == 0;
    }

    size_t Tunnel::getMinLatency() const {
        return minLatency;
    }

    size_t Tunnel::getMaxJitter() const {
        return maxJitter;
    }

    size_t Tunnel::getPeriod() const {
        return period;
    }

    void Tunnel::setMinLatency(size_t newLatency) {
        minLatency = newLatency;
    }

    void Tunnel::setMaxJitter(size_t newJitter) {
        maxJitter = newJitter;
    }

    void Tunnel::setPeriod(size_t newPeriod) {
        period = newPeriod;
    }

} // namespace TrafficEngineering
