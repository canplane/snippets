/* standard trie
 * 20200211
 * bool finish, Trie *next[MAX_LETTERS]
 * 루트 노드는 ""와 같음
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LETTERS 26

typedef struct trie {
    bool finish;
    struct trie *next[MAX_LETTERS];
} Trie;

bool insert(Trie **trie, char str[])
{
    if (!*trie)
        *trie = malloc(sizeof(Trie)), memset(*trie, 0, sizeof(Trie));
    if (!*str) {
        if ((*trie)->finish)
            return false;
        return (*trie)->finish = true;
    }
    else
        return insert(&(*trie)->next[*str - 'a'], str + 1);
}

bool findPrefix(Trie *trie, char str[])
{
    if (!trie)
        return false;
    if (!*str)
        return true;
    else
        return findPrefix(trie->next[*str - 'a'], str + 1);
}

bool findString(Trie *trie, char str[])
{
    if (!trie)
        return false;
    if (!*str)
        return trie->finish;
    else
        return findString(trie->next[*str - 'a'], str + 1);
}

/* main */

#define DATASZ 7
int main()
{
    int i;
    Trie *root = NULL;
    char *data[DATASZ] = {"bee", "be", "can", "cat", "cd", "be", "b"};

    // insertion
    for (i = 0; i < DATASZ - 1; i++)
        printf("%s : %s\n", insert(&root, data[i]) ? "inserted" : "\x1b[31malready exists\x1b[0m", data[i]);
    printf("\n");

    // finding prefix
    for (i = 0; i < DATASZ; i++)
        printf("%s : %s\n", findPrefix(root, data[i]) ? "prefix exists" : "\x1b[31mprefix not exists\x1b[0m", data[i]);
    printf("\n");

    // finding string
    for (i = 0; i < DATASZ; i++)
        printf("%s : %s\n", findString(root, data[i]) ? "string exists" : "\x1b[31mstring not exists\x1b[0m", data[i]);
    printf("\n");

    return 0;
}
