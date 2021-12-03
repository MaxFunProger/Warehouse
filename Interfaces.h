#ifndef WAREHOUSE2_INTERFACES_H
#define WAREHOUSE2_INTERFACES_H

#pragma once

#include <fstream>
#include <vector>
#include <map>
#include <random>

class Delivery;
class ItemType;
class Item;

static std::random_device rd;
static std::mt19937 gen(rd());

class IUnit {
public:
    virtual void process() = 0;
};

class IGiver;

class IAsker : virtual public IUnit {
public:
    virtual void ask(IGiver*, std::vector<ItemType*>) = 0;
    virtual void add(Item item) = 0;
};

class IGiver : virtual public IUnit {
public:
    virtual void give(IAsker*) = 0;
    virtual void push(Delivery*) = 0;
};

#endif //WAREHOUSE2_INTERFACES_H
