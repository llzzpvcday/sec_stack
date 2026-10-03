#include <stdio.h>
#include <time.h>

#define RESET "\033[1;0m"
#define BLUE  "\033[1;34m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"

#define LOG_ENABLED

#ifdef LOG_ENABLED

FILE *log_file = NULL;

void log_init() {
  // Source - https://stackoverflow.com/a/10917605
  // Posted by smichak, modified by community. See post 'Timeline' for change
  // history Retrieved 2026-10-03, License - CC BY-SA 3.0

  char filename[32];
  time_t now   = time(NULL);
  struct tm *t = localtime(&now);

  strftime(filename, sizeof(filename) - 1, "%d-%m-%Y-%H:%M.log", t);
  printf("Log file: %s\n", filename);
  log_file = fopen(filename, "w");
  setvbuf(log_file, NULL, _IONBF, 0);
}

void log_close() { fclose(log_file); }

#define $log(...)                                                              \
  {                                                                            \
    time_t now   = time(NULL);                                                 \
    struct tm *t = localtime(&now);                                            \
    char buffer[20];                                                           \
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", t);                  \
    fprintf(log_file, __VA_ARGS__);                                            \
    fprintf(stderr, __VA_ARGS__);                                              \
  }

#define $error(...)                                                            \
  {                                                                            \
    time_t now   = time(NULL);                                                 \
    struct tm *t = localtime(&now);                                            \
    char buffer[20];                                                           \
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", t);                  \
    fprintf(log_file, RED "%20s - [ERROR] - " RESET, buffer);                  \
    fprintf(log_file, __VA_ARGS__);                                            \
    fprintf(log_file, RESET);                                                  \
    fprintf(stderr, RED "%20s - [ERROR] - " RESET, buffer);                    \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, RESET);                                                    \
  }
#define $info(...)                                                             \
  {                                                                            \
    time_t now   = time(NULL);                                                 \
    struct tm *t = localtime(&now);                                            \
    char buffer[20];                                                           \
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", t);                  \
    fprintf(log_file, GREEN "%20s - [INFO] - " RESET, buffer);                 \
    fprintf(log_file, __VA_ARGS__);                                            \
    fprintf(log_file, RESET);                                                  \
    fprintf(stderr, GREEN "%20s - [INFO] - " RESET, buffer);                   \
    fprintf(stderr, __VA_ARGS__);                                              \
    fprintf(stderr, RESET);                                                    \
  }

#else
#define $log(...)
#define $info(...)
#define $error(...)
void log_init() {}
void log_close() {}
#endif
