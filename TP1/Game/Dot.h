#pragma once

class Dot
{
public:
  Dot(int x = 0, int y = 0);

  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
  bool operator==(const Dot& other) const; // A ce qu'il parait pour que le compilateur sache comment comparer
  bool operator!=(const Dot& other) const;


private:
  int x;
  int y;
};

