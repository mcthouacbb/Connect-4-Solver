#pragma once

#include <cassert>

enum class Color
{
    RED,
    YELLOW
};

constexpr Color flip(Color c)
{
    return static_cast<Color>(static_cast<int>(c) ^ 1);
}

struct Move
{
    uint16_t sqIdx;
    uint16_t column;
};
