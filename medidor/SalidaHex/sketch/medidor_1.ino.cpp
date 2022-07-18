#include <Arduino.h>
#line 1 "/home/mariana/Escritorio/Proyectos/medidor/Programas/medidor_1/medidor_1.ino"
bool push = LOW;
byte boton = 13;
byte unidad;
byte decena;
const byte segmentos[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xE6};
enum lugar{
  centenas = 9,
  decenas = 10,
  unidades = 11
} digito;

#line 12 "/home/mariana/Escritorio/Proyectos/medidor/Programas/medidor_1/medidor_1.ino"
void setup();
#line 17 "/home/mariana/Escritorio/Proyectos/medidor/Programas/medidor_1/medidor_1.ino"
void loop();
#line 39 "/home/mariana/Escritorio/Proyectos/medidor/Programas/medidor_1/medidor_1.ino"
void despliega( byte segmento, byte digit);
#line 12 "/home/mariana/Escritorio/Proyectos/medidor/Programas/medidor_1/medidor_1.ino"
void setup() {
  for(byte pata=1; pata <=12; pata++)pinMode(pata, OUTPUT);
  pinMode(boton,INPUT);
}

void loop() {
  push = LOW;
  unidad = 0;
  decena = 0;
  do{
    despliega(segmentos[decena], decenas);
    do{
      push = digitalRead(boton);
      despliega(segmentos[unidad], unidades);
      unidad = unidad + 1;
      if(unidad > 9) unidad = 0;
    }while(unidad == 0);
    decena = decena + 1;
    if(decena > 9 ) decena = 0;
  }while(push == LOW);
  push = LOW;
  do{
    push = digitalRead(boton);
  }while(push == LOW);
  push = LOW;
}

void despliega( byte segmento, byte digit){
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

