#include "board.h"
#include "utils/static_vec.h"

using MoveList = StaticVector<Move, 7>;

void genMoves(MoveList& moveList, const Board& board);
