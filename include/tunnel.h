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

        size_t getMinLatency() const;
        size_t getMaxJitter() const;
        size_t getPeriod() const;

        void setMinLatency(size_t newLatency);
        void setMaxJitter(size_t newJitter);
        void setPeriod(size_t newPeriod);

    private:
        int senderSwitchId;
        size_t packetSize;
        std::unordered_map<int, std::vector<int>> next;

        size_t minLatency;
        size_t maxJitter;
        size_t period;

    };

} // namespace TrafficEngineering
