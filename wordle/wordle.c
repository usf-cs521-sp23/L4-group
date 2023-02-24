
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char* play = "y";
  while(strcmp(play, "y") == 0){
    FILE* fptr;
    fptr = fopen("wordleWords.txt", "r");
    int r = rand() % 26;
    char *target = (char*) malloc(5 * sizeof(char));
    while(fgets(target, 5, fptr) && r > 0){
      r--;
    }
    fclose(fptr);

    printf("Tell me your name so that I can laugh at you :)=: ");
    char* name = (char*) malloc(20 * sizeof(char));
    scanf("%s", name);

    int win = 0;

    for (int i = 0; i < 6; ++i) {
      char* guess = (char*) malloc(5 * sizeof(char));
      printf("Enter your guess: ");
      scanf("%s", guess);

      if (strlen(guess) != 5) {
        printf("That is not 5 characters %s. Please learn to play the game "
              "correctly.\n", name);
        continue;
      }

      for(int i = 0; i < 5; i++){
        if(target[i] < 'a' || target[i] > 'z'){
          printf("What are you trying to enter %s? Please at least give me a word, okay?", name);
        }
      }
      
      printf("                  ");
      for (int j = 0; j < 5; ++j) {
        if (target[j] == guess[j]) {
            printf("o");
        } else if (strchr(target, guess[j]) != NULL) {
            printf("a");
        } else {
            printf("x");
        }
      }
      puts("");

      if (strncmp(target, guess, 5) == 0) {
        printf("YOU WINNNNNNNNNNNNN!!!\n");
        win = 1;
        break;
      }
      printf("%d times left", 5 - i);
      free(guess);
    }
    if(win == 0){
      printf("You loser, %s.\n", name);
    }
    printf("Do you want to play again?\n");
    scanf("%s", play);
  }
  return 0;
}