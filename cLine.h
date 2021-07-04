#pragma once

#include "cPoint.h"
#include <QList>
#include <QDebug>

struct sGuideVector
{
    sGuideVector(double x = 0.0, double y = 0.0, double z = 0.0)
        : x_ (x)
        , y_ (y)
        , z_ (z)
    {

    }

    sGuideVector(const sPoint &point1, const sPoint & point2)
        : x_ (point2.x_ - point1.x_)
        , y_ (point2.y_ - point1.y_)
        , z_ (point2.z_ - point1.z_)
    {
    }

    double module() const
    {
        return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    double x_;
    double y_;
    double z_;
};

class cLine
{
public:
    cLine(const sPoint & point1 , const sPoint & point2 );

    QList <sPoint> pointOnLine_;
    sGuideVector guideVector_;
};

