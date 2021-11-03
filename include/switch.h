#pragma once


namespace TrafficEngineering {

    class Switch {
    public:
        explicit Switch(int id) : id(id) {}

        int getId() const;

    private:
        int id;

    };

} // namespace TrafficEngineering
