#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define WORDS_COUNT 20
#define MAX_WORD_LENGTH 20
#define LIVES 5
#define LEVELS 5

void display_word(char word[], int guessed[]) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (guessed[i])
            printf("%c ", word[i]);
        else
            printf("_ ");
    }
    printf("\n");
}

int is_word_guessed(int guessed[], int length) {
    for (int i = 0; i < length; i++)
        if (!guessed[i])
            return 0;
    return 1;
}

int main() {
    char words[WORDS_COUNT][MAX_WORD_LENGTH] = {
        "variable", "function", "loop", "array", "pointer",
        "string", "stack", "queue", "object", "class",
        "inheritance", "recursion", "algorithm", "compiler",
        "syntax", "debug", "operator", "library", "constant", "integer"
    };

    int used[WORDS_COUNT] = {0};
    srand(time(NULL));

    printf("=== Welcome to Hangman Game (Programming Edition) ===\n");

    for (int level = 1; level <= LEVELS; level++) {
        printf("\n--- Level %d ---\n", level);

        // Select a random unused word
        int index;
        do {
            index = rand() % WORDS_COUNT;
        } while (used[index]);
        used[index] = 1;

        char *word = words[index];
        int length = strlen(word);
        int guessed[length];
        for (int i = 0; i < length; i++) guessed[i] = 0;

        int lives = LIVES;
        char guess;
        printf("Guess the programming word!\n");

        while (lives > 0) {
            display_word(word, guessed);
            printf("Lives left: %d\n", lives);
            printf("Enter your guess: ");
            scanf(" %c", &guess);
            guess = tolower(guess);

            int correct = 0;
            for (int i = 0; i < length; i++) {
                if (word[i] == guess && !guessed[i]) {
                    guessed[i] = 1;
                    correct = 1;
                }
            }

            if (!correct) {
                printf("Wrong guess!\n");
                lives--;
            }

            if (is_word_guessed(guessed, length)) {
                printf("Congratulations! You guessed the word: %s\n", word);
                break;
            }
        }

        if (lives == 0) {
            printf("Out of lives! The word was: %s\n", word);
        }
    }

    printf("\n=== Game Over ===\n");
    return 0;
}