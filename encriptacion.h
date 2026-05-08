#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

#include <string>

std::string aBinario(unsigned char byte);

unsigned char rotarIzquierda(unsigned char byte, int n);
unsigned char rotarDerecha(unsigned char byte, int n);

unsigned char* encriptar(const unsigned char* datos, int tamaño, int n, unsigned char clave);
unsigned char* desencriptar(const unsigned char* datos, int tamaño, int n, unsigned char clave);

#endif