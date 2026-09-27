#pragma once

#include "Base.h"

class Keeper
{
private:
    Base** objects;
    int size;
    int capacity;

    void resize();

public:
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);

    void add(Base* object);
    void remove(int index);
    void clear();

    int getSize() const;
    Base* getObject(int index) const;

    void printAll() const;
    void changeObject(int index);

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};