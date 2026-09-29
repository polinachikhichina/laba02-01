#pragma once

#include "Keeper.h"

class Menu
{
public:
    static void run(Keeper& garage);

private:
    static void addCar(Keeper& garage);
    static void addMotorcycle(Keeper& garage);
    static void addBus(Keeper& garage);

    static void deleteObject(Keeper& garage);
    static void changeObject(Keeper& garage);

    static std::string inputFileName();
};