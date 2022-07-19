/**
  * @file medidor_1.ino
  * this program is the first attempt to work with a two digits   
  * seven segments display. It stay counting and stop when 
  * a push button is pressed.
*/  
bool push = LOW;
byte boton = 13;
byte unidad;
byte decena;
//This constants has the on and off outputs to form the digits in the 7segments display.
const byte segmentos[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};
//This enum keep the pins numbers to activate only one digit in a three digits number
enum lugar{
  centenas = 9,
  decenas = 10,
  unidades = 11
} digito;

void setup() {
  //  Initializing outputs for 7 segments display
  for(byte pata=1; pata <=12; pata++)pinMode(pata, OUTPUT);
  // Defining the pin number and direction for a pushbutton
  pinMode(boton,INPUT);
}

void loop() {
  push = LOW;
  unidad = 0;
  decena = 0;
  do{
    // "despliega" function, in this position show the decade digit in the 7 segment display
    despliega(segmentos[decena], decenas);
    do{
      push = digitalRead(boton);
      // In this position, "despliega" show the units digit in 7 segment display
      despliega(segmentos[unidad], unidades);
      unidad = unidad + 1;//Increase the units by one
      if(unidad > 9) unidad = 0;//Return to 0 after 9
    }while(unidad == 0);//when raised 9, the loop end
    decena = decena + 1;//Increase decades by 1
    if(decena > 9 ) decena = 0;//Return to 0 after 9
  }while(push == LOW);
  //Pulling the button. Remains pulling until the button is pushed 
  push = LOW;
  do{
    push = digitalRead(boton);
  }while(push == LOW);
  push = LOW;
}

//Despliega function receive the number to display (byte segmento)
//and the decimal position: units or decades (digit)
void despliega(byte segmento, byte digit){
  digitalWrite(digit, HIGH);
  digitalWrite(1, segmento & 0x80);
  digitalWrite(2, segmento & 0x40);
  digitalWrite(3, segmento & 0x20);
  digitalWrite(4, segmento & 0x10);
  digitalWrite(5, segmento & 0x08);
  digitalWrite(6, segmento & 0x04);
  digitalWrite(7, segmento & 0x02);
  delay(300);
  digitalWrite(digit,LOW);
}
