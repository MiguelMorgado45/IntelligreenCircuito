#include "preferencias.h";

Preferences prefs;

void inicializarPreferencias() {
  prefs.begin("intelligreen");
}

void almacenarValorNumerico(char* nombre, int valor) {
  prefs.putInt(nombre, valor);
}

int obtenerValorNumerico(char* nombre) {
  return prefs.getInt(nombre, 0);
}