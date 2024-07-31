/* 20200126 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false, true} bool;

#define NEXTSZ 26
typedef struct trie {
    bool finish;
    struct trie *next[NEXTSZ];
} Trie;

bool insert(Trie **trie, const char str[])
{
    int cur;
    if (!*trie) {
        *trie = malloc(sizeof(Trie));
        memset(*trie, 0, sizeof(Trie));
        if (*str) {
            cur = *str - 'a';
            return insert(&(*trie)->next[cur], ++str);
        }
        else
            return (*trie)->finish = true;
    }
    else {
        if (*str) {
            cur = *str - 'a';
            return insert(&(*trie)->next[cur], ++str);
        }
        else {
            if ((*trie)->finish)
                return false;
            else
                return (*trie)->finish = true; 
        }
    }
}

bool findPrefix(Trie *trie, const char str[])
{
    int cur;
    if (!trie)
        return false;
    else {
        if (*str) {
            cur = *str - 'a';
            return findPrefix(trie->next[cur], ++str);
        }
        else
            return true;
    }
}

bool findString(Trie *trie, const char str[])
{
    int cur;
    if (!trie)
        return false;
    else {
        if (*str) {
            cur = *str - 'a';
            return findString(trie->next[cur], ++str);
        }
        else
            return trie->finish;
    }
}

/* main */

#define WORDSSZ 7
const char *WORDS[WORDSSZ] = {"bee", "be", "can", "cat", "cd", "be", "b"};

int main()
{
    int i;
    Trie *root = NULL;

    printf("\033[1m[Insertion]\033[0m\n");
    for (i = 0; i < WORDSSZ - 1; i++)
        printf("%s : %s\n", insert(&root, WORDS[i]) ? "Inserted" : "\x1b[31mAlready Exists\x1b[0m", WORDS[i]);
    printf("\n");

    printf("\033[1m[Finding Prefix]\033[0m\n");
    for (i = 0; i < WORDSSZ; i++)
        printf("%s : %s\n", findPrefix(root, WORDS[i]) ? "Prefix Exists" : "\x1b[31mPrefix Not Exists\x1b[0m", WORDS[i]);
    printf("\n");

    printf("\033[1m[Finding String]\033[0m\n");
    for (i = 0; i < WORDSSZ; i++)
        printf("%s : %s\n", findString(root, WORDS[i]) ? "String Exists" : "\x1b[31mString Not Exists\x1b[0m", WORDS[i]);
    printf("\n");

    return 0;
}