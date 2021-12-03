#ifndef WAREHOUSE2_ITEM_H
#define WAREHOUSE2_ITEM_H

#pragma once

#include "Interfaces.h"

class ItemType {
public:
    ItemType(std::string, int, int, int, int, int, int, int, int);
    ItemType(const ItemType&);
    ItemType(ItemType&&) noexcept;
    bool operator<(ItemType other) const;
    ItemType& operator=(const ItemType& other);
    ~ItemType();

    int get_factory_price() const;
    int get_packs();
    int get_capacity();
    int get_price() const;
    std::string get_name() const;

protected:
    std::string name_;
    int capacity_;
    int days_;
    int days_critical_;
    int weight_;
    int packs_;
    int price_;
    int spoiled_price_;
    int price_factory_;
};

class Item : public ItemType {
public:
    Item(std::string, int, int, int, int, int, int, int, int);
    Item(ItemType);
    ~Item();

    int get_days_left();
    int get_start_price();
    bool is_spoiled();
    void new_day();

private:
    int start_price_;
    bool spoiled = 0;
    int days_left_;

};

#endif //WAREHOUSE2_ITEM_H
