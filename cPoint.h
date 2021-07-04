#pragma once
#include <QDebug>

struct sPoint
{
    sPoint(double x = 0.0, double y = 0.0, double z = 0.0)
        : x_ (x)
        , y_ (y)
        , z_ (z)
    {
    }

    double x_;
    double y_;
    double z_;
};
