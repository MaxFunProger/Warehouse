#include "Item.h"

ItemType::ItemType(std::string name, int capacity, int days, int days_critical,
                   int weight, int packs, int price, int spoiled_price, int price_factory)
        : name_(name)
        , capacity_(capacity)
        , days_(days)
        , days_critical_(days_critical)
        , weight_(weight)
        , packs_(packs)
        , price_(price)
        , spoiled_price_(spoiled_price)
        , price_factory_(price_factory) {}


ItemType::ItemType(const ItemType & other) = default;

ItemType::ItemType(ItemType && other) noexcept
        : name_(other.name_)
        , capacity_(other.capacity_)
        , days_(other.days_)
        , days_critical_(other.days_critical_)
        , weight_(other.weight_)
        , packs_(other.packs_)
        , price_(other.price_)
        , spoiled_price_(other.spoiled_price_)
        , price_factory_(other.price_factory_) {}

ItemType::~ItemType() = default;

bool ItemType::operator<(ItemType other) const {
    return name_ < other.name_;
}

ItemType& ItemType::operator=(const ItemType& other) {
    name_ = other.name_;
    capacity_ = other.capacity_;
    days_ = other.days_;
    days_critical_ = other.days_critical_;
    weight_ = other.weight_;
    packs_ = other.packs_;
    price_ = other.price_;
    spoiled_price_ = other.spoiled_price_;
    price_factory_ = other.price_factory_;
    return *this;
}

int ItemType::get_factory_price() const {
    return price_factory_;
}

int ItemType::get_packs() {
    return packs_;
}

int ItemType::get_capacity() {
    return capacity_;
}

int ItemType::get_price() const {
    return price_;
}

std::string ItemType::get_name() const{
    return name_;
}

Item::Item(std::string name, int capacity, int days, int days_critical,
           int weight, int packs, int price, int spoiled_price, int price_factory)
: ItemType(name, capacity, days, days_critical, weight, packs, price, spoiled_price, price_factory)
, days_left_(days_)
, start_price_(price_) {}

Item::Item(ItemType item)
: ItemType(item)
, days_left_(days_)
, start_price_(price_) {}

Item::~Item() = default;

bool Item::is_spoiled() {
    return spoiled;
}

int Item::get_days_left() {
    return days_left_;
}

int Item::get_start_price() {
    return start_price_;
}

void Item::new_day() {
    --days_left_;
    if (days_left_ <= days_critical_) {
        price_ = spoiled_price_;
        spoiled = 1;
    }
}
