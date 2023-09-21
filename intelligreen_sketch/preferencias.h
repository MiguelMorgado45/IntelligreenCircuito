#ifndef PREFERENCIAS
#define PREFERENCIAS
#include <Arduino.h>
#include <Preferences.h>

void inicializarPreferencias();
void almacenarValorNumerico(char* nombre, int valor);
int obtenerValorNumerico(char* nombre);

#endif