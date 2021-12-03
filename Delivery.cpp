#include "Delivery.h"

Delivery::Delivery(IAsker *from, std::map<ItemType, int>* count)
: from_(from)
, count_(count) {}

IAsker* Delivery::from() {
    return from_;
}

std::map<ItemType, int>* Delivery::count() {
    return count_;
}
