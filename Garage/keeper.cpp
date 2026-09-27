#include "Keeper.h"

#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

Keeper::Keeper()
    : objects(nullptr),
      size(0),
      capacity(2)
{
    objects = new Base*[capacity];

    for (int i = 0; i < capacity; ++i)
    {
        objects[i] = nullptr;
    }

    std::cout << "Keeper: вызван конструктор без параметров" << std::endl;
}

Keeper::Keeper(const Keeper& other)
    : objects(nullptr),
      size(0),
      capacity(other.capacity)
{
    objects = new Base*[capacity];

    for (int i = 0; i < capacity; ++i)
    {
        objects[i] = nullptr;
    }

    for (int i = 0; i < other.size; ++i)
    {
        add(other.objects[i]->clone());
    }

    std::cout << "Keeper: вызван конструктор копирования" << std::endl;
}

Keeper::~Keeper()
{
    clear();

    delete[] objects;

    std::cout << "Keeper: вызван деструктор" << std::endl;
}

Keeper& Keeper::operator=(const Keeper& other)
{
    if (this != &other)
    {
        clear();

        delete[] objects;

        capacity = other.capacity;

        objects = new Base*[capacity];

        for (int i = 0; i < capacity; ++i)
        {
            objects[i] = nullptr;
        }

        for (int i = 0; i < other.size; ++i)
        {
            add(other.objects[i]->clone());
        }
    }

    return *this;
}

void Keeper::resize()
{
    int newCapacity = capacity * 2;

    Base** newObjects = new Base*[newCapacity];

    for (int i = 0; i < newCapacity; ++i)
    {
        newObjects[i] = nullptr;
    }

    for (int i = 0; i < size; ++i)
    {
        newObjects[i] = objects[i];
    }

    delete[] objects;

    objects = newObjects;
    capacity = newCapacity;
}

void Keeper::add(Base* object)
{
    if (object == nullptr)
    {
        throw std::invalid_argument(
            "Нельзя добавить пустой объект."
        );
    }

    if (size >= capacity)
    {
        resize();
    }

    objects[size] = object;
    ++size;
}

void Keeper::remove(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range(
            "Неверный индекс объекта."
        );
    }

    delete objects[index];

    for (int i = index; i < size - 1; ++i)
    {
        objects[i] = objects[i + 1];
    }

    objects[size - 1] = nullptr;

    --size;
}

void Keeper::clear()
{
    for (int i = 0; i < size; ++i)
    {
        delete objects[i];
        objects[i] = nullptr;
    }

    size = 0;
}

int Keeper::getSize() const
{
    return size;
}

Base* Keeper::getObject(int index) const
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range(
            "Неверный индекс объекта."
        );
    }

    return objects[index];
}

void Keeper::printAll() const
{
    if (size == 0)
    {
        std::cout << "Гараж пуст." << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i)
    {
        std::cout << "\n===== Объект #" << i + 1
                  << " =====\n";

        std::cout << *objects[i];
    }
}

void Keeper::changeObject(int index)
{
    if (index < 0 || index >= size)
    {
        throw std::out_of_range(
            "Неверный индекс объекта."
        );
    }

    Base* object = objects[index];

    std::string value;

    std::cout << "Новая марка: ";
    std::getline(std::cin, value);
    object->setBrand(value);

    std::cout << "Новая модель: ";
    std::getline(std::cin, value);
    object->setModel(value);

    if (Car* car = dynamic_cast<Car*>(object))
    {
        std::cout << "Новый объем двигателя: ";
        std::getline(std::cin, value);
        car->setEngineVolume(std::stod(value));

        std::cout << "Новый цвет: ";
        std::getline(std::cin, value);
        car->setColor(value);

        std::cout << "Новый тип КПП: ";
        std::getline(std::cin, value);
        car->setGearboxType(value);
    }
    else if (Motorcycle* motorcycle =
                 dynamic_cast<Motorcycle*>(object))
    {
        std::cout << "Новый объем двигателя: ";
        std::getline(std::cin, value);
        motorcycle->setEngineVolume(std::stod(value));

        std::cout << "Новая мощность двигателя: ";
        std::getline(std::cin, value);
        motorcycle->setEnginePower(std::stod(value));

        std::cout << "Новое предназначение: ";
        std::getline(std::cin, value);
        motorcycle->setTerrain(value);
    }
    else if (Bus* bus = dynamic_cast<Bus*>(object))
    {
        // Сначала меняем общее количество мест.
        std::cout << "Новое общее количество мест: ";
        std::getline(std::cin, value);
        int newTotalPlaces = std::stoi(value);

        bus->setTotalPlaces(newTotalPlaces);

        // После этого меняем количество сидячих мест.
        std::cout << "Новое количество сидячих мест: ";
        std::getline(std::cin, value);
        int newSeatingPlaces = std::stoi(value);

        bus->setSeatingPlaces(newSeatingPlaces);

        std::cout << "Новый конечный пункт: ";
        std::getline(std::cin, value);
        bus->setDestination(value);
    }
}

void Keeper::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Не удалось открыть файл для сохранения."
        );
    }

    file << size << '\n';

    for (int i = 0; i < size; ++i)
    {
        objects[i]->save(file);
    }

    file.close();
}

void Keeper::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error(
            "Не удалось открыть файл для загрузки."
        );
    }

    clear();

    int count;

    if (!(file >> count))
    {
        throw std::runtime_error(
            "Ошибка чтения количества объектов."
        );
    }

    file.ignore(10000, '\n');

    for (int i = 0; i < count; ++i)
    {
        std::string type;

        std::getline(file, type);

        Base* object = nullptr;

        if (type == "Car")
        {
            object = new Car();
        }
        else if (type == "Motorcycle")
        {
            object = new Motorcycle();
        }
        else if (type == "Bus")
        {
            object = new Bus();
        }
        else
        {
            throw std::runtime_error(
                "Неизвестный тип объекта в файле."
            );
        }

        try
        {
            object->load(file);
            add(object);
        }
        catch (...)
        {
            delete object;
            throw;
        }
    }

    file.close();
}