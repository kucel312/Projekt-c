#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hero.h"


void showMenu(void);

void addHero(Node **head);
void editHero(Node *head);
void removeHero(Node **head);

void searchByName(Node *head);
void searchByLevel(Node *head);

void sortByName(Node *head);
void sortByLevel(Node *head);

void displayAll(Node *head);

/* pomocnicze */
void removeNewline(char *text);
void readText(const char *prompt, char *buffer, int bufferSize);
int  readIntInRange(const char *prompt, int minValue, int maxValue);

const char* statusToText(Status s);
Status readStatus(void);

Node* findByName(Node *head, const char *name);
void  appendNode(Node **head, Node *newNode);
int   countNodes(Node *head);

int removeByName(Node **head, const char *name);
int removeManyByReputation(Node **head, int threshold, int *blockedCount);

void printHeader(void);
void printHero(const Hero *h);



void removeNewline(char *text) {
    text[strcspn(text, "\r\n")] = '\0';
}


void readText(const char *prompt, char *buffer, int bufferSize) {
    printf("%s", prompt);
    if (fgets(buffer, bufferSize, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    removeNewline(buffer);
}

int readIntInRange(const char *prompt, int minValue, int maxValue) {
    char line[128];
    int value;

    while (1) {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL) continue;

        if (sscanf(line, "%d", &value) != 1) {
            printf("Blad: wpisz liczbe.\n");
            continue;
        }

        if (value < minValue || value > maxValue) {
            printf("Blad: zakres [%d..%d].\n", minValue, maxValue);
            continue;
        }

        return value;
    }
}

const char* statusToText(Status s) {
    if (s == AKTYWNY) return "aktywny";
    if (s == NA_MISJI) return "na misji";
    if (s == RANNY) return "ranny";
    if (s == ZAGINIONY) return "zaginiony";
    if (s == ZAWIESZONY) return "zawieszony";
    return "nieznany";
}

Status readStatus(void) {
    int s;
    printf("Status:\n");
    printf("  1) aktywny\n");
    printf("  2) na misji\n");
    printf("  3) ranny\n");
    printf("  4) zaginiony\n");
    printf("  5) zawieszony\n");
    s = readIntInRange("Wybierz (1-5): ", 1, 5);
    return (Status)s;
}

