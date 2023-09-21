#include "bluetooth_funciones.h"

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void inicializarBT() {
  int valorRandom = obtenerValorNumerico("id");

  if (valorRandom == 0) {
    valorRandom = random(00000000,99999999);
    
    almacenarValorNumerico("id", valorRandom);
  }

  String nombre = "IntGreen" + String(valorRandom);
  
  SerialBT.begin(nombre);
}

int random(int min, int max)
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) );
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}