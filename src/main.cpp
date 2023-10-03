#include <iostream>
#include "board.h"
#include "movegen.h"
#include "search.h"
#include "misc.h"
#include "utils/file.h"

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
    // std::cout << "Hello World!" << std::endl;
    std::string file = readFile("res/test_L1_R1.txt");
    std::vector<BenchPos> benches = loadBenchmark(file);
    Search search;
    for (auto& bench : benches)
    {
        SearchLimits limits = {};
        limits.maxDepth = 14;
        limits.expectedScore = bench.expectedScore;
        limits.reportInfo = false;
        int score = search.iterDeep(bench.board, limits);
        if (score != bench.expectedScore)
        {
            std::cout << "Failed " << bench.moves << ", Expected: " << bench.expectedScore << " Got: " << score << std::endl;
        }
    }
    /*Board board = posFromMoves("44455554221").value();
    std::cout << board.getString() << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    Search search;
    SearchLimits limits = {30};
    int score = search.iterDeep(board, limits);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << score << ' ' << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;*/
    return 0;
}
