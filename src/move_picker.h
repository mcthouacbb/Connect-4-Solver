#pragma once

#include "defs.h"
#include "board.h"
#include "movegen.h"

using History = std::array<std::array<int, 56>, 2>;

class MovePicker
{
public:
    MovePicker(const Board& board, const History& history);

    uint32_t size() const;
    Move pickMove();
private:
    void scoreMoves();

    const Board& m_Board;
    const History& m_History;
    MoveList m_MoveList;
    std::array<int, 7> m_MoveScores;
    uint32_t m_CurrIdx;
};

inline uint32_t MovePicker::size() const
{
    return m_MoveList.size();
}