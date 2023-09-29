#pragma once

#include "defs.h"
#include "board.h"
#include "movegen.h"
#include "history.h"

using Killer = std::array<Move, 2>;

class MovePicker
{
public:
    MovePicker(const Board& board, Move ttMove, const ColorToHistory& history, const Killer& killers);

    uint32_t size() const;
    Move pickMove();
private:
    void scoreMoves();

    const Board& m_Board;
    const ColorToHistory& m_History;
    const Killer& m_Killers;
    Move m_TTMove;
    MoveList m_MoveList;
    std::array<int, 7> m_MoveScores;
    uint32_t m_CurrIdx;
};

inline uint32_t MovePicker::size() const
{
    return m_MoveList.size();
}
