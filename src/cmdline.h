#include "board.h"
#include "seearch.h"
#include "movegen.h"

class CmdLine
{
public:
    CmdLine();
private:
    std::vector<Board> m_Boards;
};