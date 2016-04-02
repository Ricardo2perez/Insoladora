

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include "TimerOne.h"
#include "Config.h"
#include "Buzzer.h" 
#include "Keypad.h"
#include "Iconos.h"

enum states
{
	PRINCIPAL, 
	TIEMPO,
	SET_MIN,
	SET_SEC,
	GRABAR,
	CONTAR,
	FIN_CONTAR
};

// Estructura para guardar los datos de los tiempos
struct DATOS{
   uint8_t   minuteExp;
   uint8_t   seconExp;
   boolean   usable;
};
 
union MEMORIA{
   DATOS dato;
   byte  b[sizeof(DATOS)];
}
miMemoria;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //configura las patillas para el LCD
Keypad key;

Buzzer zumbador(BUZZER_PIN);

states state; //hold the current state of the system

uint8_t timeMinute = 0, timeSeconds = 0;
unsigned long timeRef;
uint8_t expMinutes, expSeconds;
int8_t button;
uint8_t tmpMinutes, tmpSeconds;
volatile unsigned long blinkCount = 0;
int totalSeconds;

// Inicializacion de valores

void initValues(){
      expMinutes = miMemoria.dato.minuteExp ;
      expSeconds = miMemoria.dato.seconExp;
      
}


void setup(){
  //Creamos los iconos para mostrar en la pantalla
  lcd.begin(16,2);
  lcd.createChar(1, newChar3);  
  lcd.createChar(3, newChar11);
  lcd.createChar(9, newChar9);
  lcd.createChar(10,newChar10);
  
	pinMode(RELAY_PIN, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);
	   // Se recuperan los datos de la memoria EEPROM:
   for( int i=0 ; i<sizeof(DATOS) ; i++  )
      miMemoria.b[i] = EEPROM.read( ADDRESS+i );

      // Se comprueba que se hayan podido leer los datos (que no se haya leido basura)
   // No es la forma mas elegante de hacerlo pero funciona:
	if( miMemoria.dato.usable == true )
   {
     initValues();
   }
   // Si nunca se habian usado se inicializan todos los datos:
   else
   {
      miMemoria.dato.minuteExp  = 3;
      miMemoria.dato.seconExp = 10;
      miMemoria.dato.usable = true;

      // Se guardan los datos en la memoria EEPROM:
      for( int i=0 ; i<sizeof(DATOS) ; i++  )
      EEPROM.write( ADDRESS+i , miMemoria.b[i] );
      initValues();
   }


	

	state = PRINCIPAL;
}

void loop()
{

	timeRef = millis();
	switch (state)
	{
		case PRINCIPAL:
			showPrincipal();
			break;
		case TIEMPO:
			showTiempo();
			break;
		case SET_MIN:
			setMinute();
			break;
		case SET_SEC:
			setSecond();
			break;
		case GRABAR:
			setGrabar();
			break;
		case CONTAR:
			setContar();
			break;
		case FIN_CONTAR:	
			setFinContar();
			break;

	}
 // Comprobamos si hay teclas pulsadas o si se produce un timeOut
	while ( (unsigned long)(millis()- timeRef)< 970)
	{
		if ( (button = key.button()) != KEYPAD_NONE)
		{
			while ( key.button() != KEYPAD_NONE);
			transition(button);
			break;
		}
	}

}


void transition(uint8_t trigger)
{
	switch (state)
	{
		case PRINCIPAL:
			if ( trigger == KEYPAD_DOWN ) state = CONTAR; 
            else if ( trigger == KEYPAD_SELECT ) state = TIEMPO;
            else if ( trigger == TIME_OUT) state = TIEMPO;

		break;
		case TIEMPO:
			if ( trigger == KEYPAD_SELECT ) state = CONTAR;
			else if ( trigger == KEYPAD_RIGHT ) state = SET_MIN;
			//else if ( trigger == TIME_OUT ) state = PRINCIPAL;


		break;
		case SET_MIN:
			if ( trigger == KEYPAD_RIGHT ) state = SET_SEC;
			else if ( trigger == TIME_OUT ) state = TIEMPO;

		break;
		case SET_SEC:
			if ( trigger == KEYPAD_RIGHT ) state = GRABAR;
			else if ( trigger == TIME_OUT ) state = TIEMPO;

		break;
		case GRABAR:
			if ( trigger == KEYPAD_RIGHT ) state = TIEMPO;
			else if ( trigger == TIME_OUT ) state = TIEMPO;

		break;
		case CONTAR:
			if ( trigger == KEYPAD_SELECT ) state = FIN_CONTAR;
			else if ( trigger == KEYPAD_RIGHT ) state = FIN_CONTAR;
      else if ( trigger == TIME_OUT ) state = FIN_CONTAR;

		break;
		case FIN_CONTAR:
			if ( trigger == KEYPAD_SELECT ) state = TIEMPO;
      else if (trigger == TIME_OUT ) state = TIEMPO;
			
		break;
	}
}

void showPrincipal(){
	timeRef=millis();
  lcd.clear();
	lcd.print(TEXT_INICIO_1);
	lcd.setCursor(0,1);
	lcd.print(TEXT_INICIO_2);
  //byte letra[8] = { B01110, B11011, B10001, B10001, B10001, B10001, B10001, B11111 };
 
	digitalWrite(BUZZER_PIN,LOW);
   while ( (unsigned long)(millis() - timeRef) < 1970 )
    {
       
           
         
            
        

    }
    transition(TIME_OUT);
}

void showTiempo(){

  digitalWrite(BUZZER_PIN,LOW);
	lcd.clear();   
  lcd.write(1);
	lcd.print(TEXT_PRINCIPAL);
  lcd.write(3);
  lcd.print(TEXT_CONTAR);  

	lcd.setCursor(0,1);
	lcd.print(TEXT_MINU);

  if (expMinutes < 10) lcd.print(" ");
  lcd.print(String(expMinutes));
  lcd.print(TEXT_SEG);
  if (expSeconds <10) lcd.print(" ");
  lcd.print(String(expSeconds));
}

void setMinute(){

	unsigned long timeRef;
    boolean timeOut = true;    
    lcd.clear();
    lcd.print(TEXT_CAMBIO);
    lcd.write(9);    
    lcd.write(10);
        
    lcd.setCursor(0,1);
    lcd.print(TEXT_SET_MIN); 
    
    tmpMinutes = expMinutes;
    if ( tmpMinutes < 10 ) lcd.print(" ");
    lcd.print(String(tmpMinutes));

    timeRef = millis();    
    while ( (unsigned long)(millis() - timeRef) < 5000 )
    {
        uint8_t button = key.button();

        if ( button == KEYPAD_UP )
        {
            tmpMinutes = tmpMinutes < 59 ? tmpMinutes + 1 : tmpMinutes;
            lcd.setCursor(13,1);
            if ( tmpMinutes < 10 ) lcd.print(" ");
            lcd.print(tmpMinutes);
            timeRef = millis();
        }
        else if ( button == KEYPAD_DOWN )
        {
            tmpMinutes = tmpMinutes > 0 ? tmpMinutes - 1 : tmpMinutes;
            lcd.setCursor(13,1);
            if ( tmpMinutes < 10 ) lcd.print(" ");
            lcd.print(tmpMinutes);
            timeRef = millis();
        }
        else if ( button == KEYPAD_RIGHT )
        {
            while ( key.button() != KEYPAD_NONE ) ;
            timeOut = false;
            break;
        }
        delay(150);
    }

    if ( !timeOut ) transition(KEYPAD_RIGHT);
    else transition(TIME_OUT);
}

void setSecond(){
	unsigned long timeRef;
    boolean timeOut = true;
    
    lcd.clear();
    lcd.print(TEXT_CAMBIO);
    lcd.write(9);
    lcd.write(10);

    tmpSeconds = expSeconds;
    timeRef = millis();
    lcd.setCursor(0,1);
    lcd.print(TEXT_SET_SEG);
    if (tmpSeconds < 10) lcd.print(" ");
    lcd.print(String(tmpSeconds));
    
    while ( (unsigned long)(millis() - timeRef) < 5000 )
    {
        uint8_t button = key.button();

        if ( button == KEYPAD_UP )
        {
            tmpSeconds = tmpSeconds < 59 ? tmpSeconds + 1 : tmpSeconds;
           
            lcd.setCursor(14,1);
            if ( tmpSeconds < 10 ) lcd.print(" ");
            lcd.print(tmpSeconds);
            timeRef = millis();
        }
        else if ( button == KEYPAD_DOWN )
        {
            tmpSeconds = tmpSeconds > 0 ? tmpSeconds - 1 : tmpSeconds;
            lcd.setCursor(14,1);
            if ( tmpSeconds < 10 ) lcd.print(" ");
            lcd.print(tmpSeconds);
            timeRef = millis();
        }
        else if ( button == KEYPAD_RIGHT )
        {
            while ( key.button() != KEYPAD_NONE ) ;
            timeOut = false;
            break;
        }
        delay(150);
    }

    if ( !timeOut )
    {
      expMinutes = tmpMinutes;
      expSeconds = tmpSeconds;
      transition(KEYPAD_RIGHT);
      } 
    else transition(TIME_OUT);
}

void setGrabar(){
    timeRef = millis();
   EEPROM.write(ADDRESS+POS_MINEXP, expMinutes);
   EEPROM.write(ADDRESS+POS_SECONEXP, expSeconds);
   lcd.clear();
   lcd.print(TEXT_GRABAR);
   lcd.setCursor(0,1);
   lcd.print(TEXT_MIN);
   if (expMinutes<10) lcd.print(" ");
   lcd.print(String(expMinutes));
   lcd.print(TEXT_SEG);
   if (expSeconds < 10) lcd.print(" ");
   lcd.print(String(expSeconds));   

 while ( (unsigned long)(millis() - timeRef) < 2000 )
    {
        uint8_t button = key.button();
        if ( button != KEYPAD_NONE )
        {
            transition(TIME_OUT);
            
        }

    }
    transition(TIME_OUT);
}
void setContar(){
 
  totalSeconds = (EEPROM.read( ADDRESS+POS_MINEXP)*60)+ EEPROM.read( ADDRESS+POS_SECONEXP );
  
 /*lcd.clear();
    lcd.print(String(totalSeconds));
    delay(2000);*/

  Timer1.initialize(1000000);         // Dispara cada 1 s
  Timer1.attachInterrupt(ISR_Blink); // Activa la interrupcion y la asocia a ISR_Blink
  
  boolean timeOut = true;
  digitalWrite(RELAY_PIN,HIGH);
  while(totalSeconds >=0){
     uint8_t button = key.button();

        if ( button == KEYPAD_RIGHT )
        { 
          timeOut = false;
          break;
        }  

  }
  
  Timer1.stop();
  
   if ( !timeOut )
    {
     
      transition(KEYPAD_RIGHT);
      } 
    else transition(TIME_OUT);
}

void setFinContar(){
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LIGHT_PIN, HIGH);
  uint8_t button = key.button();
  lcd.clear();
  lcd.print(TEXT_TERMINAR); 
  zumbador.playRttl(RTTL_INTEL); 
  transition(TIME_OUT);

}

// Se ejecuta Cada segundo
void ISR_Blink(){
      // 
 int minutes = totalSeconds/60;
 int seconds = totalSeconds - minutes*60;
 totalSeconds-- ; 
 lcd.clear();
 lcd.print(TEXT_TEMPORIZANDO);
 lcd.setCursor(0,1);
 lcd.print(TEXT_MIN);
 if (minutes < 10) lcd.print (" ");
 lcd.print(String(minutes));
 lcd.print(TEXT_SEG);
 if (seconds < 10) lcd.print (" ");
 lcd.print(String(seconds));
 
}