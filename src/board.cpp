#include "board.h"


Board::Board()
    : m_Colors(), m_Threats(), m_SideToMove(Color::RED)
{
    
}

void Board::makeMove(Move m)
{
    addPiece(m.sqIdx, m_SideToMove);
    m_SideToMove = flip(m_SideToMove);
    calcThreatsFor(Color::RED);
    calcThreatsFor(Color::YELLOW);
}

// 49 bit perfect hash
// from https://gamedev.net/forums/topic/644765-hashing-connect-4-board-for-transposition-tableneed-some-help/5072946/
uint64_t Board::key() const
{
    uint64_t occupied = m_Colors[0] | m_Colors[1];
    return ((occupied << 1) | BOTTOM_ROW) ^ m_Colors[static_cast<int>(Color::RED)];
}

std::string Board::getString() const
{
	const char* between = "+---+---+---+---+---+---+---+\n";
	std::string result;
	Bitboard redLocs = threatsFor(Color::RED);
	Bitboard yellowLocs = threatsFor(Color::YELLOW);
	for (int j = 5; j >= 0; j--)
	{
		result += between;
		for (int i = j; i < j + 56; i += 8)
		{
			result += "| ";
			Bitboard square = 1ull << i;
			Color color = Color::RED;
            if (square & all())
			{
                if (square & piecesFor(Color::RED))
                    color = Color::RED;
                else if (square & piecesFor(Color::YELLOW))
                    color = Color::YELLOW;
				result += "\033[38;2;";
				result += color == Color::RED ? "255;0;0m" : "255;255;0m";
				result += "O";
				result += "\033[0m";
				// result += color == Color::RED ? 
			}
			else
			{
				if (square & redLocs)
				{
					if (square & yellowLocs)
					{
						result += "\033[38;2;";
						result += "255;127;0m";
						result += "W";
						result += "\033[0m";
					}
					else
					{
						result += "\033[38;2;";
						result += "255;0;0m";
						result += "W";
						result += "\033[0m";
					}
				}
				else if (square & yellowLocs)
				{
					result += "\033[38;2;";
					result += "255;255;0m";
					result += "W";
					result += "\033[0m";
				}
				else
				{
					result += ' ';
				}
			}
			result += ' ';
		}
		result += "|\n";
	}
	result += between;
	return result;
}

void Board::addPiece(uint32_t sq, Color color)
{
    assert((m_Colors[static_cast<int>(color)] & (1ull << sq)) == 0);
    m_Colors[static_cast<int>(color)] |= (1ull << sq);
}

// from http://blog.gamesolver.org/solving-connect-four/06-bitboard/#:~:text=Checking%20for%20aligment
bool Board::isLoss() const
{
    Bitboard pieces = m_Colors[static_cast<int>(flip(m_SideToMove))];
    
    Bitboard m = pieces & (pieces >> 8);
    if (m & (m >> 16))
        return true;

    m = pieces & (pieces >> 9);
    if (m & (m >> 18))
        return true;

    m = pieces & (pieces >> 7);
    if (m & (m >> 14))
        return true;

    m = pieces & (pieces >> 1);
    if (m & (m >> 2))
        return true;
    
    return false;
}

void Board::calcThreatsFor(Color color)
{
    m_Threats[static_cast<int>(color)] = calcThreats(m_Colors[static_cast<int>(color)], all());
}

Bitboard Board::calcThreats(Bitboard us, Bitboard all)
{
	Bitboard vertical = (us << 1) & (us << 2) & (us << 3);
	
	Bitboard tmp = (us << 8) & (us << 2 * 8);
	Bitboard horizontal = tmp & (us << 3 * 8);
	horizontal |= tmp & (us >> 8);
	tmp = (us >> 8) & (us >> 2 * 8);
	horizontal |= tmp & (us >> 3 * 8);
	horizontal |= tmp & (us << 8);

	tmp = (us << 7) & (us << 2 * 7);
	Bitboard diag1 = tmp & (us << 3 * 7);
	diag1 |= tmp & (us >> 7);
	tmp = (us >> 7) & (us >> 2 * 7);
	diag1 |= tmp & (us >> 3 * 7);
	diag1 |= tmp & (us << 7);

	tmp = (us << 9) & (us << 2 * 9);
	Bitboard diag2 = tmp & (us << 3 * 9);
	diag2 |= tmp & (us >> 9);
	tmp = (us >> 9) & (us >> 2 * 9);
	diag2 |= tmp & (us >> 3 * 9);
	diag2 |= tmp & (us << 9);

	return (vertical | horizontal | diag1 | diag2) & ~all & IN_BOARD;
}
