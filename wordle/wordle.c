#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./words/words.c"

int main(int argc, char *argv[]) {
  srand(time(NULL));
  char play[1] = "y";
  while(
    strcmp(play, "y") == 0){
  //   FILE* fptr;
  //   fptr = fopen("wordleWords.txt", "r");
  //   int r = rand() % 26;
  //   char target[5] = "email";
  //   if(fptr == NULL) {
  //     perror("Error opening file");
  //     return(-1);
  //  }
    // while(fgets(target, 5, fptr) != NULL && r > 0){
    //   r--;
    // }
    // fclose(fptr);
    printf("Tell me your name so that I can laugh at you :): ");
    char* name = (char*) malloc(20 * sizeof(char));
    scanf("%s", name);

    printf("Now choose the length of the word, you will take on!: ");
    int wordLength;
    scanf("%d", &wordLength);

    char target[wordLength];
    target[0] = 0;
    getWord(target, wordLength);

    printf("The target word: %s\n", target);

    int win = 0;

    for (int i = 0; i < 6; ++i) {
      char* guess = (char*) malloc(wordLength * sizeof(char));
      printf("Enter your guess: ");
      scanf("%s", guess);

      if (strlen(guess) != wordLength) {
        printf("That is not %d characters %s. Please learn to play the game "
              "correctly.\n", wordLength, name);
        continue;
      }

      for(int i = 0; i < wordLength; i++){
        if(guess[i] < 'a' || guess[i] > 'z'){
          printf("What are you trying to enter %s? Please at least give me a word, okay?", name);
          break;
        }
      }

      bool track[26];
      for(int i = 0; i < 26; i++){
        track[i] = true;
      }
      printf("                  ");
      for (int j = 0; j < wordLength; ++j) {
        if (target[j] == guess[j]) {
            printf("o");
        } else if (strchr(target, guess[j]) != NULL) {
            printf("a");
        } else {
            track[guess[j] - 'a'] = false;
            printf("x");
        }
      }
      puts("");

      if (strncmp(target, guess, wordLength) == 0) {
        printf("%s, YOU WINNNNNNNNNNNNN!!!\n", name);
        win = 1;
        break;
      }

      printf("The wrong letters: ");
      for(int i = 0; i < 26; i++){
        if(track[i] == false){
          printf("%c ", i + 'a');
        }
      }

      printf("\n%d times left\n", 5 - i);
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