#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include <iomap.h>
#include <thrw.h>
#include <assembly.h>
#include "compiler.h"
#include "parse.h"


struct config_t {
       char *input = nullptr;
       char *output = nullptr;
       int preprocess = 0;
};

static int preprocess_code(const char *const src_name, 
                           const char *const dst_name);

static int compile_code(const char *const src_name, 
                        const char *const dst_name);

int main(int argc, char *argv[])
{
        config_t cfg = {0};

        int opt = 0;
        while ((opt = getopt(argc, argv, "i:o:s")) != -1) {
                switch (opt) {
                case 's':
                        cfg.preprocess = 1;
                        break;
                case 'o':
                        cfg.output = optarg;
                        break;
                case 'i':
                        cfg.input  = optarg;
                        break;
                default:
                        break;
                }
        }

        thrw(exit(1), cfg.input  == nullptr, "No input file provided\n");
        thrw(exit(1), cfg.output == nullptr, "No output file provided\n");

        char prep[64] = {0};
        strcat(prep, cfg.output);
        strcat(prep, PREPROC_EXT);

        int error = 0;

        error = preprocess_code(cfg.input, prep);
        thrw(exit(1), (error), "Preprocessing failed\n");

        error = compile_code(prep, cfg.output);
        thrw(exit(1), (error), "Compilation failed\n");

        if (!cfg.preprocess) {
                error = remove(prep);
                thrw(exit(1), (error), 
                "Can't remove preprocessed file: %s\n", strerror(errno));
        }

        return 0;
}

static int compile_code(const char *const src_name, 
                        const char *const dst_name)
{
        assert(src_name);
        assert(dst_name);

        size_t predict_size  = 0;
        size_t bytes_written = 0;
        size_t size = 0;

        char *src_buf = nullptr;
        char *dst_buf  = nullptr;

        int error = 0;

        code_t code = {0};

        error = map_in(src_name, &src_buf, &size);
        thrw(goto cup0, (error), "Mapping preprocess input file failed\n");

        error = construct_asm_code(&code, src_buf);
        thrw(goto cup1, (error), "Code construction failed\n");
        
        predict_size = sizeof(header_t) + 
                       code.n_cmds * (sizeof(cmd_t) + sizeof(arg_t));

        error = map_out(dst_name, &dst_buf, predict_size);
        thrw(goto cup2, (error), "Mapping binary file failed\n");

        error = compile_asm(&code, dst_buf, &bytes_written);
        thrw(goto cup3, (error), "Compilation failed\n");
        
        error = truncate(dst_name, bytes_written);
        thrw(goto cup3, (error), 
        "Can't truncate file: %s\n", strerror(errno));


cup3:
        munmap(dst_buf, predict_size);
cup2:
        destruct_asm_code(&code);
cup1:
        munmap(src_buf, size);
cup0:
        return error;
}

static int preprocess_code(const char *const src_name, 
                           const char *const dst_name)
{
        assert(src_name);
        assert(dst_name);

        int error = 0;

        FILE *file = nullptr;
        char *buf  = nullptr;

        code_t code = {0};

        size_t size = 0;
        error = map_in(src_name, &buf, &size);
        thrw(goto map, (error), "Can't map input file\n");

        error = construct_asm_code(&code, buf);
        thrw(goto mix, (error), "Code construction failed\n");

        file = fopen(dst_name, "w");
        thrw(goto mix, (file == nullptr), "Can't open output file\n");

        preprocess_asm(&code, file);
        thrw(goto mix, (error), "Code preprocessoring failed\n");

        error = fclose(file);
        thrw(goto mix, (error == EOF), "Closing file failed\n");

mix:
        printf("Freee it\n");
        destruct_asm_code(&code);
        munmap(buf, size);

map:
        return error;
}


