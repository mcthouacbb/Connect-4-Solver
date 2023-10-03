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

    bool isLoss() const;

    Color sideToMove() const;

    Bitboard threatsFor(Color color) const;

    bool isSymmetrical() const;
private:
    void calcThreatsFor(Color color);
    Bitboard calcThreats(Bitboard us, Bitboard all);
    void addPiece(uint32_t sq, Color color);

    std::array<Bitboard, 2> m_Colors;
    std::array<Bitboard, 2> m_Threats;
    Color m_SideToMove;
};

inline Bitboard Board::all() const
{
    return m_Colors[0] | m_Colors[1];
}

inline Color Board::sideToMove() const
{
    return m_SideToMove;
}

inline Bitboard Board::threatsFor(Color color) const
{
    return m_Threats[static_cast<int>(color)];
}

inline bool Board::isSymmetrical() const
{
    return byteswap(m_Colors[0]) == m_Colors[0] && byteswap(m_Colors[1]) == m_Colors[1];
}
