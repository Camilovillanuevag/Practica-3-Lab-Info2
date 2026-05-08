#include "archivos.h"

#include <fstream>
#include <stdexcept>

using namespace std;

string leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw runtime_error("Error: No se pudo abrir el archivo '" + nombreArchivo + "'.");
    }

    string contenido = "";
    string linea;
    bool primeraLinea = true;

    while (getline(archivo, linea)) {
        if (!primeraLinea) {
            contenido += "\n";
        }
        contenido += linea;
        primeraLinea = false;
    }

    archivo.close();
    return contenido;
}

void escribirArchivo(const string& nombreArchivo, const string& contenido) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw runtime_error("Error: No se pudo crear el archivo '" + nombreArchivo + "'.");
    }

    archivo << contenido;
    archivo.close();
}