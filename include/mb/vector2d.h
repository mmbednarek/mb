#ifndef LIBMB_VECTOR2D_H
#define LIBMB_VECTOR2D_H
#include "int.h"
#include "result.h"
#include <array>
#include <bits/allocator.h>
#include <cstring>
#include <unordered_map>
#include <vector>

namespace mb {


template<typename T, mb::size ChunkSize = 4, mb::size MaxChunkId = 128>
class vector2d {
    using ChunkId = mb::size;
    using Chunk = std::array<T, ChunkSize * ChunkSize>;

    static constexpr ChunkId find_chunk_id(int x, int y) {
        const auto chunk_x = x >= 0 ? x / ChunkSize : x / ChunkSize - 1;
        const auto chunk_y = y >= 0 ? y / ChunkSize : y / ChunkSize - 1;
        return chunk_x + chunk_y * MaxChunkId;
    }

    std::unordered_map<ChunkId, Chunk> m_chunks;
public:
    vector2d() = default;

    mb::result<T &> at(int x, int y) {
        const auto chunk_id = find_chunk_id(x, y);
        auto chunk_it = m_chunks.find(chunk_id);
        if (chunk_it == m_chunks.end()) {
            return mb::error("element not found");
        }

        const auto local_x = x % ChunkSize;
        const auto local_y = y % ChunkSize;

        auto &chunk = chunk_it->second;
        return chunk[local_x + local_y * ChunkSize];
    }

    void set(int x, int y, T &&value) {
        const auto chunk_id = find_chunk_id(x, y);
        auto chunk_it = m_chunks.find(chunk_id);
        const auto local_x = x % ChunkSize;
        const auto local_y = y % ChunkSize;
        if (chunk_it != m_chunks.end()) {
            auto &chunk = chunk_it->second;
            chunk[local_x + local_y * ChunkSize] = value;
            return;
        }
        m_chunks[chunk_id] = Chunk();
        m_chunks[chunk_id][local_x + local_y * ChunkSize] = value;
    }
};

}// namespace mb

#endif//LIBMB_VECTOR2D_H
