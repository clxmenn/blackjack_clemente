#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

string palos[] = { "Corazones", "Diamantes", "Treboles", "Picas" };

string corazones[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
string diamantes[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
string treboles[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
string picas[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };

void Introduccion() {
    cout << "!Bienvenido al clásico juego de mesa BlackJack! Espero que tengas mucha suerte en esta partida,\n";
    cout << "y seas capaz de quedarte lo más cerca posible al número 21 con las cartas que el croupier te ofrece.";
    Sleep(2000);
}

string ObtenerPaloAleatorio() {
    int index = rand() % 4;
    return palos[index];
}

void ObtenerCartaAleatoria(string palo[], string& carta, int& valor) {
    int index = rand() % 13;

    // Si es un AS, permitir al croupier elegir automáticamente entre 1 y 11

    if (palo[index] == "A") {
        valor = 11; 

        // Verificar si 11 sobrepasaría 21
        if (valor + 10 > 21) {
            valor = 1;
            cout << "\nEl croupier elige 1 porque sumar 11 sobrepasaría 21.";
        }
        else {
            cout << "\nEl croupier elige 11 porque sumar 11 no sobrepasaría 21.";
        }
    }
    else if (palo[index] == "J" || palo[index] == "Q" || palo[index] == "K") {
        carta = palo[index];
        valor = 10;
    }
    else if (palo[index] == "10") {
        carta = palo[index];
        valor = 10;
    }
    else {
        valor = palo[index][0] - '0';
    }

    carta = palo[index];
}

void TurnoCroupier(string palo[], string& carta, int& valor, bool mostrar) {
    ObtenerCartaAleatoria(palo, carta, valor);

    if (mostrar) {
        cout << "\n\nCarta del croupier: " << carta << " de " << ObtenerPaloAleatorio();
    }
}

int main() {
    Introduccion();

    srand(static_cast<unsigned int>(time(0))); // no idea de lo que hace, sacado de internet 

    string carta1, carta2, cartaCroupier;
    int valorCarta1, valorCarta2, valorCroupier;
    int totalJugador = 0;
    int totalCroupier = 0;

    ObtenerCartaAleatoria(corazones, carta1, valorCarta1);
    ObtenerCartaAleatoria(corazones, carta2, valorCarta2);
    totalJugador = valorCarta1 + valorCarta2;

    cout << "\nCartas aleatorias: " << carta1 << " de " << ObtenerPaloAleatorio();
    cout << "\n                     " << carta2 << " de " << ObtenerPaloAleatorio();

    char opcion;
    while (totalJugador < 21) {
        TurnoCroupier(corazones, cartaCroupier, valorCroupier, true);
        totalCroupier += valorCroupier;

        cout << "\n¿Quieres tomar otra carta? (S/N): ";
        cin >> opcion;

        if (opcion == 'S' || opcion == 's') {
            string nuevaCarta;
            int nuevoValor;
            ObtenerCartaAleatoria(corazones, nuevaCarta, nuevoValor);
            totalJugador += nuevoValor;

            cout << "\nCarta obtenida: " << nuevaCarta << " de " << ObtenerPaloAleatorio();
        }
        else {
            TurnoCroupier(corazones, cartaCroupier, valorCroupier, false);
            totalCroupier += valorCroupier;
            cout << "\n\nCarta del croupier: " << cartaCroupier << " de " << ObtenerPaloAleatorio();
            break;
        }
    }

    cout << "\n\nPuntuación final del croupier: " << totalCroupier;
    cout << "\n\nPuntuación final del jugador: " << totalJugador;

    if (totalJugador > 21) {
        cout << "\n\n¡Te has pasado de 21! Pierdes la partida.";
    }
    else if (totalCroupier > 21 || totalJugador == 21 || (totalJugador < 21 && totalJugador > totalCroupier)) {
        cout << "\n\n¡Felicidades, ganaste la partida!";
    }
    else if (totalJugador == totalCroupier) {
        cout << "\n\n¡Es un empate!";
    }
    else {
        cout << "\n\nEl croupier gana la partida.";
    }

    return 0;
}