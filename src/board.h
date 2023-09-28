#pragma once

#include "bitboard.h"
#include "defs.h"

#include <array>

class Board
{
public:
    Board();

    Board(const Board&) = default;
    Board& operator=(const Board&) = default;

    void makeMove(Move move);

    // 49 bit perfect hash
    uint64_t key() const;

    Bitboard all() const;

    bool isWin() const;
private:
    void addPiece(uint32_t sq, Color color);

    std::array<Bitboard, 2> m_Colors;
    Color m_SideToMove;
};

inline Bitboard Board::all() const
{
    return m_Colors[0] | m_Colors[1];
}
