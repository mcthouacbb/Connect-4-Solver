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
    std::string file = readFile("res/test_L3_R1.txt");
    std::vector<BenchPos> benches = loadBenchmark(file);
    Search search;
    int passed = 0;
    int failed = 0;
    uint64_t totalNodes = 0;
    for (auto& bench : benches)
    {
        SearchLimits limits = {};
        limits.maxDepth = 14;
        limits.expectedScore = bench.expectedScore;
        limits.reportInfo = false;
        SearchInfo info = search.iterDeep(bench.board, limits);
        if (info.score != bench.expectedScore)
        {
            failed++;
            std::cout << "Failed " << bench.moves << ", Expected: " << bench.expectedScore << " Got: " << info.score << std::endl;
        }
        else
        {
            passed++;
        }
        totalNodes += info.nodes;
    }
    std::cout << "Passed: " << passed << std::endl;
    std::cout << "Failed: " << failed << std::endl;
    std::cout << "Total nodes: " << totalNodes << std::endl;
    std::cout << "Nodes per bench: " << totalNodes / benches.size() << std::endl;
    return 0;
}
