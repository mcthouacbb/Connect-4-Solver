#pragma once

#include "board.h"
#include "movegen.h"

#include <string_view>
#include <optional>
#include <string>
#include <vector>

std::optional<Board> posFromMoves(std::string_view moves);

struct BenchPos
{
    Board board;
    int expectedScore;
    std::string moves;
};

std::vector<BenchPos> loadBenchmark(const std::string& positions);
