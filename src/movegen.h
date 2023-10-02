#pragma once

#include "board.h"
#include "utils/static_vec.h"

using MoveList = StaticVector<Move, 7>;

Bitboard moveLocations(const Board& board);
void genMoves(MoveList& moveList, const Board& board);
void genMoves(MoveList& moveList, Bitboard moveBB);
