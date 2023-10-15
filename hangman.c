#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20
#define MAX_ERRORS 6

char ask_for_input(int n);
int is_duplicate(char guess, char guesses[], int guess_counter);
void print_letters(char *secret_word, int word_length, char guess, char underscores[]);
void drawing(int mistakes);

int main(void)
{
    // defining variables
    char *words[MAX_WORDS]; // array of pointers that will later receive addresses via malloc
    int word_count = 0;

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
        words[i] = (char *)malloc(MAX_WORD_LENGTH); // dinamically allocating memory for each word
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

    // saving the selected word in a new array and freeing memory
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

    // setting the word spaces
    char word_on_screen[word_length];
    for (int i = 0; i < word_length; i++)
    {
        word_on_screen[i] = '_';
    }

    // variables for the game
    int game = 1;
    int wrong_guess = 0;
    int correct_guess = 0;
    int guess_counter = 0;
    char user_guesses[MAX_WORD_LENGTH];
    char guess;

    // loop until game is won or over
    while (game)
    {
        if (guess_counter == 0)
        {
            guess = ask_for_input(guess_counter);
            user_guesses[guess_counter] = guess;
            guess_counter++;
        }
        else
        {
            do
            {
                guess = ask_for_input(guess_counter);
            } while (is_duplicate(guess, user_guesses, guess_counter) == 1);

            user_guesses[guess_counter] = guess;
            guess_counter++;
        }

        // updating the word for the user
        print_letters(selected_word, word_length, guess, word_on_screen);

        // keeping track of correct and wrong guesses
        int mistake = 1;
        for (int i = 0; i < word_length; i++)
        {
            if (guess == selected_word[i])
            {
                correct_guess++;
                mistake = 0;
            }
        }
        if (mistake)
        {
            wrong_guess++;
        }

        // drawing the hangman
        drawing(wrong_guess);

        // handling win and game over
        if (wrong_guess == MAX_ERRORS)
        {
            printf("Game over! Better luck next time.\n");
            printf("The word was %s.\n\n", selected_word);
            game = 0;
        }
        if (correct_guess == word_length)
        {
            printf("You won!");
            game = 0;
        }
    }

    return 0;
}

char ask_for_input(int n) // asking for user's input and validating it
{
    char input;

    printf("Insert your guess %d: ", n + 1);
    scanf(" %c", &input);
    printf("\n");
    input = toupper(input);

    if (input < 'A' || input > 'Z')
    {
        printf("Please, insert only characters from A to Z.\n");
        input = ask_for_input(n);
    }

    return input;
}

int is_duplicate(char guess, char guesses[], int guess_counter)
{
    for (int i = 0; i < guess_counter; i++)
    {
        if (guess == guesses[i])
        {
            printf("You have already tried letter %c.\n\n", guess);
            return 1; // The guess is a duplicate
        }
    }
    return 0; // The guess is not a duplicate
}

void print_letters(char *secret_word, int word_length, char guess, char underscores[]) // drawing letters and spaces
{
    for (int i = 0; i < word_length; i++)
    {
        if (guess == secret_word[i])
        {
            underscores[i] = guess;
        }
        printf("%c ", underscores[i]);
    }
    printf("\n\n");
}

void drawing(int mistakes)
{
    // adapted to C language from the py souce in: https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c
    char *pics[] = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",

        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="};

    printf("%s\n\n", pics[mistakes]);
}
