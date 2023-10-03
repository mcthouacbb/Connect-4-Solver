#pragma once

#include "board.h"
#include "movegen.h"
#include "move_picker.h"
#include "tt.h"

constexpr int MAX_PLY = 42;

struct SearchInfo
{
    uint64_t nodes;
    int score;
    int depth;
    std::array<Move, MAX_PLY> pv;
};

struct SearchLimits
{
    bool reportInfo;
    int maxDepth;
    int expectedScore;
};

struct SearchPly
{
    int ply;
    int pvLength;
    std::array<Move, MAX_PLY> pv;
};

class Search
{
public:
    Search();

    int iterDeep(const Board& board, const SearchLimits& limits);
private:
    int searchRoot(const Board& board, int depth);
    int search(const Board& board, int depth, int alpha, int beta, SearchPly* searchPly);

    uint64_t m_Nodes;
    std::array<SearchPly, MAX_PLY> m_Plies;
    std::array<Killer, MAX_PLY> m_Killers;
    TT m_TT;
};
