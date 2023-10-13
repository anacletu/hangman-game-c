#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20

int main(void)
{
    // defining variables
    char *words[MAX_WORDS];
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
        words[i] = (char *)malloc(MAX_WORD_LENGTH);
        if (words[i] == NULL)
        {
            printf("Memory allocation failed.\n");
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
    char selected_word[strlen(words[chosen_word_index]) + 1];
    strcpy(selected_word, words[chosen_word_index]);

    for (int i = 0; i < word_count; i++)
    {
        free(words[i]);
        words[i] = NULL;
    }

    printf("\n\n");
    printf("*********\n");
    printf(" HANGMAN\n");
    printf("*********\n");
    printf("\n\n");

    return 0;
}