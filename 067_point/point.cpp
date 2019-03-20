#include "point.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Point::Point() : x(0), y(0) {}

void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point::distanceFrom(const Point & p) {
  double ans = 0;
  double dx = x - p.x;
  double dy = y - p.y;
  ans = sqrt(dx * dx + dy * dy);
  return ans;
}
