#include <iostream>
#include <string>

#include "rle.h"
#include "lz78.h"
#include "encriptacion.h"
#include "archivos.h"

using namespace std;

int main() {

    int opcion;
    cout << "Seleccione el modulo a probar:" << endl;
    cout << "1. RLE" << endl;
    cout << "2. LZ78" << endl;
    cout << "3. Encriptacion" << endl;
    cout << "4. Integracion" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cout << endl;

    if (opcion == 1) {
        cout << "=========================================" << endl;
        cout << "        MODULO RLE - PRACTICA 3          " << endl;
        cout << "=========================================" << endl;

        string cadenaOriginal;
        cout << "Ingrese una cadena de texto: ";
        cin.ignore();
        getline(cin, cadenaOriginal);

        try {
            string cadenaComprimida = comprimirRLE(cadenaOriginal);
            string cadenaDescomprimida = descomprimirRLE(cadenaComprimida);

            cout << "Cadena comprimida   : " << cadenaComprimida << endl;
            cout << "Cadena descomprimida: " << cadenaDescomprimida << endl;

            if (cadenaDescomprimida == cadenaOriginal) {
                cout << "Verificacion: OK - coincide con la original." << endl;
            } else {
                cout << "Verificacion: FAIL - NO coinciden las cadenas." << endl;
            }

        } catch (const invalid_argument& error) {
            cout << "Error de argumento: " << error.what() << endl;
        } catch (const runtime_error& error) {
            cout << "Error en ejecucion: " << error.what() << endl;
        }

    } else if (opcion == 2) {
        cout << "=========================================" << endl;
        cout << "       MODULO LZ78 - PRACTICA 3          " << endl;
        cout << "=========================================" << endl;

        string entrada;
        cout << "Ingrese una cadena de texto: ";
        cin.ignore();
        getline(cin, entrada);

        int tamañoTexto = (int)entrada.size();
        char* texto = new char[tamañoTexto];
        for (int i = 0; i < tamañoTexto; i++) {
            texto[i] = entrada[i];
        }

        try {
            int cantidadPares = 0;
            ParSalida* pares = comprimirLZ78(texto, tamañoTexto, cantidadPares);

            cout << "Pares generados (indice, caracter):" << endl;
            for (int i = 0; i < cantidadPares; i++) {
                if (pares[i].esUltimo) {
                    cout << "  (" << pares[i].indice << ", [fin])" << endl;
                } else {
                    cout << "  (" << pares[i].indice << ", " << pares[i].caracter << ")" << endl;
                }
            }

            int tamañoSalida = 0;
            char* textoRecuperado = descomprimirLZ78(pares, cantidadPares, tamañoSalida);

            cout << "Texto original    : ";
            for (int i = 0; i < tamañoTexto; i++) cout << texto[i];
            cout << endl;

            cout << "Texto recuperado  : ";
            for (int i = 0; i < tamañoSalida; i++) cout << textoRecuperado[i];
            cout << endl;

            bool coincide = (tamañoTexto == tamañoSalida);
            if (coincide) {
                for (int i = 0; i < tamañoTexto; i++) {
                    if (texto[i] != textoRecuperado[i]) {
                        coincide = false;
                        break;
                    }
                }
            }

            if (coincide) {
                cout << "Verificacion: OK - coincide con el original." << endl;
            } else {
                cout << "Verificacion: FAIL - NO coincide." << endl;
            }

            delete[] pares;
            delete[] textoRecuperado;

        } catch (const invalid_argument& error) {
            cout << "Error de argumento: " << error.what() << endl;
        } catch (const runtime_error& error) {
            cout << "Error en ejecucion: " << error.what() << endl;
        }

        delete[] texto;

    } else if (opcion == 3) {
        cout << "=========================================" << endl;
        cout << "    MODULO ENCRIPTACION - PRACTICA 3     " << endl;
        cout << "=========================================" << endl;

        string entrada;
        cout << "Ingrese una cadena de texto: ";
        cin.ignore();
        getline(cin, entrada);

        int n;
        cout << "Ingrese el valor de rotacion n (1-7): ";
        cin >> n;

        int valorClave;
        cout << "Ingrese la clave K (0-255): ";
        cin >> valorClave;
        unsigned char clave = (unsigned char)valorClave;

        int tamaño = (int)entrada.size();
        unsigned char* datos = new unsigned char[tamaño];
        for (int i = 0; i < tamaño; i++) {
            datos[i] = (unsigned char)entrada[i];
        }

        try {
            unsigned char* datosEncriptados = encriptar(datos, tamaño, n, clave);

            cout << "Texto original (bits): ";
            for (int i = 0; i < tamaño; i++) {
                cout << aBinario(datos[i]) << " ";
            }
            cout << endl;

            cout << "Texto encriptado (bits): ";
            for (int i = 0; i < tamaño; i++) {
                cout << aBinario(datosEncriptados[i]) << " ";
            }
            cout << endl;

            unsigned char* datosRecuperados = desencriptar(datosEncriptados, tamaño, n, clave);

            cout << "Texto recuperado  : ";
            for (int i = 0; i < tamaño; i++) {
                cout << (char)datosRecuperados[i];
            }
            cout << endl;

            bool coincide = true;
            for (int i = 0; i < tamaño; i++) {
                if (datos[i] != datosRecuperados[i]) {
                    coincide = false;
                    break;
                }
            }

            if (coincide) {
                cout << "Verificacion: OK - el texto recuperado coincide con el original." << endl;
            } else {
                cout << "Verificacion: FAIL - NO coincide." << endl;
            }

            delete[] datosEncriptados;
            delete[] datosRecuperados;

        } catch (const invalid_argument& error) {
            cout << "Error de argumento: " << error.what() << endl;
        }

        delete[] datos;

    } else if (opcion == 4) {
        cout << "=========================================" << endl;
        cout << "             INTEGRACION                 " << endl;
        cout << "=========================================" << endl;

        int metodo;
        cout << "Seleccione el metodo de compresion:" << endl;
        cout << "1. RLE" << endl;
        cout << "2. LZ78" << endl;
        cout << "Opcion: ";
        cin >> metodo;

        string nombreEntrada;
        cout << "Nombre del archivo de entrada: ";
        cin.ignore();
        getline(cin, nombreEntrada);

        int n;
        cout << "Ingrese el valor de rotacion n (1-7): ";
        cin >> n;

        int valorClave;
        cout << "Ingrese la clave K (0-255): ";
        cin >> valorClave;
        unsigned char clave = (unsigned char)valorClave;

        try {
            cout << "Intentando abrir: [" << nombreEntrada << "]" << endl;
            string textoOriginal = leerArchivo(nombreEntrada);
            cout << "\n[1] Texto leido (" << textoOriginal.size() << " caracteres)." << endl;

            int tamanoComprimido = 0;
            unsigned char* bytesComprimidos = nullptr;
            ParSalida* pares = nullptr;
            int cantidadPares = 0;
            char* textoLZ78 = nullptr;

            if (metodo == 1) {
                string comprimidoRLE = comprimirRLE(textoOriginal);
                tamanoComprimido = (int)comprimidoRLE.size();
                bytesComprimidos = new unsigned char[tamanoComprimido];

                for (int i = 0; i < tamanoComprimido; i++) {
                    bytesComprimidos[i] = (unsigned char)comprimidoRLE[i];
                }

                cout << "[2] Comprimido con RLE (" << tamanoComprimido << " caracteres)." << endl;

            } else if (metodo == 2) {
                int tamanoTexto = (int)textoOriginal.size();
                textoLZ78 = new char[tamanoTexto];

                for (int i = 0; i < tamanoTexto; i++) {
                    textoLZ78[i] = textoOriginal[i];
                }

                pares = comprimirLZ78(textoLZ78, tamanoTexto, cantidadPares);

                tamanoComprimido = cantidadPares * 6;
                bytesComprimidos = new unsigned char[tamanoComprimido];

                for (int i = 0; i < cantidadPares; i++) {
                    int base = i * 6;

                    bytesComprimidos[base]     = (unsigned char)((pares[i].indice >> 24) & 0xFF);
                    bytesComprimidos[base + 1] = (unsigned char)((pares[i].indice >> 16) & 0xFF);
                    bytesComprimidos[base + 2] = (unsigned char)((pares[i].indice >> 8) & 0xFF);
                    bytesComprimidos[base + 3] = (unsigned char)(pares[i].indice & 0xFF);
                    bytesComprimidos[base + 4] = (unsigned char)pares[i].caracter;
                    bytesComprimidos[base + 5] = (unsigned char)pares[i].esUltimo;
                }

                cout << "[2] Comprimido con LZ78 (" << cantidadPares << " pares)." << endl;

            } else {
                throw invalid_argument("Error: Metodo de compresion no valido.");
            }

            unsigned char* bytesEncriptados = encriptar(bytesComprimidos, tamanoComprimido, n, clave);
            cout << "[3] Datos encriptados." << endl;

            unsigned char* bytesDesencriptados = desencriptar(bytesEncriptados, tamanoComprimido, n, clave);
            cout << "[4] Datos desencriptados." << endl;

            string textoFinal;

            if (metodo == 1) {
                string comprimidoRLE = "";
                for (int i = 0; i < tamanoComprimido; i++) {
                    comprimidoRLE += (char)bytesDesencriptados[i];
                }
                textoFinal = descomprimirRLE(comprimidoRLE);

            } else if (metodo == 2) {
                ParSalida* paresRecuperados = new ParSalida[cantidadPares];

                for (int i = 0; i < cantidadPares; i++) {
                    int base = i * 6;

                    paresRecuperados[i].indice =
                        ((int)bytesDesencriptados[base] << 24) |
                        ((int)bytesDesencriptados[base + 1] << 16) |
                        ((int)bytesDesencriptados[base + 2] << 8) |
                        ((int)bytesDesencriptados[base + 3]);

                    paresRecuperados[i].caracter = (char)bytesDesencriptados[base + 4];
                    paresRecuperados[i].esUltimo = (bytesDesencriptados[base + 5] != 0);
                }

                int tamanoSalida = 0;
                char* textoRecuperado = descomprimirLZ78(paresRecuperados, cantidadPares, tamanoSalida);

                for (int i = 0; i < tamanoSalida; i++) {
                    textoFinal += textoRecuperado[i];
                }

                delete[] paresRecuperados;
                delete[] textoRecuperado;
            }

            cout << "[5] Texto descomprimido." << endl;

            escribirArchivo("salida.txt", textoFinal);
            cout << "[6] Resultado guardado en 'salida.txt'." << endl;

            if (textoFinal == textoOriginal) {
                cout << "\nVerificacion: OK [PASS] - el texto final coincide con el original." << endl;
            } else {
                cout << "\nVerificacion: [FAIL] - el texto final NO coincide." << endl;
            }

            delete[] bytesComprimidos;
            delete[] bytesEncriptados;
            delete[] bytesDesencriptados;
            if (pares) delete[] pares;
            if (textoLZ78) delete[] textoLZ78;

        } catch (const invalid_argument& error) {
            cout << "Error de argumento: " << error.what() << endl;
        } catch (const runtime_error& error) {
            cout << "Error en ejecucion: " << error.what() << endl;
        }

    } else {
        cout << "Opcion no valida." << endl;
    }

    return 0;
}