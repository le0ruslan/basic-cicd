#include "s21_grep.h"

int main(int argc, char *argv[]) {
  int flagError = 0;
  char *patternE[argc];
  int tempCount = 0;
  Options options = grepReadFile(argc, argv, patternE, &tempCount, &flagError);
  if (!flagError) {
    flagError = grep(argc, argv, options, patternE, tempCount);
  }
  errorPrinting(&flagError);
  return 0;
}

Options grepReadFile(int argc, char *argv[], char **patternE, int *tempCount,
                     int *flagOpt) {
  Options options = {0};
  int currentOptions;
  static struct option longOptions[] = {{0, 0, 0, 0}};
  while ((currentOptions =
              getopt_long(argc, argv, "e:ivclnhso", longOptions, NULL)) != -1) {
    switch (currentOptions) {
      case 'e':
        options.patterns |= REG_EXTENDED;
        patternE[*tempCount] = optarg;
        *tempCount += 1;
        break;
      case 'i':
        options.regexFlag |= REG_ICASE;
        break;
      case 'v':
        options.invertMatch = 1;
        break;
      case 'c':
        options.stringCount = 1;
        break;
      case 'l':
        options.filesWithMatch = 1;
        break;
      case 'n':
        options.stringNumber = 1;
        break;
      case 'h':
        options.noNameFile = 1;
        break;
      case 's':
        options.noFile = 1;
        break;
      case 'o':
        options.optionO = 1;
        break;
      default:
        *flagOpt = 1;
    }
  }
  return options;
}

void grepNoNameFile(FILE *file, regex_t *preg) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  while (getline(&line, &length, file) > 0) {
    if (!regexec(preg, line, 1, &match, 0)) {
      printf("%s", line);
      if (line[strlen(line) - 1] != '\n') printf("\n");
    }
  }
  free(line);
}

void invertedMatch(FILE *file, char const *filename, regex_t *preg, int argc) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  while (getline(&line, &length, file) > 0) {
    if (regexec(preg, line, 1, &match, 0)) {
      if (argc - (optind + 1) > 1) {
        printf("%s:%s", filename, line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      } else {
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    }
  }
  free(line);
}

void grepCount(FILE *file, char const *filename, regex_t *preg, int argc,
               Options options) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  int count = 0;
  int count_cv = 0;
  while (getline(&line, &length, file) > 0) {
    if (!regexec(preg, line, 1, &match, 0)) {
      ++count;
    } else {
      count_cv++;
    }
  }
  if (options.stringCount && !options.invertMatch) {
    if (argc - (optind + 1) > 1)
      printf("%s:%d\n", filename, count);
    else
      printf("%d\n", count);
  } else {
    if (argc - (optind + 1) > 1)
      printf("%s:%d\n", filename, count_cv);
    else
      printf("%d\n", count_cv);
  }
  free(line);
}

void grepFileO(FILE *file, regex_t *preg) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match[1];
  while (getline(&line, &length, file) > 0) {
    while (regexec(preg, line, 1, match, 0) == 0) {
      for (int i = 0; i < match->rm_eo; i++) {
        if (i >= match->rm_so) {
          printf("%c", line[i]);
        }
        line[i] = 127;
      }
      printf("\n");
    }
  }
  free(line);
}

void grepFile(int argc, FILE *file, regex_t *preg, char const *filename) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  while (getline(&line, &length, file) > 0) {
    if (!regexec(preg, line, 1, &match, 0)) {
      if (argc - (optind + 1) > 1) {
        printf("%s:%s", filename, line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      } else {
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    }
  }
  free(line);
}

void grepFileE(int argc, FILE *file, regex_t *preg, char const *filename,
               int tempCount) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  while (getline(&line, &length, file) > 0) {
    if (!regexec(preg, line, 1, &match, 0)) {
      if ((argc - tempCount) > 3) {
        printf("%s:%s", filename, line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      } else {
        printf("%s", line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    }
  }

  free(line);
}

void grepFileWithMatch(FILE *file, char const *filename, regex_t *preg,
                       Options options) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  while (getline(&line, &length, file) > 0) {
    if (!regexec(preg, line, 1, &match, 0)) {
      printf("%s\n", filename);
      break;
    } else if (options.filesWithMatch && options.invertMatch) {
      printf("%s\n", filename);
      break;
    }
  }
  free(line);
}

void grepStringNumber(FILE *file, char const *filename, regex_t *preg,
                      int argc) {
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  int count = 0;
  while (getline(&line, &length, file) > 0) {
    if (!regexec(preg, line, 1, &match, 0)) {
      ++count;
      if (argc - (optind + 1) > 1) {
        printf("%s:%d:%s", filename, count, line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      } else {
        printf("%d:%s", count, line);
        if (line[strlen(line) - 1] != '\n') printf("\n");
      }
    } else {
      ++count;
    }
  }
  free(line);
}

int patternEComp(int argc, char *argv[], Options options, char **patternE,
                 int tempCount, regex_t *preg, char **pattern, char **end) {
  int flagNoFile = 0;
  for (int i = 0; i < tempCount; ++i) {
    regcomp(preg, patternE[i], options.patterns);
    for (char **filename = pattern; filename != end; ++filename) {
      FILE *file = fopen(*filename, "r");
      if (file) {
        if (errno) {
          fprintf(stderr, "%s", argv[0]);
          perror(*filename);
          continue;
        }
        grepFileE(argc, file, preg, *filename, tempCount);
        fclose(file);
      } else {
        flagNoFile = 2;
      }
    }
    regfree(preg);
  }
  return flagNoFile;
}

int grep(int argc, char *argv[], Options options, char **patternE,
         int tempCount) {
  int flagNoFileNoPattern = 0;
  char **pattern = &argv[optind];
  char **end = &argv[argc];
  regex_t pregStorage;
  regex_t *preg = &pregStorage;
  if (pattern == end) {
    flagNoFileNoPattern = 3;
  } else {
    if (options.patterns) {  // e
      flagNoFileNoPattern = patternEComp(argc, argv, options, patternE,
                                         tempCount, preg, pattern, end);
    } else {
      regcomp(preg, *pattern, options.regexFlag);
      for (char **filename = pattern + 1; filename != end; ++filename) {
        FILE *file = fopen(*filename, "r");
        if (file) {
          if (options.stringCount ||
              (options.stringCount && options.invertMatch)) {
            grepCount(file, *filename, preg, argc, options);
          } else if (options.filesWithMatch ||
                     (options.filesWithMatch && options.invertMatch)) {
            grepFileWithMatch(file, *filename, preg, options);
          } else if (options.stringNumber) {
            grepStringNumber(file, *filename, preg, argc);
          } else if (options.invertMatch) {
            invertedMatch(file, *filename, preg, argc);
          } else if (options.noNameFile) {
            grepNoNameFile(file, preg);
          } else if (options.optionO) {
            grepFileO(file, preg);
          } else {
            grepFile(argc, file, preg, *filename);
          }
          fclose(file);
        } else {
          if (options.noFile) {
            continue;
          } else {
            flagNoFileNoPattern = 2;
          }
        }
      }
      regfree(preg);
    }
  }
  return flagNoFileNoPattern;
}

void errorPrinting(int *flagError) {
  if (*flagError == 1) {
    fprintf(stderr, "illegal option, use  -e -i -v -c -l -n -h -s -o\n");
  } else if (*flagError == 2) {
    fprintf(stderr, "no such file or directory\n");
  } else if (*flagError == 3) {
    fprintf(stderr, "no pattern\n");
  }
}