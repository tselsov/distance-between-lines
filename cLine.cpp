#include "cLine.h"

cLine::cLine(const sPoint & point1, const sPoint & point2)
    : pointOnLine_({point1, point2})
    , guideVector_(point1, point2)
{
}
