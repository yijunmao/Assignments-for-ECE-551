#include "circle.h"

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

Circle::Circle(Point p, double r) : center(p), radius(r) {}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  /*radius of two circles, distance between them*/
  double r1 = radius;
  double r2 = otherCircle.radius;

  double d = center.distanceFrom(otherCircle.center);

  /*no intersection*/
  if (d >= r1 + r2) {
    return 0;
  }

  /*one circle is inside of another*/
  else if (d <= abs(r1 - r2)) {
    if (r1 <= r2) {
      return M_PI * pow(r1, 2);
    }
    else {
      return M_PI * pow(r2, 2);
    }
  }

  /*circles have intersection*/
  else {
    double r_large = 0;
    double r_small = 0;
    if (r1 >= r2) {
      r_large = r1;
      r_small = r2;
    }
    else {
      r_large = r2;
      r_small = r1;
    }
    double distance_large = (pow(r_large, 2) - pow(r_small, 2) + pow(d, 2)) / (2 * d);
    double theta_large = 2 * acos(distance_large / r_large);
    double distance_small = d - distance_large;
    double theta_small = 2 * acos(distance_small / r_small);
    double area_large = 0.5 * pow(r_large, 2) * (theta_large - sin(theta_large));
    double area_small = 0.5 * pow(r_small, 2) * (theta_small - sin(theta_small));
    double area_intersection = area_large + area_small;
    return area_intersection;
  }
}
