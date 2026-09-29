#include "Menu.h"

#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"

#include <iostream>
#include <string>

void Menu::run(Keeper& garage)
{
    int choice;

    do
    {
        std::cout << "\n========== ГАРАЖ ==========\n";
        std::cout << "1. Добавить автомобиль\n";
        std::cout << "2. Добавить мотоцикл\n";
        std::cout << "3. Добавить автобус\n";
        std::cout << "4. Показать все объекты\n";
        std::cout << "5. Изменить объект\n";
        std::cout << "6. Удалить объект\n";
        std::cout << "7. Сохранить в файл\n";
        std::cout << "8. Загрузить из файла\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";

        std::string choiceText;
        std::getline(std::cin, choiceText);

        try
        {
            choice = std::stoi(choiceText);
        }
        catch (...)
        {
            std::cout << "Ошибка: необходимо ввести номер пункта меню."
                      << std::endl;

            choice = -1;
            continue;
        }

        try
        {
            switch (choice)
            {
            case 1:
                addCar(garage);
                break;

            case 2:
                addMotorcycle(garage);
                break;

            case 3:
                addBus(garage);
                break;

            case 4:
                garage.printAll();
                break;

            case 5:
                changeObject(garage);
                break;

            case 6:
                deleteObject(garage);
                break;

            case 7:
            {
                std::string filename = inputFileName();

                garage.saveToFile(filename);

                std::cout << "Данные успешно сохранены."
                          << std::endl;

                break;
            }

            case 8:
            {
                std::string filename = inputFileName();

                garage.loadFromFile(filename);

                std::cout << "Данные успешно загружены."
                          << std::endl;

                break;
            }

            case 0:
                std::cout << "Выход из программы."
                          << std::endl;
                break;

            default:
                std::cout << "Такого пункта меню нет."
                          << std::endl;
            }
        }
        catch (const std::exception& error)
        {
            std::cout << "Ошибка: "
                      << error.what()
                      << std::endl;
        }

    } while (choice != 0);
}

std::string Menu::inputFileName()
{
    std::string filename;

    std::cout << "Введите имя файла: ";
    std::getline(std::cin, filename);

    if (filename.empty())
    {
        throw std::invalid_argument(
            "Имя файла не может быть пустым."
        );
    }

    return filename;
}

void Menu::addCar(Keeper& garage)
{
    std::string brand;
    std::string model;
    std::string color;
    std::string gearbox;
    double engineVolume;

    std::cout << "Марка: ";
    std::getline(std::cin, brand);

    std::cout << "Модель: ";
    std::getline(std::cin, model);

    std::cout << "Объем двигателя: ";

    std::string value;
    std::getline(std::cin, value);

    engineVolume = std::stod(value);

    std::cout << "Цвет: ";
    std::getline(std::cin, color);

    std::cout << "Тип КПП: ";
    std::getline(std::cin, gearbox);

    garage.add(
        new Car(
            brand,
            model,
            engineVolume,
            color,
            gearbox
        )
    );

    std::cout << "Автомобиль добавлен."
              << std::endl;
}

void Menu::addMotorcycle(Keeper& garage)
{
    std::string brand;
    std::string model;
    std::string terrain;

    double engineVolume;
    double enginePower;

    std::cout << "Марка: ";
    std::getline(std::cin, brand);

    std::cout << "Модель: ";
    std::getline(std::cin, model);

    std::cout << "Объем двигателя: ";

    std::string value;
    std::getline(std::cin, value);

    engineVolume = std::stod(value);

    std::cout << "Мощность двигателя: ";
    std::getline(std::cin, value);

    enginePower = std::stod(value);

    std::cout << "Для какой местности предназначен: ";
    std::getline(std::cin, terrain);

    garage.add(
        new Motorcycle(
            brand,
            model,
            engineVolume,
            enginePower,
            terrain
        )
    );

    std::cout << "Мотоцикл добавлен."
              << std::endl;
}

void Menu::addBus(Keeper& garage)
{
    std::string brand;
    std::string model;
    std::string destination;

    int seatingPlaces;
    int totalPlaces;

    std::cout << "Марка: ";
    std::getline(std::cin, brand);

    std::cout << "Модель: ";
    std::getline(std::cin, model);

    std::cout << "Количество сидячих мест: ";

    std::string value;
    std::getline(std::cin, value);

    seatingPlaces = std::stoi(value);

    std::cout << "Общее количество пассажирских мест: ";
    std::getline(std::cin, value);

    totalPlaces = std::stoi(value);

    std::cout << "Конечный пункт: ";
    std::getline(std::cin, destination);

    garage.add(
        new Bus(
            brand,
            model,
            seatingPlaces,
            totalPlaces,
            destination
        )
    );

    std::cout << "Автобус добавлен."
              << std::endl;
}

void Menu::deleteObject(Keeper& garage)
{
    if (garage.getSize() == 0)
    {
        std::cout << "Гараж пуст."
                  << std::endl;

        return;
    }

    garage.printAll();

    std::cout << "\nВведите номер объекта для удаления: ";

    std::string value;
    std::getline(std::cin, value);

    int number = std::stoi(value);

    garage.remove(number - 1);

    std::cout << "Объект удален."
              << std::endl;
}

void Menu::changeObject(Keeper& garage)
{
    if (garage.getSize() == 0)
    {
        std::cout << "Гараж пуст.\n";
        return;
    }

    garage.printAll();

    std::cout << "\nВыберите номер объекта для изменения: ";

    std::string input;
    std::getline(std::cin, input);

    int number = std::stoi(input);
    int index = number - 1;

    if (index < 0 || index >= garage.getSize())
    {
        throw std::out_of_range("Неверный номер объекта.");
    }

    Base* object = garage.getObject(index);

    std::cout << "\nЧто изменить?\n";

    if (object->getType() == "Car")
    {
        std::cout << "1. Марку\n";
        std::cout << "2. Модель\n";
        std::cout << "3. Объем двигателя\n";
        std::cout << "4. Цвет\n";
        std::cout << "5. Тип КПП\n";
        std::cout << "0. Отмена\n";
    }
    else if (object->getType() == "Motorcycle")
    {
        std::cout << "1. Марку\n";
        std::cout << "2. Модель\n";
        std::cout << "3. Объем двигателя\n";
        std::cout << "4. Мощность двигателя\n";
        std::cout << "5. Предназначение\n";
        std::cout << "0. Отмена\n";
    }
    else if (object->getType() == "Bus")
    {
        std::cout << "1. Марку\n";
        std::cout << "2. Модель\n";
        std::cout << "3. Количество сидячих мест\n";
        std::cout << "4. Общее количество пассажирских мест\n";
        std::cout << "5. Конечный пункт\n";
        std::cout << "0. Отмена\n";
    }

    std::cout << "Выберите действие: ";
    std::getline(std::cin, input);

    int choice = std::stoi(input);

    if (choice == 0)
    {
        std::cout << "Изменение отменено.\n";
        return;
    }

    std::string value;

    switch (choice)
    {
    case 1:
        std::cout << "Введите новую марку: ";
        std::getline(std::cin, value);

        object->setBrand(value);

        break;

    case 2:
        std::cout << "Введите новую модель: ";
        std::getline(std::cin, value);

        object->setModel(value);

        break;

    case 3:
        if (object->getType() == "Car")
        {
            Car* car = dynamic_cast<Car*>(object);

            std::cout << "Введите новый объем двигателя: ";
            std::getline(std::cin, value);

            car->setEngineVolume(std::stod(value));
        }
        else if (object->getType() == "Motorcycle")
        {
            Motorcycle* motorcycle =
                dynamic_cast<Motorcycle*>(object);

            std::cout << "Введите новый объем двигателя: ";
            std::getline(std::cin, value);

            motorcycle->setEngineVolume(std::stod(value));
        }
        else if (object->getType() == "Bus")
        {
            Bus* bus = dynamic_cast<Bus*>(object);

            std::cout << "Введите новое количество сидячих мест: ";
            std::getline(std::cin, value);

            bus->setSeatingPlaces(std::stoi(value));
        }

        break;

    case 4:
        if (object->getType() == "Car")
        {
            Car* car = dynamic_cast<Car*>(object);

            std::cout << "Введите новый цвет: ";
            std::getline(std::cin, value);

            car->setColor(value);
        }
        else if (object->getType() == "Motorcycle")
        {
            Motorcycle* motorcycle =
                dynamic_cast<Motorcycle*>(object);

            std::cout << "Введите новую мощность двигателя: ";
            std::getline(std::cin, value);

            motorcycle->setEnginePower(std::stod(value));
        }
        else if (object->getType() == "Bus")
        {
            Bus* bus = dynamic_cast<Bus*>(object);

            std::cout << "Введите новое общее количество пассажирских мест: ";
            std::getline(std::cin, value);

            bus->setTotalPlaces(std::stoi(value));
        }

        break;

    case 5:
        if (object->getType() == "Car")
        {
            Car* car = dynamic_cast<Car*>(object);

            std::cout << "Введите новый тип КПП: ";
            std::getline(std::cin, value);

            car->setGearboxType(value);
        }
        else if (object->getType() == "Motorcycle")
        {
            Motorcycle* motorcycle =
                dynamic_cast<Motorcycle*>(object);

            std::cout << "Введите новое предназначение: ";
            std::getline(std::cin, value);

            motorcycle->setTerrain(value);
        }
        else if (object->getType() == "Bus")
        {
            Bus* bus = dynamic_cast<Bus*>(object);

            std::cout << "Введите новый конечный пункт: ";
            std::getline(std::cin, value);

            bus->setDestination(value);
        }

        break;

    default:
        throw std::invalid_argument(
            "Неверный пункт меню."
        );
    }

    std::cout << "Данные объекта успешно изменены.\n";
}