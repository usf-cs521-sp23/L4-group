#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./words/words.c"

typedef struct {
    char name[20];
    int win;
} Player;

void savePlayers(Player players[], int numPlayers);

int main(int argc, char *argv[]) {
  srand(time(NULL));
  char play[1] = "y";
  FILE *results_file = fopen("results.txt", "a");
  //FILE *results_file = fopen("results.txt", "w");
  if (results_file == NULL) {
    perror("Error opening result file");
    return -1;
  }

  int winCounter = 0;
  int lossCounter = 0;

  Player players[100];
  int numPlayers = 0;

  while(
    strcmp(play, "y") == 0){
    printf("Tell me your name so that I can laugh at you :) : ");
    char* name = (char*) malloc(20 * sizeof(char));
    scanf("%s", name);
    fprintf(results_file, "Player Name: %s\n", name);    

    printf("Now choose the length of the word, you will take on!: ");
    int wordLength;
    scanf("%d", &wordLength);
    fprintf(results_file, "Word Length: %d\n", wordLength);

    char target[wordLength];
    target[0] = 0;
    getWord(target, wordLength);

    printf("The target word: %s\n", target);
    // fprintf(results_file, "Target word: %s", target);

    int win = 0;
    for (int i = 0; i < 6; ++i) {
      char* guess = (char*) malloc(wordLength * sizeof(char));
      printf("Enter your guess: ");
      scanf("%s", guess);
      fprintf(results_file, "Guesses made: %s\n", guess);

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
        winCounter++;

        bool found = false;
        for (int i = 0; i < numPlayers; i++) {
          if (strcmp(name, players[i].name) == 0) {
            players[i].win++;
            found = true;
            break;
          }
        }

        if (!found) {
          Player newPlayer;
          strcpy(newPlayer.name, name);
          newPlayer.win = 1;
          players[numPlayers] = newPlayer;
          numPlayers++;
        }

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
    fprintf(results_file, "Number of wins: %d\n", winCounter);
    if(win == 0){
      printf("You loser, %s.\n", name);
      lossCounter++;

    }
    fprintf(results_file, "Number of losses: %d\n", lossCounter);
    printf("Do you want to play again? (y/n) \n");
    fprintf(results_file, "\n");
    scanf("%s", play);
  }
  fprintf(results_file, "Winners:\n");
  fprintf(results_file, "\n");
  for (int i = 0; i < numPlayers; i++) {
    fprintf(results_file, "%s: %d wins\n", players[i].name, players[i].win);
  }

  savePlayers(players, numPlayers);

  fclose(results_file);
  return 0;
}

void savePlayers(Player players[], int numPlayers) {
  FILE *file = fopen("stats.txt", "a");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }
  fprintf(file, "Name\t Wins\n");
  for (int i = 0; i < numPlayers; i++) {
    fprintf(file, "%s\t %d\n", players[i].name, players[i].win);
  }
  fclose(file);
}