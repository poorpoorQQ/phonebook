#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

/* TODO: After modifying the original version, uncomment the following * line to set OPT properly */
#define OPT 1

typedef struct __PHONE_BOOK_DATA {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} PhoneBookData;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    PhoneBookData *data;
    int height;
    struct __PHONE_BOOK_ENTRY *pNext[2];
} entry;

entry *new_node(char lastName[]);
int max(int a, int b);
void set_height(entry *n);
int bal_factor(entry *n);
entry *rotate(entry **rootp, int dir);
void adjust_balance(entry **rootp);
void insert(entry **rootp, char lastName[]);

entry *findName(char lastName[], entry *pHead);
entry *append(char lastName[], entry *e);

#endif
