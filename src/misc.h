#include "board.h"
#include "movegen.h"

#include <charconv>
#include <optional>
#include <sstream>
#include <vector>
#include <string_view>
#include <stdexcept>

std::optional<Board> posFromMoves(std::string_view moves)
{
    Board board;
    for (char move : moves)
    {
        int column = move - '1';
        if (column < 0 || column > 6)
        {
            std::cout << "foih" << std::endl;
            std::cout << column << std::endl;
            std::cout << move << std::endl;
            std::cout << static_cast<int>(move) << std::endl;
            return {};
        }

        MoveList moves;
        genMoves(moves, board);
        for (Move move : moves)
        {
            if (sqColumn(move.sqIdx) == column)
            {
                board.makeMove(move);
                goto found_move;
            }
        }
        std::cout << "WT" << std::endl;
        return {};
    found_move:
        ;
    }
    return board;
}

struct BenchPos
{
    Board board;
    int expectedScore;
    std::string moves;
};

std::vector<BenchPos> loadBenchmark(const std::string& positions)
{
    std::vector<BenchPos> benchmark;
    std::istringstream stream(positions);
    while (stream)
    {
        std::string moves, scoreStr;
        stream >> moves >> scoreStr;
        if (!stream)
            break;
        auto board = posFromMoves(moves);
        if (!board.has_value())
            throw std::runtime_error("loadBenchmark(): invalid move sequence");
        int score;
        auto [ptr, ec] = std::from_chars(scoreStr.c_str(), scoreStr.c_str() + scoreStr.size(), score);
        if (ec != std::errc())
            throw std::runtime_error("loadBenchmark(): score must be a valid integer");
        if (score > 0)
        {
            int winMoves = 22 - score;
            int winPly = winMoves * 2 - 1;
            int currPly = popcount(board.value().all());
            score = SCORE_WIN - (winPly - currPly);
        }
        else if (score < 0)
        {
            int lossMoves = score + 22;
            int lossPly = lossMoves * 2 - 1;
            int currPly = popcount(board.value().all());
            score = -SCORE_WIN + (lossPly - currPly);
        }
        
        benchmark.push_back({board.value(), score, moves});
    }
    return benchmark;
}
