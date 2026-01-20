#ifndef HERO_H
#define HERO_H

#include <stdio.h>

/* Maksymalne długości */
#define NAME_MAX_LEN  100
#define RACE_MAX_LEN   50
#define CLASS_MAX_LEN  50

typedef enum {
    AKTYWNY = 1,
    NA_MISJI = 2,
    RANNY = 3,
    ZAGINIONY = 4,
    ZAWIESZONY = 5
} Status;

typedef struct {
    char name[NAME_MAX_LEN + 1];      /* unikalne */
    char race[RACE_MAX_LEN + 1];
    char className[CLASS_MAX_LEN + 1];
    int level;                         /* >= 1 */
    int reputation;                    /* 0..100 */
    Status status;                     /* 1..5 */
} Hero;

typedef struct Node {
    Hero data;
    struct Node *next;
} Node;

/* Funkcje, z których korzysta main.c */
void loadFromFile(Node **head, const char *filename);
void saveToFile(Node *head, const char *filename);
void freeList(Node **head);
void handleMenu(Node **head);

#endif
