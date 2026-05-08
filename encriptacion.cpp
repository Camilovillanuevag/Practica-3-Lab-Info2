#include "encriptacion.h"

#include <stdexcept>

using namespace std;

string aBinario(unsigned char byte) {
    string bits = "";
    for (int i = 7; i >= 0; i--) {
        bits += ((byte >> i) & 1) ? '1' : '0';
    }
    return bits;
}

unsigned char rotarIzquierda(unsigned char byte, int n) {
    n = n % 8;
    return (byte << n) | (byte >> (8 - n));
}

unsigned char rotarDerecha(unsigned char byte, int n) {
    n = n % 8;
    return (byte >> n) | (byte << (8 - n));
}

unsigned char* encriptar(const unsigned char* datos, int tamaño, int n, unsigned char clave) {
    if (tamaño <= 0) {
        throw invalid_argument("Error: No hay datos para encriptar.");
    }
    if (n <= 0 || n >= 8) {
        throw invalid_argument("Error: El valor de n debe estar entre 1 y 7.");
    }

    unsigned char* resultado = new unsigned char[tamaño];

    for (int i = 0; i < tamaño; i++) {
        unsigned char rotado = rotarIzquierda(datos[i], n);
        resultado[i] = rotado ^ clave;
    }

    return resultado;
}

unsigned char* desencriptar(const unsigned char* datos, int tamaño, int n, unsigned char clave) {
    if (tamaño <= 0) {
        throw invalid_argument("Error: No hay datos para desencriptar.");
    }
    if (n <= 0 || n >= 8) {
        throw invalid_argument("Error: El valor de n debe estar entre 1 y 7.");
    }

    unsigned char* resultado = new unsigned char[tamaño];

    for (int i = 0; i < tamaño; i++) {
        unsigned char sinXor = datos[i] ^ clave;
        resultado[i] = rotarDerecha(sinXor, n);
    }

    return resultado;
}