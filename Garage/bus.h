#pragma once

#include "Base.h"

class Bus : public Base
{
private:
    int seatingPlaces;
    int totalPlaces;
    std::string destination;

public:
    Bus();

    Bus(
        const std::string& brand,
        const std::string& model,
        int seatingPlaces,
        int totalPlaces,
        const std::string& destination
    );

    Bus(const Bus& other);

    ~Bus() override;

    Bus& operator=(const Bus& other);

    void setSeatingPlaces(int seatingPlaces);
    void setTotalPlaces(int totalPlaces);
    void setDestination(const std::string& destination);

    int getSeatingPlaces() const;
    int getTotalPlaces() const;
    std::string getDestination() const;

    void print(std::ostream& out) const override;

    void save(std::ofstream& file) const override;
    void load(std::ifstream& file) override;

    Base* clone() const override;

    std::string getType() const override;
};