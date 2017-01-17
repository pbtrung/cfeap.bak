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

#include <stdlib.h>

#include "linalg/cblas-wrapper.h"
#include "sput.h"

static void test_cblw();
void test_cblw_scalar_vec_mul_x();
void test_cblw_scalar_mat_mul_x();
void test_cblw_mat_vec_mul();
void test_cblw_mat_mat_mul();

static void test_cblw()
{
    test_cblw_scalar_vec_mul_x();
    test_cblw_scalar_mat_mul_x();
    test_cblw_mat_vec_mul();
    test_cblw_mat_mat_mul();
}

void test_cblw_scalar_vec_mul_x()
{
    double a = 2, *x;
    size_t dim = 3;
    x = malloc(dim * sizeof(double));

    for (int i = 0; i < 3; i++) {
        x[i] = (double)(i+1);
    }

    cblw_scalar_vec_mul_x(dim, a, x);
    sput_fail_if(x[0] != 2, "Scalar x Vec x[0]");

    free(x);
}

void test_cblw_scalar_mat_mul_x()
{
    double a = 2, *X;
    size_t dim = 3;
    X = malloc(dim * dim * sizeof(double));

    for (int i = 0; i < dim * dim; i++) {
        X[i] = (double)(i+1);
    }

    cblw_scalar_mat_mul_x(dim, dim, a, X);
    sput_fail_if(X[0] != 2, "Scalar x Mat X[0]");

    free(X);
}

void test_cblw_mat_vec_mul()
{
    double *A, *x, *y;
    size_t dim = 3;
    A = malloc(dim * dim * sizeof(double));
    x = malloc(dim * sizeof(double));
    y = malloc(dim * sizeof(double));

    for (int i = 0; i < dim * dim; i++) {
        A[i] = (double)(i+1);
    }
    for (int i = 0; i < 3; i++) {
        x[i] = (double)(i+1);
    }

    cblw_mat_vec_mul(dim, dim, A, x, y);
    sput_fail_if(y[0] != 14, "Mat x Vec y[0]");

    free(A);
    free(x);
    free(y);
}

void test_cblw_mat_mat_mul()
{
    double *A, *B, *C;
    size_t dim = 3;
    A = malloc(dim * dim * sizeof(double));
    B = malloc(dim * dim * sizeof(double));
    C = malloc(dim * dim * sizeof(double));

    for (int i = 0; i < dim * dim; i++) {
        A[i] = (double)(i + 1);
        B[i] = (double)(i + 1);
    }

    cblw_mat_mat_mul(dim, dim, dim, A, B, C);
    sput_fail_if(C[0] != 30, "Mat x Mat C[0]");

    free(A);
    free(B);
    free(C);
}