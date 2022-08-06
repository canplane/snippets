/* compressed trie (scanned from left to right)
 * 20200212
 * "ab", "abc"나 "abc", ""의 경우, "ab", ""는 next[26]으로 보내야 함. 인덱스 26 (blank)은 finish의 역할. 따라서 next[26]에 연결된 trie의 tag는 DATA여야 함
 * 26으로 갈 때는 idx를 -1로 두고 넘겨서 문자열이 끝났음을 표시한다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LETTERS (26 + 1)
#define MAX_CHAR 30

typedef enum {DATA, POINTER} NodeType;
typedef struct trie {
    NodeType tag;
    union {
        char key[MAX_CHAR];
        struct trie *next[MAX_LETTERS];
    } u;
} Trie;

static bool _insert(Trie **trie, char str[], int idx)
{
    Trie *node;
    if (!*trie) {
        *trie = malloc(sizeof(Trie)), memset(*trie, 0, sizeof(Trie));
        (*trie)->tag = DATA;
        strcpy((*trie)->u.key, str);
        return true;
    }
    else {
        if ((*trie)->tag == POINTER) {
            if (str[idx])
                return _insert(&(*trie)->u.next[str[idx] - 'a'], str, idx + 1);
            else
                return _insert(&(*trie)->u.next[26], str, -1);
        }
        else {
            if (idx == -1 || !strcmp(&str[idx], &(*trie)->u.key[idx]))
                return false;
            
            node = NULL;
            _insert(&node, (*trie)->u.key, 0);

            memset(*trie, 0, sizeof(Trie));
            (*trie)->tag = POINTER;
            (*trie)->u.next[node->u.key[idx] ? (node->u.key[idx] - 'a') : 26] = node;

            if (str[idx])
                _insert(&(*trie)->u.next[str[idx] - 'a'], str, idx + 1);
            else
                _insert(&(*trie)->u.next[26], str, -1);
            return true;
        }
    }
}
bool insert(Trie **trie, char str[])
{
    return _insert(trie, str, 0);
}

static bool _findPrefix(Trie *trie, char str[], int idx)
{
    char *p, *q;
    if (!trie)
        return false;
    else {
        if (trie->tag == POINTER) {
            if (str[idx])
                return _findPrefix(trie->u.next[str[idx] - 'a'], str, idx + 1);
            else
                return true;
        }
        else {
            p = &str[idx], q = &trie->u.key[idx];
            while (*p == *q && *p)
                p++, q++;
            return !*p;
        }
    }
}
bool findPrefix(Trie *trie, char str[])
{
    return _findPrefix(trie, str, 0);
}

static bool _findString(Trie *trie, char str[], int idx)
{
    if (!trie)
        return false;
    else {
        if (trie->tag == POINTER) {
            if (str[idx])
                return _findString(trie->u.next[str[idx] - 'a'], str, idx + 1);
            else
                return _findString(trie->u.next[26], str, -1);
        }
        else
            return idx == -1 || !strcmp(&trie->u.key[idx], &str[idx]);
    }
}
bool findString(Trie *trie, char str[])
{
    return _findString(trie, str, 0);
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
