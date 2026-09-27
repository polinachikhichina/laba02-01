#pragma once

#include <iostream>
#include <fstream>
#include <string>

class Base
{
private:
    std::string brand;
    std::string model;

public:
    Base();
    Base(const std::string& brand, const std::string& model);
    Base(const Base& other);
    virtual ~Base();

    Base& operator=(const Base& other);

    void setBrand(const std::string& brand);
    void setModel(const std::string& model);

    std::string getBrand() const;
    std::string getModel() const;

    virtual void print(std::ostream& out) const = 0;
    virtual void save(std::ofstream& file) const = 0;
    virtual void load(std::ifstream& file) = 0;
    virtual Base* clone() const = 0;
    virtual std::string getType() const = 0;
};

std::ostream& operator<<(std::ostream& out, const Base& object);