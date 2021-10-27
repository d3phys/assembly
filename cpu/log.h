/**
 * @file 
 * @brief  Log
 * @author d3phys
 * @date   08.10.2021
 */

#ifndef LOG_H
#define LOG_H

#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <config.h>


static const char LOG_NAME[]= "log.html";

static const char HEADER[] = "<!DOCTYPE html>                      \n"
                                "<html>                            \n"
                                   "<head>                         \n"
                                      "<meta charset=\"utf-8\" />  \n"
                                      "<title>Stack log</title>    \n"
                                   "</head>                        \n"
                                "<body>                            \n"
                                        "<pre><font color=\"navy\">\n"
                                                    "┈┏━╮╭━┓┈┈┈┈┈┈┈\n"
                                                    "┈┃┏┗┛┓┃┈┈┈┈┈┈┈\n"
                                                    "┈╰┓▋▋┏╯┈┈┈┈┈┈┈\n"
                                                    "╭━┻╮╲┗━━━━╮╭╮┈\n"
                                                    "┃▎▎┃╲╲╲╲╲╲┣━╯┈\n"
                                                    "╰━┳┻▅╯╲╲╲╲┃┈┈┈\n"
                                                    "┈┈╰━┳┓┏┳┓┏╯┈┈┈\n"
                                                    "┈┈┈┈┗┻┛┗┻┛┈┈┈┈\n"
                                                    "       </font>\n";  
                                                    
static inline FILE *create_log(); //setvbuf
static FILE *LOG = create_log();
static void close_log();
inline FILE *get_log();


/**
 * @brief  Gets local time
 * @param  fmt  time format
 *
 * Function uses local static buffer with a constant length.
 * It is designed to be called multiple times.
 *
 * @return Local time as a formatted string.
 */
#ifndef NOLOG
static char *local_time(const char *const fmt) 
{
        assert(fmt);

        static const size_t buf_size = 0xFF;
        static char str_tm[buf_size] = {0};

        static time_t t = time(nullptr);
        if (t == -1)
                return nullptr;

        static tm *lt = localtime(&t);
        strftime(str_tm, buf_size, fmt, lt); 

        return str_tm;
}

#endif /* NOLOG */

static inline FILE *create_log()
{
        LOG = fopen(LOG_NAME, "w");
        if (LOG == nullptr) {
                perror("Can't open log file");
                LOG = stderr;
        }

        int err = atexit(close_log);
        if (err)
                perror("Log file will not be closed");

        fprintf(LOG, HEADER);
        fflush(LOG);
        return LOG;
}

inline FILE *get_log()
{
        return LOG;
}

inline void log_flush()
{
        fflush(LOG);
}

static void close_log()
{
        int err = fclose(LOG);
        if (err == EOF)
                perror("Can't close log file");
}


#define $(code) log("%s\n", #code); code

#ifdef NOLOG
#define log_buf(fmt, ...) (void(0))
#else
#define log_buf(fmt, ...)                               \
        do {                                            \
                fprintf(get_log(), fmt, ##__VA_ARGS__); \
        } while (0)
#endif /* NOLOG */

#ifdef NOLOG
#define log(fmt, ...) (void(0))
#else
#define log(fmt, ...)                                                                         \
        do {                                                                                  \
                fprintf(get_log(), "<font color=\"Chocolate\"> >> [%s] At %s %s(%d): </font>" \
                        fmt, local_time("%x %H:%M:%S"),                                       \
                        __FILE__, __func__, __LINE__, ##__VA_ARGS__);                         \
                fflush(get_log());                                                            \
        } while (0)
#endif /* NOLOG */


#endif /* LOG_H */


