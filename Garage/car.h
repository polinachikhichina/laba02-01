#pragma once

#include "Base.h"

class Car : public Base
{
private:
    double engineVolume;
    std::string color;
    std::string gearboxType;

public:
    Car();

    Car(
        const std::string& brand,
        const std::string& model,
        double engineVolume,
        const std::string& color,
        const std::string& gearboxType
    );

    Car(const Car& other);

    ~Car() override;

    Car& operator=(const Car& other);

    void setEngineVolume(double engineVolume);
    void setColor(const std::string& color);
    void setGearboxType(const std::string& gearboxType);

    double getEngineVolume() const;
    std::string getColor() const;
    std::string getGearboxType() const;

    void print(std::ostream& out) const override;

    void save(std::ofstream& file) const override;
    void load(std::ifstream& file) override;

    Base* clone() const override;

    std::string getType() const override;
};