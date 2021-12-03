#include "Shop.h"

void Shop::ask(IGiver* to, std::vector<ItemType*> items) {
    auto* send = new std::map<ItemType, int>();
    for (auto & item : items) {
        if (dis(gen) % 4 <= dynamic_cast<Warehouse*>(to)->is_spoiled(*item)) {
            (*send)[*item] = (dis(gen) % 10 + 1 + item->get_packs() - 1) / item->get_packs();
        }
    }
    auto delivery = new Delivery(this, send);
    to->push(delivery);
}

Shop::Shop() {
    dis = std::uniform_int_distribution<int>(1, 1000);
}

Shop::~Shop() = default;


void Shop::add(Item item) {
    if (item.is_spoiled()) {
        ++count_spoiled;
    }
    money += item.get_price();
}

void Shop::process() {}

int Shop::get_count_spoiled() {
    return count_spoiled;
}

int Shop::get_money() {
    return money;
}
