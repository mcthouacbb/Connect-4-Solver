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

int storeScore(int score, int ply)
{
    return isWinScore(score) ? score + (score < 0 ? ply : -ply) : score;
}

int probeScore(int score, int ply)
{
    return isWinScore(score) ? score - (score < 0 ? ply : -ply) : score;
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

TTEntry* TT::probe(uint64_t key, int ply, bool& found, int& ttScore, Move& ttMove, int& ttDepth, TTBound& ttBound)
{
    uint64_t hash = splitMix64(key);
    size_t index = hash & (m_Entries.size() - 1);
    TTEntry* entry = &m_Entries[index];
    if (entry->key == key)
    {
        found = true;
        ttScore = probeScore(entry->score, ply);
        ttMove = entry->move;
        ttDepth = entry->depth;
        ttBound = entry->bound;
    }
    else
        found = false;
    return entry;
}

void TT::store(TTEntry* entry, uint64_t key, int ply, int score, Move move, int depth, TTBound bound)
{
    entry->key = key;
    entry->score = static_cast<int16_t>(storeScore(score, ply));
    entry->move = move;
    entry->depth = static_cast<uint8_t>(depth);
    entry->bound = bound;
}
