#include "lz78.h"

#include <stdexcept>

using namespace std;

int longitudFrase(EntradaDiccionario* diccionario, int indice) {
    int longitud = 0;
    int cursor = indice;

    while (cursor >= 0) {
        longitud++;
        int prefijo = diccionario[cursor].indicePrefijo;
        if (prefijo == 0) {
            cursor = -1;
        } else {
            cursor = prefijo - 1;
        }
    }

    return longitud;
}

bool coincideFrase(EntradaDiccionario* diccionario, int indice, const char* texto, int posicion, int longitud) {
    char* frase = new char[longitud];
    int cursor = indice;

    for (int i = longitud - 1; i >= 0; i--) {
        frase[i] = diccionario[cursor].caracter;
        int prefijo = diccionario[cursor].indicePrefijo;
        cursor = (prefijo == 0) ? -1 : prefijo - 1;
    }

    bool igual = true;
    for (int i = 0; i < longitud; i++) {
        if (frase[i] != texto[posicion + i]) {
            igual = false;
            break;
        }
    }

    delete[] frase;
    return igual;
}

ParSalida* comprimirLZ78(const char* texto, int tamañoTexto, int& cantidadPares) {
    if (tamañoTexto <= 0) {
        throw invalid_argument("Error: El texto de entrada esta vacio.");
    }

    int capacidadDiccionario = 10;
    int tamañoDiccionario = 0;
    EntradaDiccionario* diccionario = new EntradaDiccionario[capacidadDiccionario];

    int capacidadPares = 10;
    cantidadPares = 0;
    ParSalida* pares = new ParSalida[capacidadPares];

    int posicion = 0;

    while (posicion < tamañoTexto) {
        int mejorIndice = 0;
        int mejorLongitud = 0;

        for (int i = 0; i < tamañoDiccionario; i++) {
            int longitud = longitudFrase(diccionario, i);

            if (posicion + longitud <= tamañoTexto &&
                longitud > mejorLongitud &&
                coincideFrase(diccionario, i, texto, posicion, longitud)) {
                mejorIndice = i + 1;
                mejorLongitud = longitud;
            }
        }

        bool hayCaracterExtra = (posicion + mejorLongitud) < tamañoTexto;

        if (cantidadPares >= capacidadPares) {
            capacidadPares *= 2;
            ParSalida* paresNuevo = new ParSalida[capacidadPares];
            for (int i = 0; i < cantidadPares; i++) {
                paresNuevo[i] = pares[i];
            }
            delete[] pares;
            pares = paresNuevo;
        }

        if (hayCaracterExtra) {
            char caracterNuevo = texto[posicion + mejorLongitud];

            pares[cantidadPares].indice = mejorIndice;
            pares[cantidadPares].caracter = caracterNuevo;
            pares[cantidadPares].esUltimo = false;
            cantidadPares++;

            if (tamañoDiccionario >= capacidadDiccionario) {
                capacidadDiccionario *= 2;
                EntradaDiccionario* diccionarioNuevo = new EntradaDiccionario[capacidadDiccionario];
                for (int i = 0; i < tamañoDiccionario; i++) {
                    diccionarioNuevo[i] = diccionario[i];
                }
                delete[] diccionario;
                diccionario = diccionarioNuevo;
            }

            diccionario[tamañoDiccionario].indicePrefijo = mejorIndice;
            diccionario[tamañoDiccionario].caracter = caracterNuevo;
            tamañoDiccionario++;

            posicion += mejorLongitud + 1;
        } else {
            pares[cantidadPares].indice = mejorIndice;
            pares[cantidadPares].caracter = '\0';
            pares[cantidadPares].esUltimo = true;
            cantidadPares++;

            posicion += mejorLongitud;
        }
    }

    delete[] diccionario;
    return pares;
}

char* descomprimirLZ78(ParSalida* pares, int cantidadPares, int& tamañoSalida) {
    if (cantidadPares <= 0) {
        throw invalid_argument("Error: No hay pares para descomprimir.");
    }

    int capacidadDiccionario = 10;
    int tamañoDiccionario = 0;
    EntradaDiccionario* diccionario = new EntradaDiccionario[capacidadDiccionario];

    int capacidadSalida = 10;
    tamañoSalida = 0;
    char* salida = new char[capacidadSalida];

    for (int p = 0; p < cantidadPares; p++) {
        int indice = pares[p].indice;
        char caracter = pares[p].caracter;
        bool esUltimo = pares[p].esUltimo;

        int longitudPrefijo = 0;
        if (indice > 0) {
            longitudPrefijo = longitudFrase(diccionario, indice - 1);
        }

        int longitudTotal;
        if (esUltimo) {
            longitudTotal = longitudPrefijo;
        } else {
            longitudTotal = longitudPrefijo + 1;
        }

        char* fraseReconstruida = new char[longitudTotal];

        if (indice > 0) {
            int cursor = indice - 1;
            for (int i = longitudPrefijo - 1; i >= 0; i--) {
                fraseReconstruida[i] = diccionario[cursor].caracter;
                int prefijo = diccionario[cursor].indicePrefijo;
                if (prefijo == 0) {
                    cursor = -1;
                } else {
                    cursor = prefijo - 1;
                }
            }
        }

        if (!esUltimo) {
            fraseReconstruida[longitudTotal - 1] = caracter;
        }

        for (int i = 0; i < longitudTotal; i++) {
            if (tamañoSalida >= capacidadSalida) {
                capacidadSalida *= 2;
                char* salidaNueva = new char[capacidadSalida];
                for (int j = 0; j < tamañoSalida; j++) {
                    salidaNueva[j] = salida[j];
                }
                delete[] salida;
                salida = salidaNueva;
            }
            salida[tamañoSalida++] = fraseReconstruida[i];
        }

        if (!esUltimo) {
            if (tamañoDiccionario >= capacidadDiccionario) {
                capacidadDiccionario *= 2;
                EntradaDiccionario* diccionarioNuevo = new EntradaDiccionario[capacidadDiccionario];
                for (int i = 0; i < tamañoDiccionario; i++) {
                    diccionarioNuevo[i] = diccionario[i];
                }
                delete[] diccionario;
                diccionario = diccionarioNuevo;
            }

            diccionario[tamañoDiccionario].indicePrefijo = indice;
            diccionario[tamañoDiccionario].caracter = caracter;
            tamañoDiccionario++;
        }

        delete[] fraseReconstruida;
    }

    delete[] diccionario;
    return salida;
}