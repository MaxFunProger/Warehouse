#include "Factory.h"

Factory::Factory() {
    wait_list_ = std::vector<FactoryLine>();
}

Factory::~Factory() = default;

void Factory::give(IAsker* other) {
    auto next_iter = std::vector<FactoryLine>();
    for (auto & element : wait_list_) {
        if (element.time) {
            next_iter.push_back(element);
        } else {
            for (int i = 0; i < element.count; ++i) {
                other->add(Item(element.item));
            }
        }
    }
    wait_list_ = next_iter;

}

void Factory::process() {
    for (auto & element : wait_list_) {
        --element.time;
    }
}

void Factory::push(Delivery* delivery) {
    std::uniform_int_distribution<int> dis(1, 5);
    for (auto & item : *delivery->count()) {
        wait_list_.push_back({delivery->from(), item.first, dis(gen), item.second});
        money += item.first.get_factory_price() * item.second;
    }
}

int Factory::get_money() {
    return money;
}

std::vector<FactoryLine> &Factory::get_wait_list() {
    return wait_list_;
}
