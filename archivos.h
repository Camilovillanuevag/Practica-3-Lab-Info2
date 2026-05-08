#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <string>

std::string leerArchivo(const std::string& nombreArchivo);
void escribirArchivo(const std::string& nombreArchivo, const std::string& contenido);

#endif