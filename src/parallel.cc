#include "parallel.hh"

#include <algorithm>
#include <future>
#include <iostream>
#include <thread>

namespace lidia {

uint32_t GetNumThreads() {
  // TODO(LTE): Return num_threads of RenderConfig
  const uint32_t num_threads =
      std::max(1U, std::thread::hardware_concurrency());

  return num_threads;
}

void parallelFor1D(const std::function<void(unsigned int)>& job,
                   unsigned int nBlocks, unsigned int n) {
  uint32_t num_threads = GetNumThreads();

  if (nBlocks >= n) {
    nBlocks = n;
  }

  if (n < num_threads) {
    num_threads = n;
  }

  ThreadPool pool(num_threads);
  std::vector<std::future<void>> results;

  const unsigned int blockCount = n / nBlocks;
  for (unsigned int block_id = 0; block_id < blockCount; ++block_id) {
    // std::cout << "block id " << block_id << "\n";
    // std::cout << " " << block_id << ", nblocks" << nBlocks << "]\n";
    results.push_back(pool.enqueue([block_id, blockCount, nBlocks, n, job] {
      const unsigned int start_i = block_id * nBlocks;
      const unsigned int end_i =
          (block_id == (blockCount - 1)) ? n : ((block_id + 1) * nBlocks);
      // std::cout << "range[" << start_i << ", " << end_i << "]\n";
      for (unsigned int i = start_i; i < end_i; ++i) {
        job(i);
      }
    }));
  }

  for (auto&& result : results) {
    result.get();
  }
}

void parallelFor2D(const std::function<void(unsigned int, unsigned int)>& job,
                   unsigned int nBlocks_x, unsigned int nBlocks_y,
                   unsigned int nx, unsigned int ny) {
  uint32_t num_threads = GetNumThreads();

  if (nBlocks_x >= nx) {
    nBlocks_x = nx;
  }

  if (nBlocks_y >= ny) {
    nBlocks_y = ny;
  }

  ThreadPool pool(num_threads);
  std::vector<std::future<void>> results;

  const unsigned int blockCount_x = nx / nBlocks_x;
  const unsigned int blockCount_y = ny / nBlocks_y;

  for (unsigned int block_x = 0; block_x < blockCount_x; ++block_x) {
    for (unsigned int block_y = 0; block_y < blockCount_y; ++block_y) {
      results.push_back(pool.enqueue([block_x, block_y, blockCount_x,
                                      blockCount_y, nBlocks_x, nBlocks_y, nx,
                                      ny, job] {
        const unsigned int start_x = block_x * nBlocks_x;
        const unsigned int end_x =
            (block_x == (blockCount_x - 1)) ? nx : ((block_x + 1) * nBlocks_x);
        const unsigned int start_y = block_y * nBlocks_y;
        const unsigned int end_y =
            (block_y == (blockCount_y - 1)) ? ny : ((block_y + 1) * nBlocks_y);
        for (unsigned int y = start_y; y < end_y; ++y) {
          for (unsigned int x = start_x; x < end_x; ++x) {
            job(x, y);
          }
        }
      }));
    }
  }

  for (auto&& result : results) {
    result.get();
  }
}

}  // namespace lidia
