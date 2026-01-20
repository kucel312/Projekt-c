#include <stdio.h>
#include "hero.h"

/*
  Uruchomienie:
  Program MUSI dostać nazwę pliku jako parametr:
  
  1. Projects → Set programs’ arguments…
  
  2. W polu Program arguments: heroes.txt
  
  3. OK i Uruchom.
  
  Przykład:
    projekt.exe heroes.txt
*/

int main(int argc, char *argv[]) {
    Node *head = NULL;

    if (argc < 2) {
        printf("Uzycie: %s <plik_danych>\n", argv[0]);
        printf("Przyklad: %s heroes.txt\n", argv[0]);
        return 1;
    }

    loadFromFile(&head, argv[1]);
    handleMenu(&head);
    saveToFile(head, argv[1]);
    freeList(&head);

    return 0;
}
