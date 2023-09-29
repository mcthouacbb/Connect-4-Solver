#include "search.h"
#include "evaluate.h"

#include <algorithm>
#include <iostream>

Search::Search()
    : m_Nodes(0)
{
    for (uint32_t i = 0; i < m_Plies.size(); i++)
    {
        m_Plies[i].ply = i;
    }
}

int Search::iterDeep(const Board& board, const SearchLimits& limits)
{
    int score = 0;
    m_Nodes = 0;
    m_History.fill({});
    m_Killers.fill({});
    for (int depth = 1; depth <= limits.maxDepth; depth++)
    {
        score = search(board, depth, -1000000, 1000000, &m_Plies[0]);
        SearchInfo searchInfo;
        searchInfo.nodes = m_Nodes;
        searchInfo.score = score;
        searchInfo.depth = depth;
        std::copy(m_Plies[0].pv.begin(), m_Plies[0].pv.begin() + m_Plies[0].pvLength, searchInfo.pv.begin());
        
        std::cout << "Depth: " << searchInfo.depth << std::endl;
        std::cout << "\tScore: " << searchInfo.score << std::endl;
        std::cout << "\tNodes: " << searchInfo.nodes << std::endl;
    }
    return score;
}

int Search::search(const Board& board, int depth, int alpha, int beta, SearchPly* searchPly)
{
    searchPly->pvLength = 0;

    if (board.isLoss())
        return -SCORE_WIN + searchPly->ply;
    

    MovePicker movePicker(board, m_History, m_Killers[searchPly->ply]);

    if (movePicker.size() == 0)
        return 0;
    
    if (depth == 0)
        return evaluate(board);
    
    int bestScore = -SCORE_WIN;
    
    for (uint32_t i = 0; i < movePicker.size(); i++)
    {
        Move move = movePicker.pickMove();
        Board b = board;
        b.makeMove(move);
        m_Nodes++;
        int score = -search(b, depth - 1, -beta, -alpha, searchPly + 1);

        if (score > bestScore)
            bestScore = score;
        
        if (score > alpha)
        {
            alpha = score;
            
            searchPly->pvLength = searchPly[1].pvLength + 1;
            searchPly->pv[0] = move;
            std::copy(searchPly[1].pv.begin(), searchPly[1].pv.begin() + searchPly[1].pvLength, searchPly->pv.begin() + 1);
        }

        if (alpha >= beta)
        {
            m_History[static_cast<int>(board.sideToMove())][move.sqIdx] += depth * depth;
            if (m_Killers[searchPly->ply][0] != move)
            {
                m_Killers[searchPly->ply][1] = m_Killers[searchPly->ply][0];
                m_Killers[searchPly->ply][0] = move;
            }
            break;
        }
    }

    return bestScore;
}
