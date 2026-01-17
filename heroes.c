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
