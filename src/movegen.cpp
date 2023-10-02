#include "movegen.h"

void genMoves(MoveList& moveList, const Board& board)
{
    Bitboard moveLocations = board.all() + BOTTOM_ROW;
    moveLocations &= IN_BOARD;

    while (moveLocations)
    {
        uint32_t sq = popLSB(moveLocations);
        moveList.push_back(Move(static_cast<uint16_t>(sq)));
    }
}
