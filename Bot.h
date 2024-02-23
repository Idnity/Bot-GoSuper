#pragma once
#include <array>

class Bot
{
public:
    Bot();
    void tick();
    void FetchScreenBoardToArray(std::array<int, 132> array);
};
