#pragma once

#include <vector>
#include <unordered_map>


namespace TrafficEngineering {

    class Tunnel {
    public:
        int getSenderSwitchId() const;
        size_t getPacketSize() const;
        std::vector<int> getNextSwitchIds(int switchId) const;

        bool isReceiver(int switchId) const;

        void setMinLatency(size_t latency);
        void setMaxJitter(size_t jitter);

    private:
        int senderSwitchId;
        size_t packetSize;
        std::unordered_map<int, std::vector<int>> next;

        size_t minLatency;
        size_t maxJitter;

    };

} // namespace TrafficEngineering
