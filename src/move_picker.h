#pragma once

#include "defs.h"
#include "board.h"
#include "movegen.h"
#include "history.h"

class MovePicker
{
public:
    MovePicker(const Board& board, Bitboard moveBB, Move ttMove);

    uint32_t size() const;
    Move pickMove();
private:
    void scoreMoves();

    const Board& m_Board;
    Bitboard m_MoveBB;
    Move m_TTMove;
    MoveList m_MoveList;
    std::array<int, 7> m_MoveScores;
    uint32_t m_CurrIdx;
};

inline uint32_t MovePicker::size() const
{
    return static_cast<uint32_t>(m_MoveList.size());
}
