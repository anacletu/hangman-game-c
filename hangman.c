#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20

char ask_for_input(int guess_number);

int main(void)
{
    // defining variables
    char *words[MAX_WORDS];
    int word_count = 0;
    char guess;

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

    return 0;
}

char ask_for_input(int guess_number) // asking for user's input and validating it
{
    char input;
    do
    {
        printf("Insert your %d guess: ", guess_number);
        scanf(" %c", &input);
        input = toupper(input);
        if (input < 'A' || input > 'Z')
        {
            printf("Please, insert only characters from A to Z.\n");
        }
    } while (input < 'A' || input > 'Z');

    return input;
}