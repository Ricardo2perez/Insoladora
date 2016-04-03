# Temporizador para Insoladora

   Firmware para que un **Arduino** se comporte como temporizador para una Insoladora de Circuitos Impresos.
Los componentes utilizados son:
	
- Arduino Mega (Puede usarse otro arduino).
- LCD KeyPad Shield.
- Módulo Relé Arduino.
- Zumbador.

# Composición del código

Se ha dividido el código en distintos ficheros:

* [Config.h] - Configuración de las patillas de entrada y salida además de los textos que apareceran en la pantalla *LCD*.
* [Buzzer.h] - Responsable de que suene una musiquilla al terminar la temporización, se ha sacado del proyecto  [Escornabot].
* [Iconos.h] - Están guardados los símbolos personalizados para mostrar en el *LCD*, como las flechas.
* [Keypad.h] - Se utiliza para leer el teclado que viene incorporado en la *Shield* de la pantalla *LCD*, convierte los valores leidos por la entrada analógica en numeros enteros.
* [TimerOne.h] - Librería que usamos para el temporizador.
* [Insoladora.ino] - Es el programa principal, está diseñado usando el concepto de estados y transiciones.

  



[Config.h]: <https://github.com/Ricardo2perez/Insoladora/blob/master/Config.h>
[Buzzer.h]: <https://github.com/Ricardo2perez/Insoladora/blob/master/Buzzer.h>
[Escornabot]: <http://escornabot.com/web/>
[Iconos.h]: <https://github.com/Ricardo2perez/Insoladora/blob/master/Iconos.h>
[Keypad.h]: <https://github.com/Ricardo2perez/Insoladora/blob/master/Keypad.h>
[TimerOne.h]: <https://github.com/Ricardo2perez/Insoladora/blob/master/TimerOne.h>
[Insoladora.ino]:<https://github.com/Ricardo2perez/Insoladora/blob/master/Insoladora.ino>
