#pragma once
#include "Dot.h"

struct Square
{
  Dot dots[4];
};

bool operator==(const Square& lhs, const Square& rhs);
