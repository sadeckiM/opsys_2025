Zadanie polega na zaimplementowaniu komunikacji między wyznaczającym zadanie (masterem), a wykonującym (slave). Komunikacja przebiega poprzez
kolejki komunikatów. Po wykonaniu zadania, slave odsyła wynik do mastera, gdzie ten wyświetla na stdout. Każde zadanie ma swoje pid, więc może istnieć
wielu zarządców i wykonujących.

Dane wejściowe:
Liczba zadań do wykonania.

Zbudowanie programu:
./build.sh

Uruchomienie programu:
cd build && ./producent n ; ./konsument

n - liczba zadań
