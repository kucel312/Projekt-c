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


void printHeader(void) {
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-10s | %-12s | %-5s | %-10s | %-12s |\n",
           "Imie", "Rasa", "Klasa", "Lvl", "Reputacja", "Status");
    printf("-------------------------------------------------------------------------------------------------\n");
}

void printHero(const Hero *h) {
    printf("| %-20s | %-10s | %-12s | %-5d | %-10d | %-12s |\n",
           h->name, h->race, h->className, h->level, h->reputation, statusToText(h->status));
}


Node* findByName(Node *head, const char *name) {
    Node *cur = head;
    while (cur != NULL) {
        if (strcmp(cur->data.name, name) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void appendNode(Node **head, Node *newNode) {
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *cur = *head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = newNode;
}

int countNodes(Node *head) {
    int count = 0;
    Node *cur = head;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}


void showMenu(void) {
    printf("\n=== Rejestr Bohaterow Gildii ===\n");
    printf("1. Dodaj bohatera\n");
    printf("2. Edytuj bohatera\n");
    printf("3. Usun bohatera\n");
    printf("4. Wyszukaj bohatera po imieniu\n");
    printf("5. Wyszukaj bohatera po poziomie\n");
    printf("6. Sortuj bohaterow po imieniu (pokaz kopie)\n");
    printf("7. Sortuj bohaterow po poziomie (pokaz kopie)\n");
    printf("8. Wyswietl wszystkich bohaterow\n");
    printf("0. Wyjscie\n");
}


void displayAll(Node *head) {
    if (head == NULL) {
        printf("(lista pusta)\n");
        return;
    }

    printHeader();
    Node *cur = head;
    while (cur != NULL) {
        printHero(&cur->data);
        cur = cur->next;
    }
    printf("-------------------------------------------------------------------------------------------------\n");
}

void addHero(Node **head) {
    Hero h;

    while (1) {
        readText("Imie (unikalne): ", h.name, sizeof(h.name));

        if (h.name[0] == '\0') {
            printf("Blad: imie nie moze byc puste.\n");
            continue;
        }

        if (findByName(*head, h.name) != NULL) {
            printf("Blad: bohater o takim imieniu juz istnieje.\n");
            continue;
        }

        break;
    }

    while (1) {
        readText("Rasa: ", h.race, sizeof(h.race));
        if (h.race[0] == '\0') {
            printf("Blad: rasa nie moze byc pusta.\n");
            continue;
        }
        break;
    }

    while (1) {
        readText("Klasa: ", h.className, sizeof(h.className));
        if (h.className[0] == '\0') {
            printf("Blad: klasa nie moze byc pusta.\n");
            continue;
        }
        break;
    }

    h.level = readIntInRange("Poziom (>=1): ", 1, 9999);
    h.reputation = readIntInRange("Reputacja (0-100): ", 0, 100);
    h.status = readStatus();

    Node *n = (Node*)malloc(sizeof(Node));
    if (n == NULL) {
        printf("Blad: brak pamieci.\n");
        return;
    }

    n->data = h;
    n->next = NULL;
    appendNode(head, n);

    printf("OK: dodano bohatera.\n");
}

void editHero(Node *head) {
    if (head == NULL) {
        printf("(lista pusta)\n");
        return;
    }

    char name[NAME_MAX_LEN + 1];
    readText("Podaj imie bohatera do edycji: ", name, sizeof(name));

    Node *node = findByName(head, name);
    if (node == NULL) {
        printf("Nie znaleziono bohatera.\n");
        return;
    }

    printf("Edycja: %s (imie nieedytowalne)\n", node->data.name);

    while (1) {
        readText("Nowa rasa: ", node->data.race, sizeof(node->data.race));
        if (node->data.race[0] == '\0') {
            printf("Blad: rasa nie moze byc pusta.\n");
            continue;
        }
        break;
    }

    while (1) {
        readText("Nowa klasa: ", node->data.className, sizeof(node->data.className));
        if (node->data.className[0] == '\0') {
            printf("Blad: klasa nie moze byc pusta.\n");
            continue;
        }
        break;
    }

    node->data.level = readIntInRange("Nowy poziom (>=1): ", 1, 9999);
    node->data.reputation = readIntInRange("Nowa reputacja (0-100): ", 0, 100);
    node->data.status = readStatus();

    printf("OK: zapisano zmiany.\n");
}

int removeByName(Node **head, const char *name) {
    Node *prev = NULL;
    Node *cur = *head;

    while (cur != NULL) {
        if (strcmp(cur->data.name, name) == 0) {
            if (cur->data.status == NA_MISJI) return -1;

            if (prev == NULL) *head = cur->next;
            else prev->next = cur->next;

            free(cur);
            return 1;
        }

        prev = cur;
        cur = cur->next;
    }

    return 0;
}

int removeManyByReputation(Node **head, int threshold, int *blockedCount) {
    Node *prev = NULL;
    Node *cur = *head;
    int removed = 0;

    if (blockedCount) *blockedCount = 0;

    while (cur != NULL) {
        if (cur->data.reputation < threshold) {
            if (cur->data.status == NA_MISJI) {
                if (blockedCount) (*blockedCount)++;
                prev = cur;
                cur = cur->next;
                continue;
            }

            if (prev == NULL) {
                *head = cur->next;
                free(cur);
                cur = *head;
            } else {
                prev->next = cur->next;
                free(cur);
                cur = prev->next;
            }

            removed++;
            continue;
        }

        prev = cur;
        cur = cur->next;
    }

    return removed;
}

void removeHero(Node **head) {
    if (*head == NULL) {
        printf("(lista pusta)\n");
        return;
    }

    printf("\nUsuwanie:\n");
    printf("1) Usun jednego (po imieniu)\n");
    printf("2) Usun wielu (reputacja < X)\n");

    int option = readIntInRange("Wybor: ", 1, 2);

    if (option == 1) {
        char name[NAME_MAX_LEN + 1];
        readText("Podaj imie do usuniecia: ", name, sizeof(name));

        int res = removeByName(head, name);
        if (res == 1) printf("OK: usunieto.\n");
        else if (res == 0) printf("Nie znaleziono.\n");
        else printf("Blokada: bohater jest 'na misji' - nie mozna usunac.\n");
    } else {
        int threshold = readIntInRange("Usun wszystkich z reputacja < (0-100): ", 0, 100);
        int blocked = 0;
        int removed = removeManyByReputation(head, threshold, &blocked);

        printf("Usunieto: %d\n", removed);
        if (blocked > 0) printf("Zablokowano (na misji): %d\n", blocked);
    }
}


