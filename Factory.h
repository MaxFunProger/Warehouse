#ifndef WAREHOUSE2_FACTORY_H
#define WAREHOUSE2_FACTORY_H

#pragma once

#include "Delivery.h"

struct FactoryLine {
    IAsker* from = nullptr;
    ItemType item;
    int time = 0;
    int count = 0;
};

class Factory : virtual public IGiver {
public:
    explicit Factory();
    ~Factory();
    void give(IAsker*);
    void process();
    void push(Delivery*);

    int get_money();
    std::vector<FactoryLine>& get_wait_list();

private:
    std::vector<FactoryLine> wait_list_;
    int money = 0;
};


#endif //WAREHOUSE2_FACTORY_H
