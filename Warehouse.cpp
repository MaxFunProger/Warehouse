#include "Warehouse.h"

Warehouse::Warehouse() = default;

Warehouse::~Warehouse(){
    for (std::map<IAsker*, std::map<ItemType, std::vector<Item>>>::iterator it = count_give_.begin();
         it != count_give_.end(); ++it){
        delete it->first;
    }

    for (std::map<ItemType, std::map<IAsker*, int>>::iterator it = count_ask_.begin(); it != count_ask_.end(); ++it){
        for (std::map<IAsker*, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            delete it2->first;
        }
    }


}

void Warehouse::process() {

    for (auto & type : storage_) {
        auto new_items = std::vector<Item>();
        for (auto & item : type.second) {
            item.new_day();
            if (item.get_days_left()) {
                new_items.push_back(item);
            } else {
                ++erase_items_;
                lose_money_ += item.get_start_price();
            }
        }
        type.second = new_items;
    }

    // Person

    count_give_ = std::map<IAsker*, std::map<ItemType, std::vector<Item>>>();
    count_ = std::map<ItemType, double>();

    for (auto & type : count_ask_) {

        bool ok = 1;
        while (ok) {
            ok = 0;

            for (auto & info : type.second) {
                auto shop = info.first;
                int cnt = info.second;

                if (!cnt || !(int)storage_[type.first].size()) break;
                ok = 1;

                //for (int i = 0; i < type.first.get_packs() && storage_[type.first].size(); ++i) {
                    count_give_[shop][type.first].push_back(*storage_[type.first].begin());
                    storage_[type.first].erase(storage_[type.first].begin());
                    ++count_[type.first];
                    --info.second;
                //}

            }

        }

    }


}

void Warehouse::ask(IGiver * to, std::vector<ItemType *> types) {
    for (auto & type : types) {
        if (!B_score_.count(*type)) B_score_[*type] = 0;
    }
    for (auto & info : B_score_) {
        info.second = 0.5 * info.second + 0.5 * count_[info.first];
    }

    auto* send = new std::map<ItemType, int>();

    for (auto & type : types) {
        int cnt = std::min(type->get_capacity(), std::max((int)B_score_[*type], (int)count_ask_[*type].size())) - storage_[*type].size();
        if (cnt <= 0) continue;

        (*send)[*type] += cnt;

    }
    auto delivery = new Delivery(this, send);
    if (delivery->count()->size())
        to->push(delivery);
}

void Warehouse::add(Item item) {
    storage_[static_cast<ItemType>(item)].push_back(item);
    if (storage_[static_cast<ItemType>(item)].size() > item.get_capacity()) {
        storage_[static_cast<ItemType>(item)].pop_back();
    }
}

void Warehouse::give(IAsker * other) {
    auto info = count_give_[other];
    for (auto & type : info) {
        for (auto & item : type.second) {
            lose_money_ += item.get_start_price() - item.get_price();
            other->add(item);
        }
    }
}

void Warehouse::push(Delivery * delivery) {
    for (auto & type : *delivery->count()) {
        count_ask_[type.first][delivery->from()] += type.second;
    }
}

bool Warehouse::is_spoiled(ItemType type) {
    for (auto & item : storage_[type]) {
        if (item.is_spoiled())
            return 1;
    }
    return 0;
}

int Warehouse::get_erase_items() {
    return erase_items_;
}

int Warehouse::get_lose_money() {
    return lose_money_;
}

std::map<ItemType, std::vector<Item>>& Warehouse::get_storage() {
    return storage_;
}
