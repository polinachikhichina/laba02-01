#pragma once

#include "Base.h"

class Motorcycle : public Base
{
private:
    double engineVolume;
    double enginePower;
    std::string terrain;

public:
    Motorcycle();

    Motorcycle(
        const std::string& brand,
        const std::string& model,
        double engineVolume,
        double enginePower,
        const std::string& terrain
    );

    Motorcycle(const Motorcycle& other);

    ~Motorcycle() override;

    Motorcycle& operator=(const Motorcycle& other);

    void setEngineVolume(double engineVolume);
    void setEnginePower(double enginePower);
    void setTerrain(const std::string& terrain);

    double getEngineVolume() const;
    double getEnginePower() const;
    std::string getTerrain() const;

    void print(std::ostream& out) const override;

    void save(std::ofstream& file) const override;
    void load(std::ifstream& file) override;

    Base* clone() const override;

    std::string getType() const override;
};