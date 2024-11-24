#ifndef S21_GREP
#define S21_GREP

#include <errno.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int patterns;  //| 1 | -e | Шаблон |
  int regexFlag;  //| 2 | -i | Игнорирует различия регистра.  |
  int invertMatch;  //| 3 | -v | Инвертирует смысл поиска соответствий. |
  int stringCount;  //| 4 | -c | Выводит только количество совпадающих строк. |
  int filesWithMatch;  //| 5 | -l | Выводит только совпадающие файлы.  |
  int stringNumber;  //| 6 | -n | Предваряет каждую строку вывода номером строки
                     //из файла ввода. |
  int noNameFile;  //| 7 | -h | Выводит совпадающие строки, не предваряя их
                   //именами файлов. |
  int noFile;  //| 8 | -s | Подавляет сообщения об ошибках о несуществующих или
               //нечитаемых файлах. |
  int optionO;  //| 10 | -o | Печатает только совпадающие (непустые) части
                //совпавшей строки. |
} Options;

Options grepReadFile(int argc, char *argv[], char **patternE, int *tempCount,
                     int *flagOpt);
void grepCount(FILE *file, char const *filename, regex_t *preg, int argc,
               Options options);
void grepFile(int argc, FILE *file, regex_t *preg, char const *filename);
void grepFileWithMatch(FILE *file, char const *filename, regex_t *preg,
                       Options options);
void grepStringNumber(FILE *file, char const *filename, regex_t *preg,
                      int argc);
int grep(int argc, char *argv[], Options options, char **patternE,
         int tempCount);
void grepNoNameFile(FILE *file, regex_t *preg);
void grepFileE(int argc, FILE *file, regex_t *preg, char const *filename,
               int tempCount);
void grepFileO(FILE *file, regex_t *preg);
int patternEComp(int argc, char *argv[], Options options, char **pattern_e,
                 int tempCount, regex_t *preg, char **pattern, char **end);
void errorPrinting(int *flagError);

#endif