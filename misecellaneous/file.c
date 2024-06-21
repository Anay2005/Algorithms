#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// This is the limit of characters in a line
#define LIMIT 50

// this function would remove the sentence and everything after it
void clear_sentence(FILE *file, char sentence[])
{
    // move to the end of the file
    fseek(file, 0, SEEK_END);
  
    long file_size = ftell(file);
    // move the file pointer to the start of the file
    rewind(file);

    // allocate memory to read everything in the file, +1 for the null terminator
    char *buffer = malloc((file_size + 1) * sizeof(char));

    // Read the entire file into the buffer
    fread(buffer, sizeof(char), file_size, file);
    // remember fread doesn't add a null terminator
    buffer[file_size] = '\0';
    // strstr returns a pointer to the first occurrence of the sentence in the buffer
    char *start_of_sentence = strstr(buffer, sentence);
    if (start_of_sentence != NULL)
    {
        // calculate the elements between the start of the buffer and the start of the sentence
        // this is the content before the sentence which is to be deleted
        long elements_before_sentence = start_of_sentence - buffer;

        // Truncate the file to the new size, specifically used to change the file size on disk
        // ftruncate does not change the file pointer position
        // if the parameter is greater than the file size, the file is extended and the extended part is filled with null bytes
        ftruncate(fileno(file), elements_before_sentence);
        // move the file pointer to the end of file
        fseek(file, 0, SEEK_END);
    }
    // Clean up
    free(buffer);
}

void add_sentence_to_the_end(FILE *file, char sentence[], int limit)
{
    // move the file pointer to the end of the file, it is beyond the last character
    fseek(file, 0, SEEK_END);
    // returns the current position of the file pointer in bytes from the beginning of the file.
    // does not include the last character
    long file_size = ftell(file);

    // track the charcaters added to the line
    int characters_added_on_a_line = 0;

    // allocate enough memory to read everything in the file, +2 for the null terminator and newline_character/space
    char *buffer = malloc((file_size + strlen(sentence) + 50) * sizeof(char));
    // if malloc fails, it returns NULL
    if (buffer == NULL)
    {
        perror("Error allocating memory");
        return;
    }
    // move the file pointer to the start of the file
    rewind(file);
    // Read the entire pre existing content into the buffer
    fread(buffer, sizeof(char), file_size, file);

    // keep a track of index of newline
    int index_of_newline = -1;

    // We only care about the last line where we add the sentence and hence the last newline character.
    for (int i = 0; i < strlen(buffer); i++)
    {
        if (buffer[i] == '\n')
        {
            index_of_newline = i;
        }
    }

    // now point to the last line
    char *start_of_current_line = &buffer[index_of_newline + 1];
    int elements_in_current_line = strlen(start_of_current_line);
    printf("Elements in current line: %d\n", elements_in_current_line);

    // indicate the start of the sentence
    const char *start_of_sentence = &buffer[file_size];

    // add the sentence to the file
    for (int i = 0; i < strlen(sentence); i++)
    {
        if (elements_in_current_line >= limit)
        {
            // File_size can be treated as the index of the position where any character can be added
            buffer[file_size] = '\n';
            // move to the index in buffer where next character can be added
            file_size++;
            characters_added_on_a_line = 0;
            // update the start of last line
            start_of_current_line = &buffer[file_size];
            // update the elements in the current line
            elements_in_current_line = strlen(start_of_current_line);
            // don't add space on a newline
            if (sentence[i] == ' ')
            {
                continue;
            }
        }
        // This is to add space before adding the sentence on the same line
        if (characters_added_on_a_line == 0 && elements_in_current_line != 0)
        {

            // add a space character to the position of current_end_of_buffer
            buffer[file_size] = ' ';
            // Now the space character is the end of the buffer, the new position to insert is file_size_new + 1
            file_size++;
            // once a character is added, increment the characters_added_on_a_line
            characters_added_on_a_line++;
        }
        // add rest of the characters to the buffer
        buffer[file_size] = sentence[i];
        file_size++;
        characters_added_on_a_line++;
        elements_in_current_line++;
    }

    // move the file pointer to the end of the file
    fseek(file, 0, SEEK_END);
    // write the buffer to the file
    fwrite(start_of_sentence, sizeof(char), strlen(start_of_sentence), file);
    // null terminate the buffer(not needed, but good practice)
    buffer[file_size] = '\0';

    // clean up
    free(buffer);
}

int main(void)
{
    // open a file in read mode, file points(stores)
    // to the memory address of the file
    FILE *file = fopen("example.txt", "r+");

    // If file is not found or there is an error FILE returns NULL pointer
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    // fgetc returns an integer, value of character 'h' in ASCII is 72
    // hence for my file ch = 72 initially
    // after fgetc is called, file pointer automatically moves to the next character
    int ch = fgetc(file);
    // EOF has a value of -1, indicating end of the file
    while (ch != EOF)
    {
        // this is to print to the console
        putchar(ch);
        // Update the value from ASCII value of 'h' to ASCII value of 'e'
        ch = fgetc(file);
    }
    printf("\n\n");
    // store the read string here
    char buffer[50];
    // size is 50 bytes, 1 byte to store a char in c.
    int size = sizeof(buffer) / sizeof(buffer[0]);

    // move the file pointer to top
    rewind(file);
    // fgets only reads string only till newline character is reached or buffer limit is reached, whichever is first
    // Hence we need to put fgets in a loop.
    // using 'if fgets != NULL' condition would only execute the block once and hence read a single line only
    // buffer can store 49 chars including newline if present and fgets automatically adds a null terminator at the end
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        // read buffer till the null terminator
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            printf("%c", buffer[i]);
        }
    }
    printf("\n\n");

    char s1[] = "The topic sentence is the most important sentence in a paragraph. It is the main idea of the paragraph. It is usually the first sentence, but it can appear at any point in the paragraph. The topic sentence is usually a statement that is both general and specific. It helps the reader understand what the paragraph is about.";
    char s2[] = "Often, the body paragraph demonstrates and develops your topic sentence through an ordered, logical progression of ideas. There are a number of useful techniques for expanding on topic sentences and developing your ideas in a paragraph. Illustration in a paragraph supports a general statement by means of examples, details, or relevant quotations (with your comments).";
    // for(int i = 0; i<strlen(sentence); i++)
    // {
    //     fputc(sentence[i], file);
    // }

    // clear_sentence(file, sentence);

    add_sentence_to_the_end(file, s1, LIMIT);
    add_sentence_to_the_end(file, s2, LIMIT);

    // fclose returns 0, if file is closed
    // if there is an error ite returns EOF(-1)
    fclose(file);
    return 0;
}