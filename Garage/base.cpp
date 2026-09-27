#include "Base.h"

#include <stdexcept>

Base::Base()
    : brand("Unknown"), model("Unknown")
{
    std::cout << "Base: вызван конструктор без параметров" << std::endl;
}

Base::Base(const std::string& brand, const std::string& model)
    : brand(brand), model(model)
{
    std::cout << "Base: вызван конструктор с параметрами" << std::endl;
}

Base::Base(const Base& other)
    : brand(other.brand), model(other.model)
{
    std::cout << "Base: вызван конструктор копирования" << std::endl;
}

Base::~Base()
{
    std::cout << "Base: вызван деструктор" << std::endl;
}

Base& Base::operator=(const Base& other)
{
    if (this != &other)
    {
        brand = other.brand;
        model = other.model;
    }

    return *this;
}

void Base::setBrand(const std::string& brand)
{
    if (brand.empty())
    {
        throw std::invalid_argument("Марка не может быть пустой.");
    }

    this->brand = brand;
}

void Base::setModel(const std::string& model)
{
    if (model.empty())
    {
        throw std::invalid_argument("Модель не может быть пустой.");
    }

    this->model = model;
}

std::string Base::getBrand() const
{
    return brand;
}

std::string Base::getModel() const
{
    return model;
}

std::ostream& operator<<(std::ostream& out, const Base& object)
{
    object.print(out);
    return out;
}