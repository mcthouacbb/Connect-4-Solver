#include <cstdint>
#include <cstddef>
#include <vector>
#include "defs.h"

enum class TTBound : uint8_t
{
    NONE,
    LOWER_BOUND,
    EXACT,
    UPPER_BOUND
};

struct TTEntry
{
    uint64_t key;
    int16_t score;
    Move move;
    uint8_t depth;
    TTBound bound;
};

class TT
{
public:
    static constexpr size_t DEFAULT_SIZE = 32;

    TT();
    void setSize(size_t mb);

    TTEntry* probe(uint64_t key, bool& found, int& ttScore, Move& ttMove, int& ttDepth, TTBound& ttBound);
    void store(TTEntry* entry, uint64_t key, int score, Move move, int depth, TTBound bound);
private:
    std::vector<TTEntry> m_Entries;
};
