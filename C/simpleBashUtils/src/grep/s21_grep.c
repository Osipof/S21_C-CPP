#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

struct flags {
  int eflag;
  int iflag;
  int vflag;
  int cflag;
  int lflag;
  int nflag;
  int hflag;
  int sflag;
  int fflag;
  int oflag;
} flagData = {0};

char pattern[4096] = "";

void printUsages();
void startMain(int argc, char **argv);
int parseOptions(int argc, char **argv);
int takeFile(char **argv, int currentFile, FILE **fp);
int fFlag();
int eFlag();
void oFlag(char *buffer, regex_t regex, size_t nmatch, regmatch_t *pmatch,
           int lineNumber);

int main(int argc, char **argv) {
  if (argc > 2)
    startMain(argc, argv);
  else
    printUsages();
  return 0;
}

void startMain(int argc, char **argv) {
  int errorFlag = 0;
  if (parseOptions(argc, argv)) {
    errorFlag++;
  }
  if (!errorFlag) {
    char buffer[BUFFER_SIZE];
    FILE *fp;
    regex_t regex;
    size_t nmatch = 10;
    regmatch_t pmatch[nmatch];
    if (!flagData.eflag && !flagData.fflag) {
      strcpy(pattern, argv[optind]);
      optind++;
    }
    int currentFile = optind;
    int compare = 0, regflag = REG_EXTENDED;
    if (flagData.vflag) {
      compare = REG_NOMATCH;
    }
    if (flagData.iflag) {
      regflag = REG_ICASE;
    }
    if (regcomp(&regex, pattern, regflag) != 0) {
      fprintf(stderr, "Could not compile regex\n");
    } else {
      while (currentFile < argc) {
        if (currentFile != argc) {
          if (takeFile(argv, currentFile, &fp)) break;
        }
        int count = 0, lineNumber = 1;
        while (fgets(buffer, BUFFER_SIZE, (fp == NULL ? stdin : fp))) {
          if (strchr(buffer, '\n')) *(strchr(buffer, '\n')) = '\0';
          if (regexec(&regex, buffer, nmatch, pmatch, 0) == compare) {
            if (flagData.cflag) {
              count++;
              if (flagData.lflag) {
                break;
              }
            } else if (flagData.lflag) {
              if (optind != currentFile) printf("\n");
              printf("%s\n", argv[currentFile]);
              break;
            } else if (flagData.oflag && !flagData.vflag) {
              oFlag(buffer, regex, nmatch, pmatch, lineNumber);
            } else {
              if (!flagData.hflag && (argc - optind) > 1) {
                printf("%s:", argv[currentFile]);
              }
              if (flagData.nflag) printf("%d:", lineNumber);
              fprintf(stdout, "%s\n", buffer);
            }
          }
          lineNumber++;
        }
        if (flagData.cflag) {
          if (!flagData.hflag && (argc - optind) > 1) {
            printf("%s:", argv[currentFile]);
          }
          printf("%d\n", count);
          if (flagData.lflag) {
            printf("%s\n", argv[currentFile]);
          }
        }
        fclose(fp);
        currentFile++;
      }
    }
    regfree(&regex);
  }
}

void oFlag(char *buffer, regex_t regex, size_t nmatch, regmatch_t *pmatch,
           int lineNumber) {
  char *bufferC = buffer;
  int printNum = 0;
  for (size_t m = 0; m < nmatch; m++) {
    if (regexec(&regex, bufferC, nmatch, pmatch, 0)) break;
    int offset = 0;
    for (size_t g = 0; g < nmatch; g++) {
      if (pmatch[g].rm_so == (regoff_t)-1 || pmatch[g].rm_so == pmatch[g].rm_eo)
        break;
      if (g == 0) offset = pmatch[g].rm_eo;
      char bufferCopy[strlen(bufferC + 1)];
      strcpy(bufferCopy, bufferC);
      bufferCopy[pmatch[g].rm_eo] = 0;
      if (flagData.nflag && printNum == 0) {
        printf("%d:", lineNumber);
        printNum++;
      }
      printf("%s\n", bufferCopy + pmatch[g].rm_so);
    }
    bufferC += offset;
  }
}

int takeFile(char **argv, int currentFile, FILE **fp) {
  int breakFlag = 0;
  *fp = fopen(argv[currentFile], "r");
  if (*fp == NULL) {
    if (!flagData.sflag) {
      fprintf(stderr, "%s: %s: No such file or directory", argv[0],
              argv[currentFile]);
    }
    breakFlag++;
  }
  return breakFlag;
}

int parseOptions(int argc, char **argv) {
  int errorFlag = 0;
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o?")) != -1) {
    switch (opt) {
      case 'e':
        flagData.eflag++;
        if (eFlag()) {
          errorFlag++;
        }
        break;
      case 'i':
        flagData.iflag++;
        break;
      case 'v':
        flagData.vflag++;
        break;
      case 'c':
        flagData.cflag++;
        break;
      case 'l':
        flagData.lflag++;
        break;
      case 'n':
        flagData.nflag++;
        break;
      case 'h':
        flagData.hflag++;
        break;
      case 's':
        flagData.sflag++;
        break;
      case 'f':
        flagData.fflag++;
        if (fFlag()) {
          errorFlag++;
        }
        break;
      case 'o':
        flagData.oflag++;
        break;
      case '?':
        printUsages();
        errorFlag++;
    }
  }
  return errorFlag;
}

int eFlag() {
  int errorFlag = 0;
  if (optarg) {
    int len = strlen(pattern);
    if (len > 0) {
      pattern[len] = '|';
      pattern[len + 1] = '\0';
    }
    strcat(pattern, optarg);
  } else {
    printf("use pattern!");
    errorFlag++;
  }
  return errorFlag;
}

int fFlag() {
  int errorFlag = 0;
  if (optarg) {
    FILE *file;
    file = fopen(optarg, "r");
    if (file == NULL) {
      printf("n/a\n");
    } else {
      int count = 0;
      char str[1024];
      int len = strlen(pattern);
      if (len > 0) {
        pattern[len] = '|';
        pattern[len + 1] = '\0';
      }
      while (fgets(str, 300, file) != NULL) {
        strcat(pattern, str);
        count++;
      }
      if (!count) {
        printf("File is empty\n");
      }
      fclose(file);
    }
  } else {
    printf("use pattern!");
    errorFlag++;
  }
  return errorFlag;
}

void printUsages() {
  printf("usage: grep [-ivclnhso] [-e pattern] [-f file ...]\n");
}