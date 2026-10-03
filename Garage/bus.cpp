#include "Bus.h"

#include <stdexcept>

Bus::Bus()
    : Base(),
      seatingPlaces(0),
      totalPlaces(0),
      destination("Unknown")
{
    std::cout << "Bus: вызван конструктор без параметров" << std::endl;
}

Bus::Bus(
    const std::string& brand,
    const std::string& model,
    int seatingPlaces,
    int totalPlaces,
    const std::string& destination
)
    : Base(brand, model),
      seatingPlaces(seatingPlaces),
      totalPlaces(totalPlaces),
      destination(destination)
{
    if (seatingPlaces < 0)
    {
        throw std::invalid_argument(
            "Количество сидячих мест не может быть отрицательным."
        );
    }

    if (totalPlaces < 0)
    {
        throw std::invalid_argument(
            "Общее количество мест не может быть отрицательным."
        );
    }

    if (seatingPlaces > totalPlaces)
    {
        throw std::invalid_argument(
            "Количество сидячих мест не может быть больше общего количества мест."
        );
    }

    if (destination.empty())
    {
        throw std::invalid_argument(
            "Конечный пункт не может быть пустым."
        );
    }

    std::cout << "Bus: вызван конструктор с параметрами" << std::endl;
}

Bus::Bus(const Bus& other)
    : Base(other),
      seatingPlaces(other.seatingPlaces),
      totalPlaces(other.totalPlaces),
      destination(other.destination)
{
    std::cout << "Bus: вызван конструктор копирования" << std::endl;
}

Bus::~Bus()
{
    std::cout << "Bus: вызван деструктор" << std::endl;
}

Bus& Bus::operator=(const Bus& other)
{
    if (this != &other)
    {
        Base::operator=(other);

        seatingPlaces = other.seatingPlaces;
        totalPlaces = other.totalPlaces;
        destination = other.destination;
    }

    return *this;
}

void Bus::setSeatingPlaces(int seatingPlaces)
{
    if (seatingPlaces < 0)
    {
        throw std::invalid_argument(
            "Количество сидячих мест не может быть отрицательным."
        );
    }

    if (seatingPlaces > totalPlaces)
    {
        throw std::invalid_argument(
            "Количество сидячих мест не может быть больше общего количества мест."
        );
    }

    this->seatingPlaces = seatingPlaces;
}

void Bus::setTotalPlaces(int totalPlaces)
{
    if (totalPlaces < 0)
    {
        throw std::invalid_argument(
            "Общее количество мест не может быть отрицательным."
        );
    }

    if (totalPlaces < seatingPlaces)
    {
        throw std::invalid_argument(
            "Общее количество мест не может быть меньше количества сидячих мест."
        );
    }

    this->totalPlaces = totalPlaces;
}

void Bus::setDestination(const std::string& destination)
{
    if (destination.empty())
    {
        throw std::invalid_argument(
            "Конечный пункт не может быть пустым."
        );
    }

    this->destination = destination;
}

int Bus::getSeatingPlaces() const
{
    return seatingPlaces;
}

int Bus::getTotalPlaces() const
{
    return totalPlaces;
}

std::string Bus::getDestination() const
{
    return destination;
}

void Bus::print(std::ostream& out) const
{
    out << "Тип: Автобус\n";
    out << "Марка: " << getBrand() << '\n';
    out << "Модель: " << getModel() << '\n';
    out << "Количество сидячих мест: " << seatingPlaces << '\n';
    out << "Общее количество пассажирских мест: "
        << totalPlaces << '\n';
    out << "Конечный пункт: " << destination << '\n';
}

void Bus::save(std::ofstream& file) const
{
    file << "Bus\n";
    file << getBrand() << '\n';
    file << getModel() << '\n';
    file << totalPlaces << '\n';
    file << seatingPlaces << '\n';
    file << destination << '\n';
}

void Bus::load(std::ifstream& file)
{
    std::string value;

    std::getline(file, value);
    setBrand(value);

    std::getline(file, value);
    setModel(value);

    // Сначала общее количество мест.
    std::getline(file, value);
    int loadedTotalPlaces = std::stoi(value);

    // Затем количество сидячих мест.
    std::getline(file, value);
    int loadedSeatingPlaces = std::stoi(value);

    // Сначала устанавливаем общее количество.
    setTotalPlaces(loadedTotalPlaces);

    // После этого устанавливаем количество сидячих.
    setSeatingPlaces(loadedSeatingPlaces);

    std::getline(file, value);
    setDestination(value);
}

Base* Bus::clone() const
{
    return new Bus(*this);
}

std::string Bus::getType() const
{
    return "Bus";
}