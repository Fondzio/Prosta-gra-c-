#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>  // Biblioteka specyficzna dla Windows
using namespace std;
class Magazynek {
public:
    string typ_broni;
    string rodzaj_amunicji;
    int max_amo;
    int stan_ammo;

    // Konstruktor klasy Magazynek
    Magazynek(string typ_broni, string rodzaj_amunicji, int max_amo, int stan_ammo)
        : typ_broni(typ_broni), rodzaj_amunicji(rodzaj_amunicji), max_amo(max_amo), stan_ammo(stan_ammo) {}
};

class Bron {
public:
    float obrazenia;
    int amunicja;
    float szybkosc_br;
    Magazynek mag; // Typ z klasy Magazynek

    // Konstruktor klasy Bron
    Bron(Magazynek mag, float obrazenia, int amunicja, float szybkosc_br)
        : mag(mag), obrazenia(obrazenia), amunicja(amunicja), szybkosc_br(szybkosc_br) {}

};

class Postac {
public:

    float szybkosc;
    int zdrowie;
    Bron bron; // Typ z klasy Bron

    // Konstruktor klasy Postac
    Postac(Bron bron, float szybkosc, int zdrowie)
        : bron(bron), szybkosc(szybkosc), zdrowie(zdrowie) {}
};

void displayBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}
//strzał i zmieniająca zdrowie postaci
void strzel(Postac& b, Postac& p) {



    if (b.zdrowie > 0) {
        b.zdrowie -= p.bron.obrazenia;
        p.bron.amunicja = p.bron.amunicja - 1;
        cout << "Nowy stan amonicji: " << p.bron.amunicja << endl;
        cout << "Postac stracila " << p.bron.obrazenia << " zdrowia. Pozostale zdrowie: " << b.zdrowie << endl;
    }
}
void strzel2(Postac& b, Postac& p) {

    p.zdrowie = p.zdrowie - b.bron.obrazenia;
    b.bron.amunicja = b.bron.amunicja - 1;
    cout << "Postac stracila " << b.bron.obrazenia << " zdrowia. Pozostale zdrowie: " << p.zdrowie << endl;

}



int main() {
    int wybor;
    Magazynek mag("Pistolet", "9mm", 15, 15);

    // Tworzymy obiekt klasy Bron
    //rozrzut 0.5 w góre
    //szybkość 2.5 strzału na sekunde
    Bron bron(mag, 25, 15, 2.5);
    Bron bron2(mag, 20, 20, 0.5);

    // Tworzymy obiekt klasy Postac
    //predkosc 5 metrów na sekunde
    Postac p(bron, 5, 100);
    Postac b(bron, 5, 100);
    char ch;

    do {

        // Wyświetlenie menu

        cout << "\033[31mMenu wyboru:\033[0m\n" << endl;
        cout << "Wybierz klase snajpera:" << endl;
        cout << "1. Poradnik" << endl;
        cout << "2. Cel gry" << endl;
        cout << "3. Odpalenie gry\n";
        cout << "Wybierz opcje (1-3): ";
        cin >> wybor;
        // Obsługa wyboru za pomocą switch
        switch (wybor) {
        case 1: {
            cout << "Wybrałeś Poradnik: " << endl;
            cout << "Sterowanie: " << endl;
            cout << "Ruch (w/g/s/d/): W-postać idzie w góre,A-postać idzie w prawo,S-postać idzie w dół,D-postać idzie w prawo" << endl;
            cout << "strzelanie(Q): Q-postac oddaje strzał" << endl;
            cout << "przeładowanie broni(r): R-postac przeładowuje bron" << endl;
            cout << "k-zakończenie programu" << endl;
            break;
        }
        case 2:
            cout << "Wybrałeś cel gry" << endl;
            cout << "Celem gry jest pokonanie przeciwnika oznaczonego jako 'B', przedtym jak przeciwnik pokona użytkonika " << endl;
            break;
        case 3:
            cout << "Wybrales Opcje 3\n"; {
                const int rows = 10, cols = 10; // Rozmiar planszy
                vector<vector<char>> board(rows, vector<char>(cols, '.')); // Plansza wypełniona '.'
                int playerX = 5, playerY = 5; // Pozycja gracza (start w lewym górnym rogu)
                board[playerX][playerY] = '+'; // Umieszczenie gracza na planszy
                int enemyX = 7, enemyY = 9; // Pozycja gracza (start w lewym górnym rogu)
                board[enemyX][enemyY] = 'B'; // Umieszczenie gracza na planszy
                char move;
                while (true) {



                    //system("cls"); // Wyczyść ekran (Windows: zamień na system("cls"))
                    displayBoard(board); // Wyświetl plansze
                    cout << "Twoje aktualne zdrowie: " << p.zdrowie << endl;
                    cout << "Zdrowie przeciwnika: " << b.zdrowie << endl;
                    cout << "Amonicja w Magazynku: " << p.bron.amunicja << endl;
                    

                    //cin >> move;
                    move = _getch();

                    // Usuń gracza z obecnej pozycji
                    board[playerX][playerY] = '.';
                    if (b.zdrowie > 0) {

                        if (move == 'w' || move == 'a' || move == 's' || move == 'd' || move == 'q' && playerY != enemyY || move == 'q' && playerX != enemyX) {
                            // Usuń gracza z obecnej pozycji

                            board[enemyX][enemyY] = '.';

                            // Losowy kierunek: 0 - góra, 1 - dół, 2 - lewo, 3 - prawo
                            int direction = rand() % 4;
                            int losowy = rand() % 5;

                            // Zmień pozycję gracza w zależności od losowego kierunku
                            if (direction == 0 && enemyX > 0) { // Góra
                                enemyX--;
                                if (losowy == 1 && p.zdrowie > 0) {
                                    strzel2(b, p);
                                }
                            }
                            else if (direction == 1 && enemyX < rows - 1) { // Dół
                                enemyX++;
                                if (losowy == 1 && p.zdrowie > 0) {
                                    strzel2(b, p);
                                }
                            }
                            else if (direction == 2 && enemyY > 0) { // Lewo
                                enemyY--;
                                if (losowy == 1 && p.zdrowie > 0) {
                                    strzel2(b, p);
                                }
                            }
                            else if (direction == 3 && enemyY < cols - 1) { // Prawo
                                enemyY++;
                                if (losowy == 1 && p.zdrowie > 0) {
                                    strzel2(b, p);
                                }
                            }

                            // Umieść gracza na nowej pozycji
                            board[enemyX][enemyY] = 'B';


                        }
                    }
                    else if (b.zdrowie <= 0) {

                        board[enemyX][enemyY] = 'X';
                        cout << "Wygrałeś gre!!!" << endl;
                    }

                    // Zmień pozycję gracza w zależności od ruchu
                    if (p.zdrowie > 0) {
                        if (move == 'w' && playerX > 0) playerX--;
                        else if (move == 's' && playerX < rows - 1) playerX++;
                        else if (move == 'a' && playerY > 0) playerY--;
                        else if (move == 'd' && playerY < cols - 1) playerY++;

                    }
                    else if (p.zdrowie == 0) {
                        cout << "Przegrałeś!!!" << endl;
                        cout << "klinknij przycisk k, zeby zakończyć" << endl;
                        board[playerX][playerY] = 'X';


                    }
                    //Wyłączenie gry
                    if (move == 'k') {
                        exit(0);
                    }

                    // Wykonaj atak, gdy naciśniesz 'q'

                    if (move == 'q') {
                        int losowy2 = rand() % 5;

                        if (losowy2 >= 2 && enemyX == playerX && enemyY == playerY && p.zdrowie > 0 && p.bron.amunicja > 0) {
                            strzel(b, p); // Zadaj obrażenia postaci
                        }
                        //Unik postaci 
                        else if (losowy2 <= 1 && enemyX == playerX && enemyY == playerY && p.zdrowie > 0 && p.bron.amunicja > 0) {
                            cout << "przeciwnik zrobił unik" << endl;
                            if (move == 'w' || move == 'a' || move == 's' || move == 'd' || move == 'q') {
                                // Usuń gracza z obecnej pozycji

                                board[enemyX][enemyY] = '.';

                                // Losowy kierunek: 0 - góra, 1 - dół, 2 - lewo, 3 - prawo
                                int direction = rand() % 4;
                                int losowy = rand() % 5;

                                // Zmień pozycję gracza w zależności od losowego kierunku
                                if (direction == 0 && enemyX > 0) { // Góra
                                    enemyX--;
                                    if (losowy == 1 && p.zdrowie > 0) {
                                        strzel2(b, p);
                                    }
                                }
                                else if (direction == 1 && enemyX < rows - 1) { // Dół
                                    enemyX++;
                                    if (losowy == 1 && p.zdrowie > 0) {
                                        strzel2(b, p);
                                    }
                                }
                                else if (direction == 2 && enemyY > 0) { // Lewo
                                    enemyY--;
                                    if (losowy == 1 && p.zdrowie > 0) {
                                        strzel2(b, p);
                                    }
                                }
                                else if (direction == 3 && enemyY < cols - 1) { // Prawo
                                    enemyY++;
                                    if (losowy == 1 && p.zdrowie > 0) {
                                        strzel2(b, p);
                                    }
                                }

                                // Umieść gracza na nowej pozycji
                                board[enemyX][enemyY] = 'B';


                            }
                        }


                        else if (enemyX != playerX && p.bron.amunicja > 0 || enemyY != playerY && p.bron.amunicja > 0) {
                            p.bron.amunicja = p.bron.amunicja - 1;
                            cout << "nie trafiłeś" << endl;
                            cout << "Nowy stan amonicjii: " << p.bron.amunicja << endl;

                        }
                        else if (b.zdrowie == 0 && p.bron.amunicja > 0) {
                            p.bron.amunicja = p.bron.amunicja - 1;
                            cout << "Nowy stan amonicjii: " << p.bron.amunicja << endl;
                            cout << "Przeciwnik nie żyje: " << b.zdrowie << endl;
                        }
                        else if (p.bron.amunicja == 0) {
                            cout << "nie masz amonicjii, musisz przeładować!!!: " << p.bron.amunicja << endl;
                        }

                    }
                    //Przeładowanie broni
                    if (move == 'r') {
                        if (p.bron.amunicja < 15) {
                            for (int i = p.bron.amunicja; i <= 14; i++) {
                                p.bron.amunicja = p.bron.amunicja + 1;
                            }
                        }
                        else if (p.bron.amunicja >= 15) {
                            cout << "masz pełen magazynek" << p.bron.amunicja << endl;
                        }
                    }

                    // Umieść gracza na nowej pozycji
                    if (p.zdrowie > 0 && enemyY != playerY || p.zdrowie > 0 && enemyX != playerX) {
                        board[playerX][playerY] = '+';
                    }
                    //Ustawia celownik na O jezeli b ma te same współrzedne co +
                    else if (p.zdrowie > 0 && enemyY == playerY || p.zdrowie > 0 && enemyX == playerX) {
                        board[playerX][playerY] = 'O';
                    }
                }
            }

            break;
        default:
            cout << "Niepoprawny wybor. Sprobuj ponownie.\n";
        }
    } while (wybor != 3); // Pętla działa, dopóki użytkownik nie wybierze opcji 4

    return 0;
}