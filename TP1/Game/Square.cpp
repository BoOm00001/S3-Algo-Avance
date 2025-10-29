#include "stdafx.h"
#include "Square.h"

bool operator==(const Square& lhs, const Square& rhs)
{
    int matchCount = 0;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (lhs.dots[i] == rhs.dots[j])
            {
                ++matchCount;
                break;
            }
        }
    }

    return matchCount == 4;
}
