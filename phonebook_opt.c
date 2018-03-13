#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "phonebook_opt.h"

/* TODO: FILL YOUR OWN IMPLEMENTATION HERE! */
entry *new_node(char lastName[])
{
    entry *node = calloc(1, sizeof *node);
    strcpy(node->lastName, lastName);
    node->height = 1;
    node->pNext[0] = NULL;
    node->pNext[1] = NULL;
    return node;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void set_height(entry *n)
{
    int a, b;
    /*if ((a = 0) && n->pNext[0] != NULL) {
        a = n->pNext[0]->height;
    }
    if ((b = 0) && n->pNext[1] != NULL) {
        b = n->pNext[1]->height;
    }*/

    if (n->pNext[0] == NULL)
        a = 0;
    else
        a = n->pNext[0]->height;

    if (n->pNext[1] == NULL)
        b = 0;
    else
        b = n->pNext[1]->height;

    n->height = 1 + max(a, b);
}

int bal_factor(entry *n)
{
    if (n->pNext[0] == NULL)
        return -(n->pNext[1]->height);
    else if (n->pNext[1] == NULL)
        return n->pNext[0]->height;
    else
        return n->pNext[0]->height - n->pNext[1]->height;
}

entry *rotate(entry **rootp, int dir)
{
    entry *old_rt = *rootp, *new_rt = old_rt->pNext[dir];

    if ( (*rootp = new_rt) == NULL )
        free(old_rt);
    else {
        old_rt->pNext[dir] = new_rt->pNext[!dir];
        set_height(old_rt);
        new_rt->pNext[!dir] = old_rt;
    }
    return new_rt;
}

void adjust_balance(entry **rootp)
{
    entry *root = *rootp;
    int b = bal_factor(root)/2;

    if (b) {
        int dir = (1 - b)/2;
        if (bal_factor(root->pNext[dir]) == -b) {
            rotate(&root->pNext[dir], !dir);
        }
        root = rotate(rootp, dir);
    }
    if (root != NULL) set_height(root);
}

void insert(entry **rootp, char lastName[])
{

    entry *root = *rootp;

    if (root == NULL)
        *rootp = new_node(lastName);
    else {
        int sc = strcasecmp(lastName, root->lastName);
        if (sc > 0) {
            insert(&root->pNext[1], lastName);
            adjust_balance(rootp);
        } else if (sc < 0) {
            insert(&root->pNext[0], lastName);
            adjust_balance(rootp);
        }
    }
}


entry *findName(char lastName[], entry *pHead)
{
    entry *current = pHead;
    int cmpResult;

    while (current != NULL && (cmpResult = strcasecmp(lastName, current->lastName)) != 0) {
        if (cmpResult < 0)
            current = current->pNext[0];
        else
            current = current->pNext[1];
    }

    if (cmpResult == 0) {
        return current;
    } else
        return NULL;
}

entry *append(char lastName[], entry *e)
{
    insert(&e, lastName);

    return e;
}
