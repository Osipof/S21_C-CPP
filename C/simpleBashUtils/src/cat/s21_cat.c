#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

struct flags {
  int bflag;
  int nflag;
  int sflag;
  int vflag;
  int eflag;
  int tflag;
} flagData = {0};

struct option const long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {"show-nonprinting", no_argument, NULL, 'v'},
    {"show-ends", no_argument, NULL, 'E'},
    {"show-tabs", no_argument, NULL, 'T'},
    {NULL, 0, NULL, 0},
};

int isAscii(int c);
int toAscii(int c);
void startMain(int argc, char **argv);
int parseOptions(int argc, char **argv);
void printCattedFile(FILE *fp);

int main(int argc, char **argv) {
  startMain(argc, argv);
  return 0;
}

void startMain(int argc, char **argv) {
  if (!parseOptions(argc, argv)) {
    int currentFile = optind;
    FILE *fp;
    while (currentFile < argc) {
      if (currentFile != argc) {
        fp = fopen(argv[currentFile], "r");
        if (fp == NULL) {
          fprintf(stderr, "%s: %s: No such file or directory", argv[0],
                  argv[currentFile]);
          break;
        }
      }
      printCattedFile(fp);
      fclose(fp);
      currentFile++;
    }
  }
}

void printCattedFile(FILE *fp) {
  int ch, emptyLine, line, prev;
  line = emptyLine = 0;
  for (prev = '\n'; (ch = getc(fp)) != EOF; prev = ch) {
    if (prev == '\n') {
      if (flagData.sflag) {
        if (ch == '\n') {
          if (emptyLine) continue;
          emptyLine = 1;
        } else
          emptyLine = 0;
      }
      if (flagData.nflag && (!flagData.bflag || ch != '\n')) {
        (void)fprintf(stdout, "%6d\t", ++line);
        if (ferror(stdout)) break;
      }
    }
    if (ch == '\n') {
      if (flagData.eflag && putchar('$') == EOF) break;
    } else if (ch == '\t') {
      if (flagData.tflag) {
        if (putchar('^') == EOF || putchar('I') == EOF) break;
        continue;
      }
    } else if (flagData.vflag) {
      if (!isAscii(ch) && !isprint(ch)) {
        if (putchar('M') == EOF || putchar('-') == EOF) break;
        ch = toAscii(ch);
      }
      if (iscntrl(ch)) {
        if (putchar('^') == EOF ||
            putchar(ch == '\177' ? '?' : ch | 0100) == EOF)
          break;
        continue;
      }
    }
    if (putchar(ch) == EOF) break;
  }
}

int parseOptions(int argc, char **argv) {
  int opt, errorFlag = 0;
  while ((opt = getopt_long(argc, argv, "benstvET?", long_options, NULL)) !=
         EOF) {
    switch (opt) {
      case 'b':
        flagData.nflag = 1;
        flagData.bflag = 1;
        break;
      case 'e':
        flagData.eflag = 1;
        flagData.vflag = 1;
        break;
      case 'n':
        flagData.nflag = 1;
        break;
      case 's':
        flagData.sflag = 1;
        break;
      case 't':
        flagData.tflag = 1;
        flagData.vflag = 1;
        break;
      case 'v':
        flagData.vflag = 1;
        break;
      case 'E':
        flagData.eflag = 1;
        break;
      case 'T':
        flagData.tflag = 1;
        break;
      case '?':
        printf("usage: cat [-benstET] [file ...]\n");
        errorFlag++;
    }
  }
  return errorFlag;
}

int isAscii(int c) { return ((c & ~0x7F) == 0); }

int toAscii(int c) { return (c & 0x7F); }