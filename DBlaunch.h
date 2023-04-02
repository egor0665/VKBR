#ifndef DBLAUNCH_H
#define DBLAUNCH_H

#include <QString>



class DBlaunch
{
public:
    DBlaunch();
    DBlaunch(int id, int booster_rocket_id, int upper_block_id, int spaceport_id, int price_year, const QString &prices, qreal launch_price, qreal delivery_price, qreal min_payload, qreal max_payload, bool valid);

    int id() const;
    int booster_rocket_id() const;
    int upper_block_id() const;
    int spaceport_id() const;
    int price_year() const;
    const QString &prices() const;
    qreal launch_price() const;
    qreal delivery_price() const;
    qreal min_payload() const;
    qreal max_payload() const;

    bool valid() const;

private:
int _id;
int _booster_rocket_id;
int _upper_block_id;
int _spaceport_id;
int _price_year;
QString _prices;
qreal _launch_price;
qreal _delivery_price;
qreal _min_payload;
qreal _max_payload;
bool _valid;

};

#endif // DBLAUNCH_H
