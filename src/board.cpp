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

// from http://blog.gamesolver.org/solving-connect-four/06-bitboard/#:~:text=Checking%20for%20aligment
bool Board::isLoss() const
{
    Bitboard pieces = m_Colors[static_cast<int>(flip(m_SideToMove))];
    
    Bitboard m = pieces & (pieces >> 8);
    if (m & (m >> 16))
        return true;

    m = pieces & (pieces >> 9);
    if (m & (m >> 18))
        return true;

    m = pieces & (pieces >> 7);
    if (m & (m >> 14))
        return true;

    m = pieces & (pieces >> 1);
    if (m & (m >> 2))
        return true;
    
    return false;
}
