#ifndef LZ78_H
#define LZ78_H

struct EntradaDiccionario {
    int indicePrefijo;
    char caracter;
};

struct ParSalida {
    int indice;
    char caracter;
    bool esUltimo;
};

int longitudFrase(EntradaDiccionario* diccionario, int indice);

bool coincideFrase(EntradaDiccionario* diccionario, int indice, const char* texto, int posicion, int longitud);

ParSalida* comprimirLZ78(const char* texto, int tamañoTexto, int& cantidadPares);

char* descomprimirLZ78(ParSalida* pares, int cantidadPares, int& tamañoSalida);

#endif