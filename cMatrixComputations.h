#pragma once

#include <QVector>
#include "cLine.h"

struct sMatrix
{
    sMatrix (int rowCount, int columnCount)
        : rowCount_(rowCount)
        , columnCount_(columnCount)
        , data_(rowCount_, QVector< double >(columnCount_, 0))
    {
    }

    int rowCount_;
    int columnCount_;
    QVector < QVector< double > > data_;
};


class cMatrixComputations
{
public:
    cMatrixComputations();

    static double getDetermination(const sMatrix & matrix) ;
    static double getDistance(const cLine & line1, const cLine & line2 );
    static double getDistanceBetweenParallelLines(const cLine & line1, const cLine & line2 );

};

