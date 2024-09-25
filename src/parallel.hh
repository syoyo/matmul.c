#pragma once

#include <functional>

#include "ThreadPool.h"

namespace lidia {

uint32_t GetNumThreads();

///
/// Simple 1D parallel for.
///
/// Each job will receive the index range of `[i * nBlock, i * nBlock + (nBlock - 1)]`
/// where `i` is the i'th job id(`i * nBlocks < n`)
///
/// @param[job] Job function
/// @param[in] nBlock The number of blocks
/// @param[in] n The number of tasks(Usually `nBlocks < n`)
///
///

void parallelFor1D(const std::function<void(unsigned int)>& job,
                   unsigned int nBlocks, unsigned int n);

///
/// Simple 2D parallel for.
///
/// Each job will receive the index range of `[x * nBlocks_x, x * nBlocks_x + (nBlocks_x - 1)] x [y * nBlocks_y, y * nBlocks_y + (nBlocks_y - 1)]`
///
/// @param[job] Job function
/// @param[in] nBlocks_x The number of blocks in dim x.
/// @param[in] nBlocks_y The number of blocks in dim y.
/// @param[in] nx The number of tasks in dim x(Usually `nBlocks_x < nx`)
/// @param[in] nx The number of tasks in dim y(Usually `nBlocks_y < ny`)
///
void parallelFor2D(const std::function<void(unsigned int, unsigned int)>& job,
                   unsigned int nBlocks_x, unsigned int nBlocks_y,
                   unsigned int nx, unsigned int ny);

} // namespace lidia
