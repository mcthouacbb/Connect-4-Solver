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

int searchRoot(const Board& board, int depth)
{
    m_Plies[0].pvLength = 0;
    if (board.isLoss())
        return -SCORE_WIN;
    Bitboard moves = moveLocations(board);
    Bitboard usWins = board.threatsFor(board.sideToMove());
    if (moves & usWins)
    {
        m_Plies[0].pvLength = 1;
        m_Plies[0].pv[0] = Move(getLSB(moves & usWins));
        return SCORE_WIN - 1;
    }
    return search(board, depth, -SCORE_WIN, SCORE_WIN, &m_Plies[0]);
}

int Search::search(const Board& board, int depth, int alpha, int beta, SearchPly* searchPly)
{
    searchPly->pvLength = 0;
    
	alpha = std::max(alpha, -SCORE_WIN + searchPly->ply);
	beta = std::min(beta, SCORE_WIN - searchPly->ply);
	if (alpha >= beta)
		return alpha;

    Bitboard moves = moveLocations(board);
    if (moves == 0)
        return 0;

    Bitboard oppWins = board.threatsFor(flip(board.sideToMove()));
    Bitboard forcedMoves = moves & oppWins;

    Bitboard nonLosingMoves = moves;
    if (forcedMoves & (forcedMoves - 1))
        return -SCORE_WIN + searchPly->ply + 2;
    else if (forcedMoves)
        nonLosingMoves &= forcedMoves;

    // if (board.isLoss())
        // return -SCORE_WIN + searchPly->ply;

    bool found;
    int ttScore;
    Move ttMove;
    TTEntry* entry;
    {
        int ttDepth;
        TTBound ttBound;
        entry = m_TT.probe(board.key(), searchPly->ply, found, ttScore, ttMove, ttDepth, ttBound);
        if (found)
        {
            if (ttDepth >= depth && (
                ttBound == TTBound::EXACT ||
                (ttBound == TTBound::LOWER_BOUND && ttScore >= beta) ||
                (ttBound == TTBound::UPPER_BOUND && ttScore <= alpha)
                ))
            {
                return ttScore;
            }
        }
        else
        {
            ttMove = MOVE_NULL;
        }
    }

    MovePicker movePicker(board, nonLosingMoves, ttMove, m_Killers[searchPly->ply]);

    if (movePicker.size() == 0)
        return 0;
    
    if (depth == 0)
        return evaluate(board);
    
    int bestScore = -SCORE_WIN;
    Move bestMove = MOVE_NULL;
    TTBound currBound = TTBound::UPPER_BOUND;
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
            currBound = TTBound::EXACT;
            alpha = score;
            bestMove = move;
            
            searchPly->pvLength = searchPly[1].pvLength + 1;
            searchPly->pv[0] = move;
            std::copy(searchPly[1].pv.begin(), searchPly[1].pv.begin() + searchPly[1].pvLength, searchPly->pv.begin() + 1);
        }

        if (alpha >= beta)
        {
            currBound = TTBound::LOWER_BOUND;
            if (m_Killers[searchPly->ply][0] != move)
            {
                m_Killers[searchPly->ply][1] = m_Killers[searchPly->ply][0];
                m_Killers[searchPly->ply][0] = move;
            }
            break;
        }
    }

    m_TT.store(entry, board.key(), searchPly->ply, bestScore, bestMove, depth, currBound);

    return bestScore;
}
