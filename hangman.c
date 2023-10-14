#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20
#define MAX_ATTEMPTS 7

char ask_for_input(int guess_number);
int print_letters(char *secret_word, char guess, int word_length, char printed[]);
int isDuplicate(char guess, char guesses[], int guess_counter);
void drawing(int word_length, int guess_counter, char *secret_word, char guesses[], int *game);

int main(void)
{
    // defining variables
    char *words[MAX_WORDS];
    int word_count = 0;
    char guess;
    char guesses[26];
    int guess_counter = 0;

    // opening the txt file with words to be ramdonly used in the game
    FILE *word_list = fopen("words.txt", "r");

    if (word_list == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // reading the file and storing the words in the array
    for (int i = 0; i < MAX_WORDS; i++)
    {
        words[i] = (char *)malloc(MAX_WORD_LENGTH);
        if (words[i] == NULL)
        {
            printf("Memory allocation failed for word %d.\n", i);
            exit(1);
        }

        if (fscanf(word_list, "%s", words[i]) != 1)
        {
            break;
        }
        word_count++;
    }
    fclose(word_list); // closing the .txt file

    // randomly selecting a word from the array
    srand(time(NULL)); // defining the seed for rand() based on EPOCH
    int chosen_word_index = rand() % word_count;

    // saving the word in a new array and freeing memory
    int word_length = strlen(words[chosen_word_index]);
    char selected_word[word_length + 1];
    strcpy(selected_word, words[chosen_word_index]);

    for (int i = 0; i < word_count; i++)
    {
        free(words[i]);
        words[i] = NULL;
    }

    // vitual presentation of the game
    printf("\n\n");
    printf("*********\n");
    printf(" HANGMAN\n");
    printf("*********\n");
    printf("\n\n");

    // loop until game is won or over
    int game = 0;

    // setting the word spaces
    char word_on_screen[word_length];
    for (int i = 0; i < word_length; i++)
    {
        word_on_screen[i] = '_';
    }

    while (!game)
    {
        guess = ask_for_input(guess_counter);

        // tracking guesses and validating duplicates
        if (guess_counter == 0 || !isDuplicate(guess, guesses, guess_counter))
        {
            guesses[guess_counter] = guess;
        }
        else
        {
            printf("You have already tried letter %c.\n", guess);
        }

        // updating the game
        game = print_letters(selected_word, guesses[guess_counter], word_length, word_on_screen);
        guess_counter++;

        drawing(word_length, guess_counter, selected_word, guesses, &game);
    }

    return 0;
}

char ask_for_input(int guess_number) // asking for user's input and validating it
{
    char input;
    do
    {
        printf("Insert your guess %d: ", guess_number + 1);
        scanf(" %c", &input);
        printf("\n");
        input = toupper(input);
        if (input < 'A' || input > 'Z')
        {
            printf("Please, insert only characters from A to Z.\n");
        }
    } while (input < 'A' || input > 'Z');

    return input;
}

int isDuplicate(char guess, char guesses[], int guess_counter)
{
    for (int i = 0; i < guess_counter; i++)
    {
        if (guess == guesses[i])
        {
            return 1; // The guess is a duplicate
        }
    }
    return 0; // The guess is not a duplicate
}

int print_letters(char *secret_word, char guess, int word_length, char printed[]) // drawing letters and spaces
{
    int word_guessed = 1; // Assume the word is guessed until an unguessed letter is found.

    for (int i = 0; i < word_length; i++)
    {
        if (guess == secret_word[i])
        {
            printed[i] = guess;
        }
        if (printed[i] == '_') // Unguessed letter found
        {
            word_guessed = 0;
        }
        printf("%c ", printed[i]);
    }

    printf("\n\n");

    if (word_guessed)
    {
        printf("Congratulations! You've guessed the word!\n");
    }

    printf("Secret Word: %s, Guess: %c, Word Guessed: %d\n\n", secret_word, guess, word_guessed);
    return (word_guessed);
}

void drawing(int word_length, int guess_counter, char *secret_word, char guesses[], int *game)
{
    int wrong_guess = 0; // Initialize it to 1 to account for the initial picture.

    for (int i = 0; i < guess_counter; i++)
    {
        int is_wrong = 1; // Initialize as wrong, and only set to 0 if guess is correct.
        for (int j = 0; j < word_length; j++)
        {
            if (secret_word[i] == guesses[j])
            {
                is_wrong = 0; // The guess is correct.
                break;
            }
        }
        if (is_wrong)
        {
            wrong_guess++;
        }
    }

    if (wrong_guess >= MAX_ATTEMPTS)
    {
        printf("Game over!\n");
        *game = 1;
    }

    char *pics[] = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n /|\\  |\n /     |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="};

    printf("%s\n", pics[wrong_guess]);
}
