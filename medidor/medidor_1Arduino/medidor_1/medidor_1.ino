/**
  * @file medidor_1.ino
  * this program take a measure with an ultrasonic sensor, calculate    
  * the distance and then display it in the 7-segments three digits display. 
*/ 

volatile boolean push = LOW;   //variable that save the button state
const byte disparo = 12; //Number of the pin that triggers the sensor function
const byte boton  = 13;//Number of the pin in which is connected the shot button
const byte sensor = 14;//Number of pin in wich is connected the shot button
double distancia  = 0; //Variable that keep the distance calculated/measure
double eco = 0;        //Variable that saves a value proportional with the measured distance
byte unidades = 0;    //variable that saves units from the counter
byte decenas  = 0;    //variable that saves decades from the counter
byte centenas = 0;    //variable that saves hundreds from the counter

void setup() {
  //  Initializing outputs for 7 segments display
  for(byte i=1; i<=12; i++)pinMode(i, OUTPUT);
  // Defining the pin number and direction for a pushbutton
  pinMode(disparo,OUTPUT);//Initialize pin for shot the sensor
  pinMode(boton, INPUT);//Initialize pin to check the shot button status
  pinMode(sensor,INPUT);//Initialize pin to check the sensor signal
}

void loop() {
  //Check the start button status
  push = digitalRead(boton);//This function get a free noise signal from 'boton'
  //When start button is pushed, measuring are done
  if(push == HIGH){
    //Measured distance are obtained from the proportional value given by the sensor
    //This value are given us throught the 'Lectura_de_distancia' function
    distancia = Lectura_de_distancia(disparo, sensor)/58.2;
    //Dividing the number to get hundreds
    centenas    = distancia / 100;
    distancia   = distancia - (centenas * 10);
    //Dividing the number to get decades
    decenas     = distancia / 10;
    distancia   = distancia - (decenas * 10);
    //Getting units
    unidades    = distancia;
    //Resetting 'distancia' variable
    distancia   = 0;
  }
  push = LOW; //Cleaning the start button status
  //'Despliega' function, display measured distance in three digits, 7-segments display
  Despliega(centenas, decenas, unidades);
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

/* The function 'Lectura_de_distancia' drive the ultrasonic sensor and 
 *  return a value that is proportional with the distance measured.
 *  Receive the number pins for trigger (byte trigger) 
 *  and sensor response (byte sensor)
 */
float Lectura_de_distancia (byte trigger, byte sensor){
  //First we send a high pulse that remain in high for 10 miliseconds
  //The signal are sending throught 'trigger' pin
  digitalWrite(trigger,LOW);
  delay(2);
  digitalWrite(trigger,HIGH);
  delay(10);
  digitalWrite(trigger,LOW);
  
  eco = 0;//Initialize 'eco' variable
  //Get a value proportional with the measured distance. 
  eco = pulseIn(sensor, HIGH);
  // Sending the obtained value
  return (eco);
  
}
