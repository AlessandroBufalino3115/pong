#include "Vector.h"
#include <math.h>

void Vector::vector(int x, int y)
{
  if (new_x == x && new_y == y)
  {
    // do nothing
  }
  else
  {
    mag  = sqrt(pow(new_x - x,2) + pow(new_y - y, 2));

    unit_y = (new_y - y)/mag;
    unit_x = (new_x - x)/mag;
  }
}

//called everytime the ball is instantiated at first
void Vector::startVectorBall(int x, int y)
{
  mag  = sqrt(pow( x,2) + pow(y, 2));

  unit_y = (y)/mag;
  unit_x = (x)/mag;
}
