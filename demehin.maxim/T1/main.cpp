#include <iostream>
#include <string>
#include <iomanip>
#include "rectangle.hpp"
#include "ring.hpp"
#include "polygon.hpp"
#include "factory.hpp"

namespace
{
  void makeIsoScale(demehin::Shape** shapes, size_t shp_cnt, double scale_k, const demehin::point_t& scale_pt)
  {
    for (size_t i = 0; i < shp_cnt; i++)
    {
      demehin::point_t orig_pt = shapes[i]->getFrameRect().pos;
      shapes[i]->move(scale_pt);
      demehin::point_t new_pt = shapes[i]->getFrameRect().pos;
      double move_x = (new_pt.x - orig_pt.x) * scale_k;
      double move_y = (new_pt.y - orig_pt.y) * scale_k;
      demehin::point_t move_vector = {move_x, move_y};
      shapes[i]->scale(scale_k);
      shapes[i]->move(move_vector.x * -1, move_vector.y * -1);
    }
  }

  double getAreaSum(const demehin::Shape* const* shapes, size_t shp_cnt)
  {
    double area_sum = 0;
    for (size_t i = 0; i < shp_cnt; i++)
    {
      area_sum += shapes[i]->getArea();
    }
    return area_sum;
  }

  void getFrRectCords(const demehin::rectangle_t& fr_rect, double& lt_bot_x, double& lt_bot_y,
    double& rt_top_x, double& rt_top_y)
 {
    lt_bot_x = fr_rect.pos.x - fr_rect.width / 2;
    lt_bot_y = fr_rect.pos.y - fr_rect.height / 2;
    rt_top_x = fr_rect.pos.x + fr_rect.width / 2;
    rt_top_y = fr_rect.pos.y + fr_rect.height / 2;
  }

  void printShapesInfo(std::ostream& out, const demehin::Shape* const* shapes, size_t shp_cnt)
  {
    out << getAreaSum(shapes, shp_cnt);
    for (size_t i = 0; i < shp_cnt; i++)
    {
      double lt_bot_x = 0, lt_bot_y = 0, rt_top_x = 0, rt_top_y = 0;
      demehin::rectangle_t fr_rect = shapes[i]->getFrameRect();
      getFrRectCords(fr_rect, lt_bot_x, lt_bot_y, rt_top_x, rt_top_y);
      out << " "  << lt_bot_x << " " << lt_bot_y << " " << rt_top_x << " " << rt_top_y;
    }
  }

  void free_shapes(demehin::Shape** shapes, size_t shp_cnt)
  {
    for (size_t i = 0; i < shp_cnt; i++)
    {
      delete shapes[i];
    }
  }
}

int main()
{
  demehin::Shape* shapes[10000] = {};
  size_t shp_cnt = 0;
  bool is_incorrect_shp = false;

  std::string shape_name;
  while (shape_name != "SCALE")
  {
    std::cin >> shape_name;
    if (std::cin.eof())
    {
      std::cerr << "error: eof\n";
      free_shapes(shapes, shp_cnt);
      return 1;
    }

    try
    {
      demehin::createShape(std::cin, shape_name, shapes, shp_cnt);
    }
    catch (const std::bad_alloc&)
    {
      free_shapes(shapes, shp_cnt);
      return 1;
    }
    catch (const std::logic_error&)
    {
      shp_cnt--;
      is_incorrect_shp = true;
    }
  }

  double scale_pt_x = 0, scale_pt_y = 0, scale_k = 0;
  std::cin >> scale_pt_x >> scale_pt_y >> scale_k;
  if (scale_k < 0)
  {
    std::cerr << "Incorrect scale\n";
    free_shapes(shapes, shp_cnt);
    return 1;
  }

  if (shp_cnt == 0)
  {
    std::cerr << "no shapes\n";
    return 1;
  }

  if (is_incorrect_shp)
  {
    std::cerr << "Incorrect shape\n";
  }

  std::cout << std::fixed << std::setprecision(1);
  printShapesInfo(std::cout, shapes, shp_cnt);
  std::cout << "\n";

  demehin::point_t scale_pt = {scale_pt_x, scale_pt_y};
  makeIsoScale(shapes, shp_cnt, scale_k, scale_pt);

  printShapesInfo(std::cout, shapes, shp_cnt);
  std::cout << "\n";

  free_shapes(shapes, shp_cnt);
}

