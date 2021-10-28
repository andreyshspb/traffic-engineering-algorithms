#pragma once

#include <vector>
#include <unordered_map>


namespace TrafficEngineering {

    class Tunnel {
    public:
        int getSenderSwitchId() const;
        size_t getPacketSize() const;
        std::vector<int> getNextSwitchIds(int switchId);

        bool isReceiver(int switchId) const;

    private:
        int senderSwitchId;
        size_t packetSize;
        std::unordered_map<int, std::vector<int>> next;

    };

} // namespace TrafficEngineering
