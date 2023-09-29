#include <iostream>
#include "board.h"
#include "movegen.h"
#include "search.h"

#include <chrono>

uint64_t perft(Board& board, int depth)
{
    if (board.isLoss() || depth == 0)
        return 1;
    MoveList moveList;
    genMoves(moveList, board);

    uint64_t nodes = 0;
    
    for (uint32_t i = 0; i < moveList.size(); i++)
    {
        Move move = moveList[i];
        Board b = board;
        b.makeMove(move);
        nodes += perft(b, depth - 1);
    }

    return nodes;
}

int main()
{
    std::cout << "Hello World!" << std::endl;
    Board board;
    auto t1 = std::chrono::high_resolution_clock::now();
    Search search;
    SearchLimits limits = {20};
    int score = search.iterDeep(board, limits);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << score << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;

    return 0;
}
