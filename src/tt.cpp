#include "tt.h"

namespace
{

uint64_t splitMix64(uint64_t x)
{
    x ^= x >> 30;
    x *= 0xbf58476d1ce4e5b9ULL;
    x ^= x >> 27;
    x *= 0x94d049bb133111ebULL;
    x ^= x >> 31;
    return x;
}

}

TT::TT()
{
    setSize(DEFAULT_SIZE);
}

void TT::setSize(size_t mb)
{
    assert(mb & (mb - 1));
    size_t bytes = mb * 1024 * 1024;
    size_t entries = bytes / sizeof(TTEntry);
    m_Entries.resize(entries);
}

TTEntry* TT::probe(uint64_t key, bool& found, int& ttScore, Move& ttMove, int& ttDepth, TTBound& ttBound)
{
    uint64_t hash = splitMix64(key);
    size_t index = hash & (m_Entries.size() - 1);
    TTEntry* entry = &m_Entries[index];
    if (entry->key == key)
    {
        found = true;
        ttScore = static_cast<int>(entry->score);
        ttMove = entry->move;
        ttDepth = entry->depth;
        ttBound = entry->bound;
    }
    else
        found = false;
    return entry;
}

void TT::store(TTEntry* entry, uint64_t key, int score, Move move, int depth, TTBound bound)
{
    entry->key = key;
    entry->score = score;
    entry->move = move;
    entry->depth = depth;
    entry->bound = bound;
}
