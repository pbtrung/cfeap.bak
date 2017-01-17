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

static int cargs_print_help(void *argtable[], char program_name[]);

static int cargs_print_error(struct arg_end *end, char program_name[]);

static int cargs_export_file_name(struct arg_file *arg_input_fn, struct arg_file *arg_output_fn,
                                  struct arg_file *arg_log_fn, bstring *input_fn, bstring *output_fn,
                                  bstring *log_fn);

int cargs_parse(int argc, char *argv[], bstring *input_fn,
                bstring *output_fn, bstring *log_fn)
{
    struct arg_lit *help, *version;
    struct arg_file *arg_input_fn, *arg_output_fn, *arg_log_fn;
    struct arg_end *end;

    void *argtable[] = {
        help          = arg_litn("h", "help", 0, 1, "display this help and exit"),
        version       = arg_litn("v", "version", 0, 1, "display version info and exit"),
        arg_input_fn  = arg_filen("i", "input", "input_file", 1, 1, "input file (required)"),
        arg_output_fn = arg_filen("o", "output", "output_file", 0, 1, "output file (optional)"),
        arg_log_fn    = arg_filen("l", "log", "log_file", 0, 1, "log file (optional)"),
        end           = arg_end(20),
    };

    int rc = 0;
    char program_name[] = "cfeap";

    int nerrors = 0;
    nerrors = arg_parse(argc, argv, argtable);

    // special case: '--help' takes precedence over error reporting
    if(help->count > 0) {
        rc = cargs_print_help(argtable, program_name);
        goto exit;
    }

    // If the parser returned any errors, then display them and exit.
    if(nerrors > 0) {
        rc = cargs_print_error(end, program_name);
        goto exit;
    }

    rc = cargs_export_file_name(arg_input_fn, arg_output_fn, arg_log_fn,
                                input_fn, output_fn, log_fn);

    exit:
    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return rc;
}

static int cargs_print_help(void *argtable[], char program_name[])
{
    int rc = 0;

    printf("Usage: %s", program_name);
    arg_print_syntax(stdout, argtable, "\n");
    printf("C Finite Element Analysis Program (CFEAP).\n\n");
    arg_print_glossary(stdout, argtable, "  %-25s %s\n");

    return rc;
}

static int cargs_print_error(struct arg_end *end, char program_name[])
{
    int rc = -1;

    arg_print_errors(stdout, end, program_name);
    printf("Try '%s --help' for more information.\n", program_name);

    return rc;
}

static int cargs_export_file_name(struct arg_file *arg_input_fn, struct arg_file *arg_output_fn,
                                  struct arg_file *arg_log_fn, bstring *input_fn, bstring *output_fn,
                                  bstring *log_fn)
{
    int rc = 0;

    if(*input_fn == NULL) {
        *input_fn = bfromcstr(arg_input_fn->basename[0]);
    } else {
        bassigncstr(*input_fn, arg_input_fn->basename[0]);
    }
    if(arg_output_fn->count == 1) {
        if(*output_fn == NULL) {
            *output_fn = bfromcstr(arg_output_fn->basename[0]);
        } else {
            bassigncstr(*output_fn, arg_output_fn->basename[0]);
        }
    } else if(arg_output_fn->count == 0) {
        if(*output_fn == NULL) {
            *output_fn = bfromcstr("cfeap-output.txt");
        } else {
            bassigncstr(*output_fn, "cfeap-output.txt");
        }
    }
    if(arg_log_fn->count == 1) {
        if(*log_fn == NULL) {
            *log_fn = bfromcstr(arg_log_fn->basename[0]);
        } else {
            bassigncstr(*log_fn, arg_log_fn->basename[0]);
        }
    } else if(arg_log_fn->count == 0) {
        if(*log_fn == NULL) {
            *log_fn = bfromcstr("cfeap-log.txt");
        } else {
            bassigncstr(*log_fn, "cfeap-log.txt");
        }
    }

    return rc;
}