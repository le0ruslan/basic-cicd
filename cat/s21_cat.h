#ifndef S21_CAT
#define S21_CAT

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool b;  //| 1 | -b (GNU: --number-nonblank) | нумерует только непустые строки
  bool e;  //| 2 | -e предполагает и -v (GNU only: -E то же самое, но без
           //применения -v) | также отображает символы конца строки как $  |
  bool n;  //| 3 | -n (GNU: --number) | нумерует все выходные строки |
  bool s;  //| 4 | -s (GNU: --squeeze-blank) | сжимает несколько смежных пустых
           //строк |
  bool t;  //| 5 | -t предполагает и -v (GNU: -T то же самое, но без применения
           //-v) | также отображает табы как  ^I |
  bool v;
} Options;

Options catReadOptions(int argc, char *argv[], int *flag);
void CatFile(FILE *file, Options options, const char *table[static 256]);
int Cat(int argc, char *argv[], Options options, const char *table[static 256]);
void CatSetTable(const char *table[static 256]);
void CatSetEndl(const char *table[static 256]);
void CatSetTab(const char *table[static 256]);
void CatSetNonPrintable(const char *table[static 256]);
void errorPrinting(int *flagError);

#endif