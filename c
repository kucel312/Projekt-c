#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef enum {
    AKTYWNY,
    NA_MISJI,
    RANNY,
    ZAGINIONY,
    ZAWIESZONY
} Status;

typedef struct {
    char name[100];
    char race[50];
    char className[50];
    int level;
    int reputation;
    Status status;
} Hero;

typedef struct Node {
    Hero data;
    struct Node *next;
} Node;




void showMenu(void) {
    printf("\n=== Rejestr Bohaterów Gildii ===\n");
    printf("1. Dodaj bohatera\n");
    printf("2. Edytuj bohatera\n");
    printf("3. Usun bohatera\n");
    printf("4. Wyszukaj bohatera po imieniu\n");
    printf("5. Wyszukaj bohatera po poziomie\n");
    printf("6. Sortuj bohaterow po imieniu\n");
    printf("7. Sortuj bohaterow po poziomie\n");
    printf("8. Wyswietl wszystkich bohaterow\n");
    printf("0. Wyjscie\n");
    printf("Wybor: ");
}

void handleMenu(Node **head) {
    int choice;

    do {
        showMenu();

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            printf("Bledny wybor\n");
            continue;
        }

        switch (choice) {
            case 1:
                addHero(head);
                break;
            case 2:
                editHero(*head);
                break;
            case 3:
                removeHero(head);
                break;
            case 4:
                searchByName(*head);
                break;
            case 5:
                searchByLevel(*head);
                break;
            case 6:
                sortByName(*head);
                break;
            case 7:
                sortByLevel(*head);
                break;
            case 8:
                displayAll(*head);
                break;
            case 0:
                printf("Koniec programu\n");
                break;
            default:
                printf("Nieprawidlowy wybor\n");
                break;
        }

    } while (choice != 0);
}



void addHero(Node **head);
void editHero(Node *head);
void removeHero(Node **head);


void searchByName(Node *head);
void searchByLevel(Node *head);


void sortByName(Node *head);
void sortByLevel(Node *head);


void displayAll(Node *head);


void saveToFile(Node *head, const char *filename);
void loadFromFile(Node **head, const char *filename);


void freeList(Node **head);



int main(int argc, char *argv[]) {
    Node *head = NULL;

    if (argc < 2) {
        printf("Użycie: %s <plik_danych>\n", argv[0]);
        return 1;
    }

    loadFromFile(&head, argv[1]);
    handleMenu(&head);
    saveToFile(head, argv[1]);
    freeList(&head);

    return 0;
}



void showMenu(void) {
}

void handleMenu(Node **head) {
}

void addHero(Node **head) {
}

void editHero(Node *head) {
}

void removeHero(Node **head) {
}

void searchByName(Node *head) {
}

void searchByLevel(Node *head) {
}

void sortByName(Node *head) {
}

void sortByLevel(Node *head) {
}

void displayAll(Node *head) {
}

void saveToFile(Node *head, const char *filename) {
}

void loadFromFile(Node **head, const char *filename) {
}

void freeList(Node **head) {
}
