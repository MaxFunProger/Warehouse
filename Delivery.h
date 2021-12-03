#ifndef WAREHOUSE2_DELIVERY_H
#define WAREHOUSE2_DELIVERY_H

#include "Item.h"

class Delivery {
public:
    Delivery(IAsker* from, std::map<ItemType, int>*);
    IAsker* from();
    std::map<ItemType, int>* count();
private:
    IAsker* from_;
    std::map<ItemType, int>* count_;
};


#endif //WAREHOUSE2_DELIVERY_H
