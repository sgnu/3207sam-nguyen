#include "../headers/csapp.h"

char** dict[256000][MAXLINE];

int checkDict(const char* word);
int count = 0;

int main(void) {
  char buffer[MAXLINE];

  FILE * dictFile = fopen("/usr/share/dict/words", "r");
 
  while (fscanf(dictFile, "%s", buffer) > 0) {
    strcpy(dict[count], buffer);
    count++;
  }

  fclose(dictFile);

  while (1) {
    char input[MAXLINE];

    printf("Enter a  word: ");
    scanf("%s", input);

    printf("%s: %d\n", input, checkDict(input));
  }

  free(dict);
  return 0;
}

int checkDict(const char* word) {
  int i = 0;

  while (strcmp(word, dict[i]) > 0) {
    i++;
    if (strcmp(word, dict[i]) == 0) {
      return 1;
    }
  }

  return 0;
}
