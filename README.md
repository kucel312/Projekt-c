# Rejestr Bohaterów Gildii Poszukiwaczy Przygód

Program do zarządzania rejestrem bohaterów: dodawanie, edycja, usuwanie, wyszukiwanie, sortowanie oraz zapis/odczyt z pliku.

## Pliki
- main.c   – uruchamia program
- hero.h   – struktury danych + prototypy funkcji
- heroes.c – cała logika programu (menu, lista dynamiczna, pliki, wyszukiwanie, sortowanie)

---

## Uruchomienie
Program MUSI dostać nazwę pliku jako parametr.

1) Project → Set programs’ arguments…
2) W polu Program arguments: heroes.txt
3) OK i Uruchom

Przykład:
projekt.exe heroes.txt

---

## Format pliku danych (1 bohater = 1 linia)
name|race|class|level|reputation|status

Przykład:
Aragon|czlowiek|wojownik|5|80|1
Elira|elf|mag|3|90|2

---

## Status bohatera
1 – aktywny
2 – na misji
3 – ranny
4 – zaginiony
5 – zawieszony
