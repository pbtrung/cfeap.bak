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

#include "utils/cmdl-args.h"
#include "sput.h"

static void test_cargs();
void test_case_a_cargs_parse();
void test_case_b_cargs_parse();
void test_case_c_cargs_parse();

static void test_cargs()
{
    test_case_a_cargs_parse();
    test_case_b_cargs_parse();
    test_case_c_cargs_parse();
}

void test_case_a_cargs_parse()
{
    int argc = 3;
    char *argv[] = {"cfeap", "-i", "input.txt"};
    bstring input_fn = NULL, output_fn = NULL, log_fn = NULL;

    cargs_parse(argc, argv, &input_fn, &output_fn, &log_fn);
    bstring tmp = bfromcstr(argv[2]);
    sput_fail_if(biseq(input_fn, tmp) != 1, "Case a: Input file name");
    bassigncstr(tmp, "cfeap-output.txt");
    sput_fail_if(biseq(output_fn, tmp) != 1, "Case a: Output file name");
    bassigncstr(tmp, "cfeap-log.txt");
    sput_fail_if(biseq(log_fn, tmp) != 1, "Case a: Log file name");

    bdestroy(input_fn);
    bdestroy(output_fn);
    bdestroy(log_fn);
    bdestroy(tmp);
}

void test_case_b_cargs_parse()
{
    int argc = 5;
    char *argv[] = {"cfeap", "-i", "input.txt", "-o", "output.txt"};
    bstring input_fn = NULL, output_fn = NULL, log_fn = NULL;

    cargs_parse(argc, argv, &input_fn, &output_fn, &log_fn);
    bstring tmp = bfromcstr(argv[2]);
    sput_fail_if(biseq(input_fn, tmp) != 1, "Case b: Input file name");
    bassigncstr(tmp, argv[4]);
    sput_fail_if(biseq(output_fn, tmp) != 1, "Case b: Output file name");
    bassigncstr(tmp, "cfeap-log.txt");
    sput_fail_if(biseq(log_fn, tmp) != 1, "Case b: Log file name");

    bdestroy(input_fn);
    bdestroy(output_fn);
    bdestroy(log_fn);
    bdestroy(tmp);
}

void test_case_c_cargs_parse()
{
    int argc = 7;
    char *argv[] = {"cfeap", "-i", "input.txt", "-o", "output.txt", "-l", "log.txt"};
    bstring input_fn = NULL, output_fn = NULL, log_fn = NULL;

    cargs_parse(argc, argv, &input_fn, &output_fn, &log_fn);
    bstring tmp = bfromcstr(argv[2]);
    sput_fail_if(biseq(input_fn, tmp) != 1, "Case c: Input file name");
    bassigncstr(tmp, argv[4]);
    sput_fail_if(biseq(output_fn, tmp) != 1, "Case c: Output file name");
    bassigncstr(tmp, argv[6]);
    sput_fail_if(biseq(log_fn, tmp) != 1, "Case c: Log file name");

    bdestroy(input_fn);
    bdestroy(output_fn);
    bdestroy(log_fn);
    bdestroy(tmp);
}