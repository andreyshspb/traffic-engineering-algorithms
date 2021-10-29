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

    void Tunnel::setMinLatency(size_t latency) {
        minLatency = latency;
    }

    void Tunnel::setMaxJitter(size_t jitter) {
        maxJitter = jitter;
    }

} // namespace TrafficEngineering
