#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longest_common_prefix(char **strs, size_t array_size);

int main() 
{
    // strs is an array of pointers
    // strs: [ ptr to "flower", ptr to "flow", ptr to "flight" ]
    // strs[i] gives a pointer to i th string
    // strs[i][j] can be used to access the j th char in the i th string
    char *strs[] = {"abca", "aba", "aaab"};
    int strsSize = sizeof(strs) / sizeof(strs[0]);
    // strs decays to double pointer when passed to a function
    char *prefix = longestCommonPrefix(strs, strsSize);
    printf("Longest common prefix: %s\n", prefix);
    return 0;
    }

// The function expects address of a pointer to the first string
// strs stores this address
char* longest_common_prefix(char **strs, size_t array_size)
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
    strncp(dest, initial_prefix, prefix_length);
    dest[prefix_length] = '\0';
    return dest;
}
