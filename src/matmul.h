#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void matmul(float* A, float* B, float* C, const int M, const int N, const int K);
void matmul_naive(float* A, float* B, float* C, const int M, const int N, const int K);

#ifdef __cplusplus
}
#endif
