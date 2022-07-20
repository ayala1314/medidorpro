/**
  * @file medidor_1.ino
  * this program generate a three digits number and   
  * then display it in the 7-segments display. A counter start
  * counting and stop when the push button is pressed, then the
  * reached number are showed.
*/  
volatile boolean push = LOW;   //variable that save the button state
const byte boton = 13;//pin in wich the button are connected
byte unidades = 0;    //variable that saves units from the counter
byte decenas = 0;     //variable that saves decades from the counter
byte centenas = 0;    //variable that saves hundreds from the counter
byte cuenta = 0;      //variable used to get hundreds, decades and units
byte contador = 0;    //variable used in the counter

void setup() {
  //  Initializing outputs for 7 segments display
  for(byte i=1; i<=12; i++)pinMode(i, OUTPUT);
  // Defining the pin number and direction for a pushbutton
  pinMode(boton,INPUT);
}

void loop() {
  //The next loop, increase the 'contador' var until push button is pushed
  do{
    push = digitalRead(boton);
    contador = contador + 1;
    if(contador > 999) contador = 0;//Return to 0 after 999
  }while(push == LOW);// If the push button is pushed, the count stop.
  push = LOW;
  cuenta   = contador;//'cuenta' variable will be used todivide the number
  //Dividing the number to get hundreds
  centenas = cuenta / 100;
  cuenta   = cuenta - (centenas * 10);
  //Dividing the number to get decades
  decenas  = cuenta / 10;
  cuenta   = cuenta - (decenas * 10);
  //Getting units
  unidades = cuenta;
  //Resetting 'cuenta' variable
  cuenta   = 0;
  //'Despliega' function, display three digits in 7-segments display
  do{
    Despliega(centenas, decenas, unidades);
    digitalWrite(12,push);
    if(push == HIGH)break;
  }while(!(detectaFlanco(boton)));//Quit from the loop in descendent sidewall
}

/*'Despliega' function receive three numbers to display in the 7 segment display
the number with three digits; hundreds, decades and units.*/
void Despliega( byte centenas, byte decenas, byte unidades ){
  
  byte pin_unidades = 11;// pin to select units 7-segments display
  byte pin_decenas = 10; // pin to select decades 7-segments display
  byte pin_centenas = 9; // pin to select hundreds 7-segments display
  // array with the pines to be change in the 7-segments display
  byte segmentos[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};
  
  digitalWrite(pin_unidades, HIGH); 
  digitalWrite(1, segmentos[unidades] & 0x80);
  digitalWrite(1, segmentos[unidades] & 0x40);
  digitalWrite(1, segmentos[unidades] & 0x20);
  digitalWrite(1, segmentos[unidades] & 0x10);
  digitalWrite(1, segmentos[unidades] & 0x08);
  digitalWrite(1, segmentos[unidades] & 0x04);
  digitalWrite(1, segmentos[unidades] & 0x02);
  delay(5);
  digitalWrite(pin_unidades, LOW);
  digitalWrite(pin_decenas, HIGH);
  digitalWrite(1, segmentos[decenas] & 0x80);
  digitalWrite(1, segmentos[decenas] & 0x40);
  digitalWrite(1, segmentos[decenas] & 0x20);
  digitalWrite(1, segmentos[decenas] & 0x10);
  digitalWrite(1, segmentos[decenas] & 0x08);
  digitalWrite(1, segmentos[decenas] & 0x04);
  digitalWrite(1, segmentos[decenas] & 0x02);
  delay(5);
  digitalWrite(pin_decenas, LOW);
  digitalWrite(pin_centenas, HIGH);
  digitalWrite(1, segmentos[centenas] & 0x80);
  digitalWrite(1, segmentos[centenas] & 0x40);
  digitalWrite(1, segmentos[centenas] & 0x20);
  digitalWrite(1, segmentos[centenas] & 0x10);
  digitalWrite(1, segmentos[centenas] & 0x08);
  digitalWrite(1, segmentos[centenas] & 0x04);
  digitalWrite(1, segmentos[centenas] & 0x02);
  delay(5);
  digitalWrite(pin_centenas, LOW);
}

/*The 'detectaFlanco' function check the input especified by 
 * 'pin' parameter and return:
 *  1  if we have an ascendent sidewall
 * -1  if it detect an descendent sidewall
 *  0  if we have not any change
 */
int detectaFlanco(int pin){
  //'anterior_estado' keep the last value detected in the pin
  static boolean anterior_estado = digitalRead(pin);
  //'estado' has the actual value detected in the pin
  boolean estado = digitalRead(pin);
  //first if: we have a change
  if (anterior_estado != estado){
    //Change from LOW to HIGH
    if (estado == HIGH) {
      anterior_estado = estado;
      return 1;
    }
    //Change from HIGH to LOW
    else {
      anterior_estado = estado;
      return -1;
    }
  }
  //No change in the pin
  else {
    return 0;  
  }
}
