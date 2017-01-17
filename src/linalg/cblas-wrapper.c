/*************************************************************************************
 * Copyright (C) 2017, Trung Pham <me@trungbpham.com>                                *
 * All rights reserved.                                                              *
 *                                                                                   *
 * Redistribution and use in source and binary forms, with or without                *
 * modification, are permitted provided that the following conditions are met:       *
 *                                                                                   *
 *       * Redistributions of source code must retain the above copyright notice,    *
 *       this list of conditions and the following disclaimer.                       *
 *                                                                                   *
 *       * Redistributions in binary form must reproduce the above copyright notice, *
 *       this list of conditions and the following disclaimer in the documentation   *
 *       and/or other materials provided with the distribution.                      *
 *                                                                                   *
 *       * Neither the name of cfeap nor the names of its contributors may be used   *
 *       to endorse or promote products derived from this software without specific  *
 *       prior written permission.                                                   *
 *                                                                                   *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"       *
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE         *
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE    *
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE      *
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL        *
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR        *
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER        *
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,     *
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE     *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.              *
 *************************************************************************************/

#include <string.h>
#include "linalg/cblas-wrapper.h"

int cblw_scalar_vec_mul_x(size_t dim, double a, double *x)
{
    int rc = 0;

    size_t incx = 1;
    cblas_dscal(dim, a, x, incx);

    return rc;
}

int cblw_scalar_mat_mul_x(size_t col, size_t row, double a, double *X)
{
    int rc = 0;

    size_t dim = col * row;
    cblw_scalar_vec_mul_x(dim, a, X);

    return rc;
}

int cblw_scalar_vec_mul_y(size_t dim, double a, double *x, double *y)
{
    int rc = 0;

    size_t incx = 1;
    size_t incy = 1;
    double tmp[dim];
    memset(tmp, 0, dim * sizeof(double));
    cblas_daxpy(dim, a, x, incx, tmp, incy);
    cblas_dcopy(dim, tmp, incx, y, incy);

    return rc;
}

int cblw_scalar_mat_mul_y(size_t col, size_t row, double a, double *X, double *Y)
{
    int rc = 0;

    size_t dim = col * row;
    cblw_scalar_vec_mul_y(dim, a, X, Y);

    return rc;
}

int cblw_mat_vec_mul(size_t col, size_t row, double *A, double *x, double *y)
{
    int rc = 0;

    double alpha = 1.0;
    double beta = 0.0;
    size_t lda = col;
    size_t incx = 1;
    size_t incy = 1;

    cblas_dgemv(CblasRowMajor, CblasNoTrans, col, row, alpha, A, lda, x, incx, beta, y, incy);

    return rc;
}

int cblw_mat_mat_mul(size_t rowA, size_t colB, size_t colA_rowB, double *A, double *B, double *C)
{
    int rc = 0;

    double alpha = 1.0;
    double beta = 0.0;
    size_t lda = rowA;
    size_t ldb = colB;
    size_t ldc = rowA;

    memset(C, 0, rowA * colB * sizeof(double));
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                rowA, colB, colA_rowB, alpha, A, lda, B,
                ldb, beta, C, ldc);

    return rc;
}