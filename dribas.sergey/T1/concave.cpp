#include "concave.hpp"
#include <cmath>
#include <stdexcept>
#include "base-types.hpp"

namespace dribas
{
  bool isTriangle(point_t a, point_t b, point_t c);
  bool isPointInTriangle(point_t a, point_t b, point_t c, point_t d);
  double getMyArea(point_t a, point_t b, point_t c);
  bool isDupePoint(point_t p1, point_t p2, point_t p3, point_t p4);
}

bool dribas::isDupePoint(point_t p1, point_t p2, point_t p3, point_t p4) {
   if (p1.x == p2.x && p1.y == p2.y) return true;
   if (p1.x == p3.x && p1.y == p3.y) return true;
   if (p1.x == p4.x && p1.y == p4.y) return true;
   if (p2.x == p3.x && p2.y == p3.y) return true;
   if (p2.x == p4.x && p2.y == p4.y) return true;
   if (p3.x == p4.x && p3.y == p4.y) return true;
   return false;
}

bool dribas::isTriangle(point_t a, point_t b, point_t c)
{
  return !((((a.x == b.x) && (a.x == c.x))) || (( a.y == b.y) && (a.y == c.y)));
}

double dribas::getMyArea(point_t a, point_t b, point_t c) {
  return std::abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y -b.y)) / 2.0l);
}

bool dribas::isPointInTriangle(point_t a, point_t b, point_t c, point_t d)
{
  double s = getMyArea(a, b, c);
  double s1 = getMyArea(a, b, d);
  double s2 = getMyArea(a, d, c);
  double s3 = getMyArea(d, b, c);
  return (s == (s1 + s2 + s3));
}

dribas::Concave::Concave(point_t a, point_t b, point_t c, point_t d):
  a_({0.0, 0.0}), b_({0.0, 0.0}), c_({0.0, 0.0}), d_({0.0, 0.0})
{
  if (!isTriangle(a, b, c) || !isPointInTriangle(a, b, c, d) || isDupePoint(a, b, c, d)) {
    throw std::invalid_argument("Error witch point for concave\n");
  }
  a_ = a;
  b_ = b;
  c_ = c;
  d_ = d;
}

double dribas::Concave::getArea() const
{
  return std::abs(a_.x * b_.y + b_.x * c_.y + c_.x * d_.y + d_.x * a_.y - b_.x * a_.y - c_.x
    * b_.y - d_.x * c_.y - a_.x * d_.y) / 2.0; //ОБЯЗАТЕЛЬНО ПЕРЕДЕЛАТЬ!!!!!
}
dribas::rectangle_t dribas::Concave::getFrameRect() const
{
  double maxX = std::max(a_.x, std::max(b_.x, c_.x));
  double maxY = std::max(a_.y, std::max(b_.y, c_.y));
  double minY = std::min(a_.y, std::min(b_.y, c_.y));
  double minX = std::min(a_.x, std::min(b_.x, c_.x));
  rectangle_t result;
  result.height = maxY - minY;
  result.width = maxX - minX;
  result.pos.x = minX + (result.width / 2.0);
  result.pos.y = minY + (result.height / 2.0);
  return result;
}
void dribas::Concave::move(double x, double y)
{
  a_.x += x;
  b_.x += x;
  c_.x += x;
  d_.x += x;
  a_.y += y;
  b_.y += y;
  c_.y += y;
  d_.y += y;
}

void dribas::Concave::move(point_t point)
{
  double moveX = point.x - d_.x;
  double moveY = point.y - d_.y;
  move(moveX, moveY);
}

void dribas::Concave::scale(double ratio)
{
  if (ratio <= 0) {
    throw std::invalid_argument("under zero ratio\n");
  }
  if (a_.x - d_.x < 0) {
    a_.x = -(d_.x - a_.x) * ratio;
  } else {
    a_.x = (a_.x - d_.x) * ratio;
  }
  if (b_.x - d_.x < 0) {
    b_.x = -(d_.x - b_.x) * ratio;
  } else {
    b_.x = (b_.x - d_.x) * ratio;
  }
  if (c_.x - d_.x < 0) {
    c_.x = -(d_.x - c_.x) * ratio;
  } else {
    c_.x = (c_.x - d_.x) * ratio;
  }
   if (a_.y - d_.y < 0) {
    a_.y = -(d_.y - a_.y) * ratio;
  } else {
    a_.y = (a_.y - d_.y) * ratio;
  }
  if (b_.y - d_.y < 0) {
    b_.y = -(d_.y - b_.y) * ratio;
  } else {
    b_.y = (b_.y - d_.y) * ratio;
  }
  if (c_.y - d_.y < 0) {
    c_.y = -(d_.y - c_.y) * ratio;
  } else {
    c_.y = (c_.y - d_.y) * ratio;
  }
}
