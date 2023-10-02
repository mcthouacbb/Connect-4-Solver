#include "movegen.h"

Bitboard moveLocations(const Board& board)
{
    return (board.all() + BOTTOM_ROW) & IN_BOARD;
}

void genMoves(MoveList& moveList, const Board& board)
{
    Bitboard moveBB = moveLocations(board);

    while (moveBB)
    {
        uint32_t sq = popLSB(moveBB);
        moveList.push_back(Move(static_cast<uint16_t>(sq)));
    }
}

void genMoves(MoveList& moveList, Bitboard moveBB)
{
    while (moveBB)
    {
        uint32_t sq = popLSB(moveBB);
        moveList.push_back(Move(static_cast<uint16_t>(sq)));
    }
}
