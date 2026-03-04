#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 5000
#define LINE_NUMBER_WIDTH 6

void printUsage() {
  printf("usage: cat [-benstv] [file ...]\n");
  exit(1);
}

void processFile(FILE *fp, _Bool bflag, _Bool eflag, _Bool nflag, _Bool sflag,
                 _Bool tflag, _Bool vflag, _Bool Eflag, _Bool Tflag) {
  char buffer[BUFFER_SIZE];
  int lastLineBlank = 0;
  int lineNumber = 1;

  while (fgets(buffer, BUFFER_SIZE, (fp == NULL ? stdin : fp))) {
    int length = strlen(buffer);

    if (bflag && length > 1) {
      char *tmp = strdup(buffer);
      buffer[0] = '\0';
      sprintf(buffer, "%*d\t", LINE_NUMBER_WIDTH, lineNumber++);
      strcat(buffer, tmp);
      free(tmp);
    }

    if (eflag) {
      length = strlen(buffer);
      if (buffer[length - 1] == '\n') {
        buffer[length - 1] = '$';
        buffer[length] = '\n';
        buffer[++length] = '\0';
      }
    }

    else if (nflag) {
      char *tmp = strdup(buffer);
      buffer[0] = '\0';
      sprintf(buffer, "%*d\t", LINE_NUMBER_WIDTH, lineNumber++);
      strcat(buffer, tmp);
      free(tmp);
    }

    if (sflag) {
      _Bool currentLineBlank = (length <= 1) ? 1 : 0;
      if (lastLineBlank && currentLineBlank) {
        continue;
      }
      lastLineBlank = currentLineBlank;
    }

    if (tflag) {
      length = strlen(buffer);
      char new_buffer[length * 2 + 1];
      int j = 0;
      for (int i = 0; i < length; i++) {
        if (buffer[i] == '\t') {
          new_buffer[j++] = '^';
          new_buffer[j++] = 'I';
        } else {
          new_buffer[j++] = buffer[i];
        }
      }
      new_buffer[j] = '\0';
      memcpy(buffer, new_buffer, sizeof(new_buffer));
    }

    if (vflag) {
      for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\t') {
          putchar('\t');
        } else if ((buffer[i] >= 1 && buffer[i] <= 31 && buffer[i] != 10)) {
          printf("^%c", buffer[i] + 64);
        } else if (buffer[i] == 127) {
          printf("^?");
        } else {
          putchar(buffer[i]);
        }
      }
      // putchar('\n');
    } else {
      printf("%s", buffer);
    }

    if (Eflag) {
      length = strlen(buffer);
      buffer[length++] = '$';
      buffer[length] = '\0';
    }

    if (Tflag) {
      length = strlen(buffer);
      char new_buffer[length * 2 + 1];
      int j = 0;
      for (int i = 0; i < length; i++) {
        if (buffer[i] == '\t') {
          new_buffer[j++] = '^';
          new_buffer[j++] = 'I';
        } else {
          new_buffer[j++] = buffer[i];
        }
      }
      new_buffer[j] = '\0';
      memcpy(buffer, new_buffer, sizeof(new_buffer));
    }
  }
}

int main(int argc, char **argv) {
  _Bool bflag = 0, eflag = 0, nflag = 0, sflag = 0, tflag = 0, vflag = 0,
        Eflag = 0, Tflag = 0;
  int opt;

  static struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"NULL", no_argument, NULL, 'e'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {"NULL", no_argument, NULL, 't'},
      {"show-nonprinting", no_argument, NULL, 'v'},
      {"show-ends", no_argument, NULL, 'E'},
      {"show-tabs", no_argument, NULL, 'T'},
      {NULL, 0, NULL, 0}};

  while ((opt = getopt_long(argc, argv, "+benstvET", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        bflag = 1;
        break;
      case 'e':
        eflag = 1;
        vflag = 1;
        break;
      case 'n':
        nflag = 1;
        break;
      case 's':
        sflag = 1;
        break;
      case 't':
        vflag = 1;
        tflag = 1;
        break;
      case 'v':
        vflag = 1;
        break;
      case 'E':
        Eflag = 1;
        break;
      case 'T':
        Tflag = 1;
        break;
      default:
        printUsage();
        break;
    }
  }

  if (optind < argc) {
    FILE *fp;
    for (; optind < argc; optind++) {
      if ((fp = fopen(argv[optind], "r")) == NULL) {
        fprintf(stderr, "cat: %s: No such file or directory\n", argv[optind]);
        continue;
      }
      processFile(fp, bflag, eflag, nflag, sflag, tflag, vflag, Eflag, Tflag);
      fclose(fp);
    }
  }

  else {
    processFile(stdin, bflag, eflag, nflag, sflag, tflag, vflag, Eflag, Tflag);
  }

  return 0;
}
