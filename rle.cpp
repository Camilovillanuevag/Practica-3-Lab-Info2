#include "rle.h"

#include <stdexcept>
#include <cctype>

using namespace std;

string comprimirRLE(const string& cadena) {
    if (cadena.empty()) {
        throw invalid_argument("Error: La cadena de entrada esta vacia.");
    }

    string resultado = "";
    int tamano = (int)cadena.size();
    int indice = 0;

    while (indice < tamano) {
        char caracterActual = cadena[indice];
        int contador = 1;

        while (indice + contador < tamano && cadena[indice + contador] == caracterActual) {
            contador++;
        }

        if (contador > 1) {
            resultado += to_string(contador);
        }
        resultado += caracterActual;

        indice += contador;
    }

    return resultado;
}

string descomprimirRLE(const string& cadenaComprimida) {
    if (cadenaComprimida.empty()) {
        throw invalid_argument("Error: La cadena comprimida esta vacia.");
    }

    string resultado = "";
    int tamano = (int)cadenaComprimida.size();
    int indice = 0;

    while (indice < tamano) {
        string numeroTexto = "";

        while (indice < tamano && isdigit((unsigned char)cadenaComprimida[indice])) {
            numeroTexto += cadenaComprimida[indice];
            indice++;
        }

        if (indice >= tamano) {
            throw runtime_error("Error: Formato RLE invalido. Numero sin caracter al final.");
        }

        char caracterActual = cadenaComprimida[indice];
        indice++;

        int repeticiones;
        if (numeroTexto.empty()) {
            repeticiones = 1;
        } else {
            repeticiones = stoi(numeroTexto);
        }

        for (int j = 0; j < repeticiones; j++) {
            resultado += caracterActual;
        }
    }

    return resultado;
}