#include "board.h"

Board::Board()
    : m_Colors(), m_SideToMove(Color::RED)
{
    
}

void Board::makeMove(Move m)
{
    addPiece(m.sqIdx, m_SideToMove);
    m_SideToMove = flip(m_SideToMove);
}

// 49 bit perfect hash
// from https://gamedev.net/forums/topic/644765-hashing-connect-4-board-for-transposition-tableneed-some-help/5072946/
uint64_t Board::key() const
{
    uint64_t occupied = m_Colors[0] | m_Colors[1];
    return ((occupied << 1) | BOTTOM_ROW) ^ m_Colors[static_cast<int>(Color::RED)];
}

void Board::addPiece(uint32_t sq, Color color)
{
    assert((m_Colors[static_cast<int>(color)] & (1ull << sq)) == 0);
    m_Colors[static_cast<int>(color)] |= (1ull << sq);
}
