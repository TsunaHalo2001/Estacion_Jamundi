#include "config.hpp"

void setup() {
  // put your setup code here, to run once:
  //Se inicializa la comunicacion serial
  //Comunicacion con PC
  Serial.begin(9600);

  //Comunicacion con modulo LoRA
  Serial2.begin(9600);

  wdt_disable();

  //Se inicializan los pines
  pinMode(detc_amax_comp2,INPUT_PULLUP);
  pinMode(detc_ctot_comp2,INPUT_PULLUP);
  pinMode(bup,INPUT_PULLUP);
  pinMode(bdown,INPUT_PULLUP);
  pinMode(man_auto,INPUT_PULLUP);

  pinMode(Dir,OUTPUT);
  pinMode(Step,OUTPUT);
  pinMode(Ena,OUTPUT);

  pinMode(pin_trigger1, OUTPUT);
  pinMode(pin_echo1, INPUT);

  pinMode(pin_trigger2, OUTPUT);
  pinMode(pin_echo2, INPUT);

  pinMode(pin_trigger3, OUTPUT);
  pinMode(pin_echo3, INPUT);

  //Condicional de reinicio de datos en EEPROM
  if(digitalRead(detc_amax_comp2)==LOW && digitalRead(detc_ctot_comp2)==LOW && digitalRead(bup)==LOW && digitalRead(bdown)==LOW)
  {
    EEPROM[0]=0;
    delay(50);
    EEPROM[1]=0;
    delay(50);
    EEPROM[2]=0;
    delay(50);
    EEPROM[3]=0;
    delay(50);
    EEPROM[4]=0;
    delay(50);
    EEPROM[5]=0;
    delay(50);
    EEPROM[6]=0;
    delay(50);
    EEPROM[8]=0;
    delay(50);
  }

  //Toma de datos de EEPROM
  rangocomp5 = EEPROM[5];
  delay(50);
  rangocomp4 = EEPROM[4];
  delay(50);
  rangocomp3 = EEPROM[3];
  delay(50);
  rangocomp2 = EEPROM[2];
  delay(50);
  rangocomp1 = EEPROM[1];
  delay(50);
  
  rangocomp = rangocomp5;
  delay(50);
  rangocomp = rangocomp + (rangocomp4<<4);
  delay(50);
  rangocomp = rangocomp + (rangocomp3<<8);
  delay(50);
  rangocomp = rangocomp + (rangocomp2<<12);
  delay(50);
  rangocomp = rangocomp + (rangocomp1<<16);
  delay(50);
  Serial.println(rangocomp);
  
  pasototalcomp = rangocomp/100;
  tolepaso = pasototalcomp/20;
  pasoscomp = EEPROM[8];
  delay(50);
  Serial.println(pasoscomp);
  contadorpulsos = pasototalcomp*pasoscomp;

  //Se inicializa la interrupcion del motor
  SREG = (SREG & 0b01111111);
  TIMSK2 = TIMSK2|0b00000001;
  TCCR2B = 0b00000010;
  SREG = (SREG & 0b01111111) | 0b10000000;

  wdt_enable(WDTO_8S);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Condicion de comunicacion
  if(banderaL == 1)
  {
  }
  else
  {
    //Condicion de control manual
    if(digitalRead(man_auto)==LOW)
    {
      modoOPERA = 2;
    }
    if(digitalRead(man_auto)==HIGH && modoOPERA==2)
    {
      modoOPERA = 1;
    }

    //Metodo de consumo
    if(Cont_C>=tConsumo)
    {
      
    ActualizarVarConsumo();
    capturaValoresControl();
    Cont_C = 0;
    wdt_reset();
    }

    //Metodo de control
    if(Cont_N>=tControl || modoOPERA == 2)
    {
      
      capturaValoresControl();
      controlCompuertaAdm();
    
      Cont_N = 0;
      wdt_reset();
    }

    //Metodo de envio a 1era estacion
    envioDatos();

    //Contadores
if(conts>=3000)
{
  pos2 = pos_comp2;
  EEPROM[8] = pos2;
  delay(50);
  conts=0;
}

    
    delay(250);
    Cont_C++;
    conts++;
    Cont_N++;
    cont_t++;

    if(cont_t>limt)
    {
      Serial.print("Posicion del codigo: "+ String(modoOPERA));
      Serial.println("Final del codigo");
      Serial.print("Contador actual del motor: ");
      Serial.println(contadorpulsos);
      Serial.println(contadorobjetivo);
      Serial.print("Posicion de la compuerta actual: ");
      Serial.println(pos_comp2);
      cont_t = 0;
    }
    wdt_reset();

    //Metodo de recepcion
    recepcionDeDatos();
  }
}
