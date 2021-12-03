#ifndef WAREHOUSE2_GENERATOR_H
#define WAREHOUSE2_GENERATOR_H

#pragma once

#include "Delivery.h"
#include "Shop.h"
#include "Factory.h"
#include "Warehouse.h"
#include <iostream>

struct Item_Log {
    std::string name;
    int cnt, cnt_spoiled;
};

struct Factory_Item {
    std::string name;
    int cnt, days;
};

struct Logger {
    int money, lose_money, erase_items, cnt_spoiled_sold;
    std::vector<Item_Log> items;
    std::vector<Factory_Item> fac_items;
};

class Generator : public IUnit {
public:
    Generator(IUnit*, IGiver*, std::vector<IAsker*>, std::vector<ItemType*>);
    ~Generator();
    void process();
    Logger log();

private:
    IUnit *warehouse_;
    IGiver *factory_;
    std::vector<IAsker*> shops_;
    std::vector<ItemType*> items_;
};





#endif //WAREHOUSE2_GENERATOR_H
