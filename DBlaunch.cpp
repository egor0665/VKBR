#include "DBlaunch.h"

DBLaunch::DBLaunch()
{

}

int DBLaunch::id() const
{
    return _id;
}

int DBLaunch::booster_rocket_id() const
{
    return _booster_rocket_id;
}

int DBLaunch::upper_block_id() const
{
    return _upper_block_id;
}

int DBLaunch::spaceport_id() const
{
    return _spaceport_id;
}

int DBLaunch::price_year() const
{
    return _price_year;
}

const QString &DBLaunch::prices() const
{
    return _prices;
}


qreal DBLaunch::min_payload() const
{
    return _min_payload;
}

qreal DBLaunch::max_payload() const
{
    return _max_payload;
}

bool DBLaunch::valid() const
{
    return _valid;
}

qreal DBLaunch::launch_price() const
{
    return _launch_price;
}

qreal DBLaunch::delivery_price() const
{
    return _delivery_price;
}

DBLaunch::DBLaunch(int id, int booster_rocket_id, int upper_block_id, int spaceport_id, int price_year, const QString &prices, qreal launch_price, qreal delivery_price, qreal min_payload, qreal max_payload, bool valid) : _id(id),
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
