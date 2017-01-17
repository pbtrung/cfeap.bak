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

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <errno.h> 
#include <string.h>

#define RED    "\e[31m"
#define GREEN  "\e[32m"
#define YELLOW "\e[33m"
#define WHITE  "\e[1m"

// COLOR_X resets the colour.
#define COLOR_X "\e[m"

#ifdef NDEBUG
    #define debug(M, ...)
#else
    #define debug(M, ...) fprintf(stderr, "DEBUG %s:%d:%s: " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, RED "[ERROR]" COLOR_X " (%s:%d:%s: errno: %s) " M "\n", __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, YELLOW "[WARN]" COLOR_X " (%s:%d:%s: errno: %s) " M "\n", __FILE__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, WHITE "[INFO]" COLOR_X " (%s:%d:%s) " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno = 0; goto error; }
#define check_no_msg(A, ...) if(!(A)) { errno = 0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno = 0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno = 0; goto error; }

#endif //__DEBUG_H__