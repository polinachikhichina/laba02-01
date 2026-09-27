#include "Motorcycle.h"

#include <stdexcept>

Motorcycle::Motorcycle()
    : Base(),
      engineVolume(0.0),
      enginePower(0.0),
      terrain("Unknown")
{
    std::cout << "Motorcycle: вызван конструктор без параметров" << std::endl;
}

Motorcycle::Motorcycle(
    const std::string& brand,
    const std::string& model,
    double engineVolume,
    double enginePower,
    const std::string& terrain
)
    : Base(brand, model),
      engineVolume(engineVolume),
      enginePower(enginePower),
      terrain(terrain)
{
    if (engineVolume < 0)
    {
        throw std::invalid_argument(
            "Объем двигателя не может быть отрицательным."
        );
    }

    if (enginePower < 0)
    {
        throw std::invalid_argument(
            "Мощность двигателя не может быть отрицательной."
        );
    }

    if (terrain.empty())
    {
        throw std::invalid_argument(
            "Предназначение не может быть пустым."
        );
    }

    std::cout << "Motorcycle: вызван конструктор с параметрами" << std::endl;
}

Motorcycle::Motorcycle(const Motorcycle& other)
    : Base(other),
      engineVolume(other.engineVolume),
      enginePower(other.enginePower),
      terrain(other.terrain)
{
    std::cout << "Motorcycle: вызван конструктор копирования" << std::endl;
}

Motorcycle::~Motorcycle()
{
    std::cout << "Motorcycle: вызван деструктор" << std::endl;
}

Motorcycle& Motorcycle::operator=(const Motorcycle& other)
{
    if (this != &other)
    {
        Base::operator=(other);

        engineVolume = other.engineVolume;
        enginePower = other.enginePower;
        terrain = other.terrain;
    }

    return *this;
}

void Motorcycle::setEngineVolume(double engineVolume)
{
    if (engineVolume < 0)
    {
        throw std::invalid_argument(
            "Объем двигателя не может быть отрицательным."
        );
    }

    this->engineVolume = engineVolume;
}

void Motorcycle::setEnginePower(double enginePower)
{
    if (enginePower < 0)
    {
        throw std::invalid_argument(
            "Мощность двигателя не может быть отрицательной."
        );
    }

    this->enginePower = enginePower;
}

void Motorcycle::setTerrain(const std::string& terrain)
{
    if (terrain.empty())
    {
        throw std::invalid_argument(
            "Предназначение не может быть пустым."
        );
    }

    this->terrain = terrain;
}

double Motorcycle::getEngineVolume() const
{
    return engineVolume;
}

double Motorcycle::getEnginePower() const
{
    return enginePower;
}

std::string Motorcycle::getTerrain() const
{
    return terrain;
}

void Motorcycle::print(std::ostream& out) const
{
    out << "Тип: Мотоцикл\n";
    out << "Марка: " << getBrand() << '\n';
    out << "Модель: " << getModel() << '\n';
    out << "Объем двигателя: " << engineVolume << " л\n";
    out << "Мощность двигателя: " << enginePower << " л.с.\n";
    out << "Предназначение: " << terrain << '\n';
}

void Motorcycle::save(std::ofstream& file) const
{
    file << "Motorcycle\n";
    file << getBrand() << '\n';
    file << getModel() << '\n';
    file << engineVolume << '\n';
    file << enginePower << '\n';
    file << terrain << '\n';
}

void Motorcycle::load(std::ifstream& file)
{
    std::string value;

    std::getline(file, value);
    setBrand(value);

    std::getline(file, value);
    setModel(value);

    std::getline(file, value);
    setEngineVolume(std::stod(value));

    std::getline(file, value);
    setEnginePower(std::stod(value));

    std::getline(file, value);
    setTerrain(value);
}

Base* Motorcycle::clone() const
{
    return new Motorcycle(*this);
}

std::string Motorcycle::getType() const
{
    return "Motorcycle";
}