#include <QCoreApplication>
#include "cPoint.h"
#include "cMatrixComputations.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QList<sPoint> pointList;
    for ( int i = 1; i < argc; i++ )
    {
        QString inputStr( argv[ i ] );
        inputStr.remove("--point" + QString::number(i)+"(");
        inputStr.remove(")");
        auto list = inputStr.split(",");

        sPoint p;
        p.x_ = list.at(0).toDouble();
        p.y_ = list.at(1).toDouble();
        p.z_ = list.at(2).toDouble();

        pointList.append(p);
    }

    if (pointList.count() < 4)
    {
        return 0;
    }

    cLine line(pointList.at(0), pointList.at(1));
    cLine line2( pointList.at(2), pointList.at(3));

    std::cout<< "Distance: "<< cMatrixComputations::getDistance(line, line2) << "\n";

    return 0;
}
