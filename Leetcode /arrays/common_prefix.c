#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest_common_prefix1(char **strs, size_t array_size);
int compare(const void *str1, const void *str2);
char *longest_common_prefix2(char **strs, size_t strs_size);

int main() 
{
    // strs is an array of pointers
    // strs: [ ptr to "flower", ptr to "flow", ptr to "flight" ]
    // strs[i] gives a pointer to i th string
    // strs[i][j] can be used to access the j th char in the i th string
    char *strs[] = {"flower", "flow", "flight", "flown"};
    int strsSize = sizeof(strs) / sizeof(strs[0]);
    // sort the strings alphabetically using quicksort
    qsort(strs, strsSize, sizeof(char *), compare);

    // print the string
    for(size_t i = 0; i < strsSize; i++)
    {
        printf("%s\n", strs[i]);
    }
    // strs decays to double pointer when passed to a function
    char *prefix1 = longest_common_prefix1(strs, strsSize);
    char *prefix2 = longest_common_prefix2(strs, strsSize);
    printf("Longest common prefix using iterating only is: %s\n", prefix1);
    printf("Longest common prefix using sorting then iterating is: %s\n", prefix2);
    return 0;
    }

// The function expects address of a pointer to the first string
// strs stores this address
char* longest_common_prefix1(char **strs, size_t array_size)
{
    if(array_size == 0)
    {
        return "";
    }
    char *initial_prefix = strs[0];
    size_t prefix_length = strlen(initial_prefix);
    int k;
    for(size_t i = 1; i < array_size; i++)
    {
        k = 0;
        while(k < prefix_length && initial_prefix[k] == strs[i][k])
        {
            k++;
        }
        prefix_length = k;
        if(prefix_length == 0)
        {
            return "";
        }
    }
    char *dest = malloc(prefix_length + 1);
    strncpy(dest, initial_prefix, prefix_length);
    dest[prefix_length] = '\0';
    return dest;
}

// time complexity is O(nlogn + L) due to sorting, L is the length of the shorter string
// space complexity is O(1) since we are not using any extra space
char *longest_common_prefix2(char **strs, size_t strs_size)
{
    if(strs_size == 0)
    {
        return "";
    }
    // get the first and the last string of the array
    char *first = strs[0];
    char *last = strs[strs_size - 1];

    int length_first = strlen(first);
    int length_last = strlen(last);

    // Find the minimum length using the ternary operator
    size_t min_len = (length_first < length_last) ? length_first : length_last;

    int i = 0;

    while(i <= min_len && first[i] == last[i])
    {
        i++;
    }
    if(i == 0)
    {
        return "";
    }
    char *dest = malloc(i + 1);
    strncpy(dest, first, i);
    dest[i] = '\0';
    return dest;
}



// remeber the arguments are pointers to char *
// hence they are char **
// qsort passes pointers to the elements of the array
// however, the elements of the arrays are char * in this case
int compare(const void *str1, const void *str2)
{

    // Type cast to const char * to treat them as strings
    const char *char_str1 = *(const char **)str1;
    const char *char_str2 = *(const char **)str2;

    if(strcmp(char_str1, char_str2) < 0)
    {
        return -1;
    }
    else if(strcmp(char_str1, char_str2) == 0)
    {
        return 0;
    }
    return 1;
}