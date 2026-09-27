#include "Car.h"

#include <stdexcept>

Car::Car()
    : Base(),
      engineVolume(0.0),
      color("Unknown"),
      gearboxType("Unknown")
{
    std::cout << "Car: вызван конструктор без параметров" << std::endl;
}

Car::Car(
    const std::string& brand,
    const std::string& model,
    double engineVolume,
    const std::string& color,
    const std::string& gearboxType
)
    : Base(brand, model),
      engineVolume(engineVolume),
      color(color),
      gearboxType(gearboxType)
{
    if (engineVolume < 0)
    {
        throw std::invalid_argument(
            "Объем двигателя не может быть отрицательным."
        );
    }

    if (color.empty())
    {
        throw std::invalid_argument(
            "Цвет не может быть пустым."
        );
    }

    if (gearboxType.empty())
    {
        throw std::invalid_argument(
            "Тип КПП не может быть пустым."
        );
    }

    std::cout << "Car: вызван конструктор с параметрами" << std::endl;
}

Car::Car(const Car& other)
    : Base(other),
      engineVolume(other.engineVolume),
      color(other.color),
      gearboxType(other.gearboxType)
{
    std::cout << "Car: вызван конструктор копирования" << std::endl;
}

Car::~Car()
{
    std::cout << "Car: вызван деструктор" << std::endl;
}

Car& Car::operator=(const Car& other)
{
    if (this != &other)
    {
        Base::operator=(other);

        engineVolume = other.engineVolume;
        color = other.color;
        gearboxType = other.gearboxType;
    }

    return *this;
}

void Car::setEngineVolume(double engineVolume)
{
    if (engineVolume < 0)
    {
        throw std::invalid_argument(
            "Объем двигателя не может быть отрицательным."
        );
    }

    this->engineVolume = engineVolume;
}

void Car::setColor(const std::string& color)
{
    if (color.empty())
    {
        throw std::invalid_argument(
            "Цвет не может быть пустым."
        );
    }

    this->color = color;
}

void Car::setGearboxType(const std::string& gearboxType)
{
    if (gearboxType.empty())
    {
        throw std::invalid_argument(
            "Тип КПП не может быть пустым."
        );
    }

    this->gearboxType = gearboxType;
}

double Car::getEngineVolume() const
{
    return engineVolume;
}

std::string Car::getColor() const
{
    return color;
}

std::string Car::getGearboxType() const
{
    return gearboxType;
}

void Car::print(std::ostream& out) const
{
    out << "Тип: Автомобиль\n";
    out << "Марка: " << getBrand() << '\n';
    out << "Модель: " << getModel() << '\n';
    out << "Объем двигателя: " << engineVolume << " л\n";
    out << "Цвет: " << color << '\n';
    out << "Тип КПП: " << gearboxType << '\n';
}

void Car::save(std::ofstream& file) const
{
    file << "Car\n";
    file << getBrand() << '\n';
    file << getModel() << '\n';
    file << engineVolume << '\n';
    file << color << '\n';
    file << gearboxType << '\n';
}

void Car::load(std::ifstream& file)
{
    std::string value;

    std::getline(file, value);
    setBrand(value);

    std::getline(file, value);
    setModel(value);

    std::getline(file, value);
    setEngineVolume(std::stod(value));

    std::getline(file, value);
    setColor(value);

    std::getline(file, value);
    setGearboxType(value);
}

Base* Car::clone() const
{
    return new Car(*this);
}

std::string Car::getType() const
{
    return "Car";
}