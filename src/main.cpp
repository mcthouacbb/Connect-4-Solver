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

void runBench(std::string filepath)
{
    std::string file = readFile(filepath);
    std::vector<BenchPos> benches = loadBenchmark(file);
    Search search;
    int passed = 0;
    int failed = 0;
    uint64_t totalNodes = 0;
    for (auto& bench : benches)
    {
        SearchLimits limits = {};
        limits.maxDepth = 28;
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
        if ((passed + failed) % 10 == 0)
            std::cout << "Passed: " << passed << " Failed: " << failed << " npb: " << totalNodes / (passed + failed) << std::endl;
    }
    std::cout << "Passed: " << passed << std::endl;
    std::cout << "Failed: " << failed << std::endl;
    std::cout << "Total nodes: " << totalNodes << std::endl;
    std::cout << "Nodes per bench: " << totalNodes / benches.size() << std::endl;
}

int main(int argc, char** argv)
{
    if (argc > 1)
    {
        std::string arg(argv[1]);
        runBench(arg);
    }
    else
    {
        SearchLimits limits;
        limits.reportInfo = true;
        limits.maxDepth = 42;
        Search search;
        Board board;
        search.iterDeep(board, limits);
    }
    return 0;
}
