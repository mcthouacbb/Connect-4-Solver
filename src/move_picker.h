#pragma once

#include "defs.h"
#include "board.h"
#include "movegen.h"

class MovePicker
{
public:
    MovePicker(const Board& board);

    uint32_t size() const;
    Move pickMove();
private:
    void scoreMoves();

    const Board& m_Board;
    MoveList m_MoveList;
    std::array<int, 7> m_MoveScores;
    uint32_t m_CurrIdx;
};

inline uint32_t MovePicker::size() const
{
    return m_MoveList.size();
}