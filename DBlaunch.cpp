#include "DBlaunch.h"

DBlaunch::DBlaunch()
{

}

int DBlaunch::id() const
{
    return _id;
}

int DBlaunch::booster_rocket_id() const
{
    return _booster_rocket_id;
}

int DBlaunch::upper_block_id() const
{
    return _upper_block_id;
}

int DBlaunch::spaceport_id() const
{
    return _spaceport_id;
}

int DBlaunch::price_year() const
{
    return _price_year;
}

const QString &DBlaunch::prices() const
{
    return _prices;
}


qreal DBlaunch::min_payload() const
{
    return _min_payload;
}

qreal DBlaunch::max_payload() const
{
    return _max_payload;
}

bool DBlaunch::valid() const
{
    return _valid;
}

qreal DBlaunch::launch_price() const
{
    return _launch_price;
}

qreal DBlaunch::delivery_price() const
{
    return _delivery_price;
}

DBlaunch::DBlaunch(int id, int booster_rocket_id, int upper_block_id, int spaceport_id, int price_year, const QString &prices, qreal launch_price, qreal delivery_price, qreal min_payload, qreal max_payload, bool valid) : _id(id),
    _booster_rocket_id(booster_rocket_id),
    _upper_block_id(upper_block_id),
    _spaceport_id(spaceport_id),
    _price_year(price_year),
    _prices(prices),
    _launch_price(std::move(launch_price)),
    _delivery_price(std::move(delivery_price)),
    _min_payload(std::move(min_payload)),
    _max_payload(std::move(max_payload)),
    _valid(valid)
{}
