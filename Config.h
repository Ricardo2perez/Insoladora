//Config.h

// ensure this library description is only included once
#ifndef Config_h
#define Config_h

#define RELAY_PIN 22 //Patilla de salida para encender los tubos
#define LIGHT_PIN 24 //Patilla indicador luminoso de fin de contaje
#define BUZZER_PIN 26 // Patilla para conectar el avisador acústico
#define TIME_OUT 5  // Valor que se usa para el cambio de estado
#define ADDRESS 0  //Posicion de memoria desde la que empiezan a guardar datos
#define POS_MINEXP 0 // Posicion de memoria para guardar los minutos de exposicion
#define POS_SECONEXP 1 // Posicion de memoria para guardar los segundos de exposicion
#define POS_USABLE 2 // Posicion de memoria para verificar si los datos no estan corrompidos

// Textos que aparecen el la pantalla
#define TEXT_INICIO_1 "Temporizador"
#define TEXT_INICIO_2 "Insoladora"
#define TEXT_PRINCIPAL "Cambia "
#define TEXT_CONTAR "Contar"
#define TEXT_MINU "Minu: "
#define TEXT_SEG " Seg: "
#define TEXT_CAMBIO "Modificar "
#define TEXT_SET_MIN "Set Minutes: "
#define TEXT_SET_SEG "Set Seconds:  "
#define TEXT_GRABAR "Grabando"
#define TEXT_MIN "Minu: "
#define TEXT_SEG " Seg: "
#define TEXT_TERMINAR "Terminado"
#define TEXT_TEMPORIZANDO "Temporizando"


#endif  // Config_h

//EOF