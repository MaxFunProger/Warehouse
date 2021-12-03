#ifndef WAREHOUSE2_SHOP_H
#define WAREHOUSE2_SHOP_H

#pragma once

#include "Warehouse.h"

class Shop : virtual public IAsker {
public:
    Shop();
    ~Shop();

    void process();
    void ask(IGiver* to, std::vector<ItemType*>) override;
    void add(Item);

    int get_money();
    int get_count_spoiled();

private:
    int money = 0, count_spoiled = 0;
    std::uniform_int_distribution<int> dis;
};


#endif //WAREHOUSE2_SHOP_H
