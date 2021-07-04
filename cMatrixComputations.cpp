#include "cMatrixComputations.h"
#include <QDebug>

cMatrixComputations::cMatrixComputations()
{
}

double cMatrixComputations::getDetermination(const sMatrix & matrix)
{
    if (matrix.columnCount_ != matrix.rowCount_)
    {
        printf("Wrong matrix size \n");
        return -1;
    }

    double det = 0;
    int size = matrix.columnCount_;

    if( size == 1 )
    {
        det = matrix.data_[0][0];
    }
    else if( size == 2 )
    {
        det = matrix.data_[0][0] *
                matrix.data_[1][1] -
                matrix.data_[0][1] *
                matrix.data_[1][0];
    }
    else
    {
        sMatrix  localMatrix(size - 1, size - 1 );
        int i,j;
        for( i = 0; i < size; ++i )
        {
            for( j = 0; j < size - 1; ++j )
            {
                if( j < i )
                    localMatrix.data_[j] = matrix.data_[j].mid(0, size - 1);
                else
                    localMatrix.data_[j] = matrix.data_[j+1].mid(0, size - 1);

            }

            det += pow( ( double) - 1, ( i + j) ) * getDetermination (localMatrix) * matrix.data_[i][ size - 1];
        }
    }

    return det;
}


double cMatrixComputations::getDistanceBetweenParallelLines(const cLine & line1, const cLine & line2 )
{
    sMatrix numenatorMatrix1( 2, 2 );
    sMatrix numenatorMatrix2( 2, 2 );
    sMatrix numenatorMatrix3( 2, 2 );

    sPoint point1 = line1.pointOnLine_.first();
    sPoint point2 = line2.pointOnLine_.first();

    numenatorMatrix1.data_[0][0] =  point2.x_ - point1.x_;
    numenatorMatrix1.data_[0][1] = point2.y_ - point1.y_;
    numenatorMatrix1.data_[1][0] = line1.guideVector_.x_;
    numenatorMatrix1.data_[1][1] = line1.guideVector_.y_;

    numenatorMatrix2.data_[0][0] =  point2.y_ - point1.y_;
    numenatorMatrix2.data_[0][1] = point2.z_ - point1.z_;
    numenatorMatrix2.data_[1][0] = line1.guideVector_.y_;
    numenatorMatrix2.data_[1][1] = line1.guideVector_.z_;

    numenatorMatrix3.data_[0][0] =  point2.z_ - point1.z_;
    numenatorMatrix3.data_[0][1] = point2.x_ - point1.x_;
    numenatorMatrix3.data_[1][0] = line1.guideVector_.z_;
    numenatorMatrix3.data_[1][1] = line1.guideVector_.x_;

    double determ1 = getDetermination(numenatorMatrix1);
    double determ2 = getDetermination(numenatorMatrix2);
    double determ3 = getDetermination(numenatorMatrix3);


    double numenator = sqrt(determ1 * determ1 + determ2 * determ2 + determ3 * determ3);
    double denominator = line1.guideVector_.module();

    if (denominator != 0.0)
    {
        return numenator / denominator;
    }

    return 0.0;
}


double cMatrixComputations::getDistance(const cLine & line1, const cLine & line2 )
{
    double distance = 0.0;

    sMatrix numeratorMatrix( 3, 3 );

    sPoint point1 = line1.pointOnLine_.first();
    sPoint point2 = line2.pointOnLine_.first();

    numeratorMatrix.data_[0][0] = point2.x_ - point1.x_;
    numeratorMatrix.data_[0][1] = point2.y_ - point1.y_;
    numeratorMatrix.data_[0][2] = point2.z_ - point1.z_;

    numeratorMatrix.data_[1][0] = line1.guideVector_.x_;
    numeratorMatrix.data_[1][1] = line1.guideVector_.y_;
    numeratorMatrix.data_[1][2] = line1.guideVector_.z_;

    numeratorMatrix.data_[2][0] = line2.guideVector_.x_;
    numeratorMatrix.data_[2][1] = line2.guideVector_.y_;
    numeratorMatrix.data_[2][2] = line2.guideVector_.z_;

    double numerator = getDetermination(numeratorMatrix);

    if (numerator == 0.0)
    {
        return  getDistanceBetweenParallelLines(line1, line2);
    }

    sMatrix denominatorMatrix1( 2, 2 );

    denominatorMatrix1.data_[0][0] = line1.guideVector_.x_;
    denominatorMatrix1.data_[0][1] = line1.guideVector_.y_;

    denominatorMatrix1.data_[1][0] = line2.guideVector_.x_;
    denominatorMatrix1.data_[1][1] = line2.guideVector_.y_;

    sMatrix denominatorMatrix2( 2, 2 );

    denominatorMatrix2.data_[0][0] = line1.guideVector_.y_;
    denominatorMatrix2.data_[0][1] = line1.guideVector_.z_;

    denominatorMatrix2.data_[1][0] = line2.guideVector_.y_;
    denominatorMatrix2.data_[1][1] = line2.guideVector_.z_;

    sMatrix denominatorMatrix3( 2, 2 );

    denominatorMatrix3.data_[0][0] = line1.guideVector_.z_;
    denominatorMatrix3.data_[0][1] = line1.guideVector_.x_;

    denominatorMatrix3.data_[1][0] = line2.guideVector_.z_;
    denominatorMatrix3.data_[1][1] = line2.guideVector_.x_;

    double detetm1 = getDetermination(denominatorMatrix1);
    double detetm2 = getDetermination(denominatorMatrix2);
    double detetm3 = getDetermination(denominatorMatrix3);

    double denominator = sqrt(detetm1 * detetm1 + detetm2 * detetm2 + detetm3 * detetm3);

    if (denominator != 0.0)
    {
        distance = qAbs(numerator / denominator);
    }

    return distance;
}
