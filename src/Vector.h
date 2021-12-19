
#ifndef PONGSFML_VECTOR_H
#define PONGSFML_VECTOR_H
class Vector
{
 public:
  void vector(int x,int y);
  void startVectorBall(int x,int y);

  int new_x;
  int new_y;

  float mag;
  float unit_y;
  float unit_x;

};

#endif // PONGSFML_VECTOR_H
