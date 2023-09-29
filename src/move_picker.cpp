#include "move_picker.h"

constexpr int sqScores[56] = {
    // column 1         // unused padding
    1, 1, 1, 1, 1, 1,    0, 0,
    // column 2
    2, 2, 2, 2, 2, 2,    0, 0,
    // column 3
    3, 3, 3, 3, 3, 3,    0, 0,
    // column 4
    4, 4, 4, 4, 4, 4,    0, 0,
    // column 5
    3, 3, 3, 3, 3, 3,    0, 0,
    // column 6
    2, 2, 2, 2, 2, 2,    0, 0,
    // column 7
    1, 1, 1, 1, 1, 1,    0, 0
};

MovePicker::MovePicker(const Board& board)
    : m_Board(board), m_CurrIdx(0)
{
    genMoves(m_MoveList, m_Board);
    scoreMoves();
}

void MovePicker::scoreMoves()
{
    for (uint32_t i = 0; i < size(); i++)
    {
        Move move = m_MoveList[i];
        m_MoveScores[i] = sqScores[move.sqIdx];
        // m_MoveScores[i] = 0;
    }
}

Move MovePicker::pickMove()
{
    uint32_t bestIdx = m_CurrIdx;
    for (uint32_t i = m_CurrIdx + 1; i < size(); i++)
    {
        if (m_MoveScores[i] > m_MoveScores[bestIdx])
            bestIdx = i;
    }

    std::swap(m_MoveScores[m_CurrIdx], m_MoveScores[bestIdx]);
    std::swap(m_MoveList[m_CurrIdx], m_MoveList[bestIdx]);

    return m_MoveList[m_CurrIdx++];
}