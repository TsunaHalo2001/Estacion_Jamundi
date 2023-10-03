#include "config.hpp"

void setup() {
  // put your setup code here, to run once:
  
  //Se inicializa la comunicacion Serial
    //Serial para la comunicacion con un computador
    Serial.begin(9600);
    
    //Serial 1 para la comunicacion con la ESP32
    Serial1.begin(9600);
    
    //Serial 2 para la comunicacion con el modulo LoRA
    Serial2.begin(9600);

    wdt_disable();

  //Se inicializan los pines a utilizar
    //Se inicializan los pines del control manual
    pinMode(detc_amax_comp1,INPUT_PULLUP);
    pinMode(detc_ctot_comp1,INPUT_PULLUP);
    pinMode(bup,INPUT_PULLUP);
    pinMode(bdown,INPUT_PULLUP);
    pinMode(man_auto,INPUT_PULLUP);

    //Se inicializa el pin del Anemometro
    pinMode(windPulsePin, INPUT_PULLUP); 

    //Se inicializa el pin del pluviometro
    pinMode(rainPulsePin, INPUT_PULLUP);

    //Se inicializan los pines de los sensores de nivel
    pinMode(pin_trigger1, OUTPUT);
    pinMode(pin_echo1, INPUT);
    pinMode(pin_trigger2, OUTPUT);
    pinMode(pin_echo2, INPUT);
    pinMode(pin_trigger3, OUTPUT);
    pinMode(pin_echo3, INPUT);

    //Se inicializan los pines del driver
    pinMode(Dir,OUTPUT);
    pinMode(Step,OUTPUT);
    pinMode(Ena,OUTPUT);

  //Se inicializan los metodos
    //Se inicializa el metodo de presion atmosferica
    bmp180.begin();

    //Se inicializa el metodo de humedad del aire
    dht.begin();

    //Se inicializa el metodo de temperatura del suelo
    sensorDS18B20.begin();

    //Se inicializa ell reloj en tiempo real
    if (!rtc.begin())
    {
      Serial.println(F("Couldn't find RTC"));
    }
    if (rtc.lostPower())
    {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    
  //Se inicializan las interrupciones
    //Se inicializa la interrupcion del anemometro
    attachInterrupt(digitalPinToInterrupt(windPulsePin), windCounterInterrupt, FALLING);

    //Se inicializa la interrupcion del pluviometro
    attachInterrupt(digitalPinToInterrupt(rainPulsePin), rainCounterInterrupt, FALLING);

    //Se inicializa la interrupcion del motor
    SREG = (SREG & 0b01111111);
    TIMSK2 = TIMSK2|0b00000001;
    TCCR2B = 0b00000010;
    SREG = (SREG & 0b01111111) | 0b10000000;

  //Se crea el metodo de reinicio de la EEPROM
  if(digitalRead(detc_amax_comp1)==LOW && digitalRead(detc_ctot_comp1)==LOW && digitalRead(bup)==LOW && digitalRead(bdown)==LOW)
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
    EEPROM[7]=0;
    delay(50);
  }

  //Se toman e interpretan los datos de la EEPROM
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

  rangocomp = pasototalcomp*100;
  tolepaso = pasototalcomp/20;
  pasoscomp = EEPROM[6];
  delay(50);
  Serial.println(pasoscomp);
  contadorpulsos = pasototalcomp*pasoscomp;

  wdt_enable(WDTO_8S);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Se añade un condicional de funcionamiento que limita el funcionamiento del codigo cuando hay comunicacion
  if(banderaL==1 || banderaL2==1 || banderaL3==1)
  {
  }
  
  //Se incluye el programa principal
  else
  {
    //Sistema de tiempo para banderas
    
    //Condicion para la activacion del modo manual por control fisico
    if(digitalRead(detc_amax_comp1)==LOW && digitalRead(detc_ctot_comp1)==LOW)
    {
      while(digitalRead(detc_amax_comp1)==LOW);
      modoOPERA = 2;
    }
    if(digitalRead(detc_amax_comp1)==LOW && digitalRead(detc_ctot_comp1)==LOW && modoOPERA == 2)
    {
      while(digitalRead(detc_amax_comp1)==LOW);
      modoOPERA = 1;
    }
    //Obtenemos la hora actual
    DateTime now = rtc.now();

    //Valor de alerta de precipitacion
    if(cont_A>=12)
    {
       cont_A=0;
       if((preci_actual-preci_min) > Valor_Alerta)
       { 
          cont_E=tEnvio;
       }
       
       else
       {
         preci_min=preci_actual; 
       }
    }

    //Metodos de control de compuertas
    if(tControl<=cont_N)
    {
       if(modoOPERA == 1 || modoOPERA ==0)
       {
       Serial.println("control");
       }
       actualizarVarControl(); 
       controlCompuertaAdm();
       cont_N = 0;
    }
    
    //Muestreo de variables
    if(tMuestreo<cont_M)
    {
        
       timeWindSpeed=tMuestreo;
       
       //Muestreo de variables ambientales
       ActualizarVarAmb();
       Cont_Prom++;

       //Muestreo de variables de consumo
       ActualizarVarConsumo();

       //Muestreo de variables de control
       actualizarVarControl();

       //Envio de bandera a 2da estacion
       envioDatosaEsc();

       cont_A++;
       cont_M=0;
       wdt_reset();
    }
    tEnvio1 = tEnvio/3;

    tEnvio2 = tEnvio1*2;
    //Envio de variables
    if (tEnvio1<cont_E && casoN==0)
    {buffer_tx = "T/"+String(annio, DEC)+"/"+String(mes, DEC)+"/"+String(dia, DEC)+"/"+String(hora, DEC)+"/"+String(minn, DEC)+"/"+String(seg, DEC)+"/"+"F";
  Serial1.println(buffer_tx);
      EnviarVarControl();EnviarEsp();
      casoN = 1;
    }
    if(tEnvio2<cont_E && casoC==0)
    {buffer_tx = "T/"+String(annio, DEC)+"/"+String(mes, DEC)+"/"+String(dia, DEC)+"/"+String(hora, DEC)+"/"+String(minn, DEC)+"/"+String(seg, DEC)+"/"+"F";
  Serial1.println(buffer_tx);
      EnviarVarConsumo();EnviarEsp();
      casoC=1;
    }
    if (tEnvio<cont_E)
    {
      
      Wind_Speed_Prom=Wind_Speed_Temp/Cont_Prom;
      //Envio de datos con delay entre si para evitar conflictos de tramas
      EnviarVarAmb();
      
      delay(500);
      EnviarEsp();
      casoN=0;
      casoC=0;
      //Se reinician las variables involucradas
      Cont_Prom=0;
      Wind_Speed_Temp=0;
      preci_actual=0;
      cont_E=0;
      cont_M=0;
      temp_suelo_prom=0;
      P_prom = 0;
      T_prom = 0;
      h_prom = 0;
      t_prom = 0;
      radiacion_valor_prom = 0;
      humedad_valor_prom = 0;
      temp_suelo_prom =0;
      wdt_reset();
    }
    //En caso de un error de recepcion por parte de la ESP32 se solicitan de nuevo los datos
    if (errorrecibo == 1)
    {
      
      Wind_Speed_Prom=Wind_Speed_Temp/Cont_Prom;
      EnviarVarAmb();      
      delay(500);      
      EnviarVarConsumo();
      delay(500);           
      EnviarVarControl();
      delay(500);  
      EnviarEsp();
      Cont_Prom=0;
      Wind_Speed_Temp=0;
      preci_actual=0;
      cont_M=0;
      temp_suelo_prom=0;
      P_prom = 0;
      T_prom = 0;
      h_prom = 0;
      t_prom = 0;
      radiacion_valor_prom = 0;
      humedad_valor_prom = 0;
      temp_suelo_prom =0;
      errorrecibo = 0;
      wdt_reset();
    }

    //Contadores que determinan los tiempos
    delay(100);
      //Contador de muestreo
      cont_M++;

      //Contador de envio
      cont_E++;

      //Contador de control
      cont_N++;

      //Contador de N segundos
      cont_t++;

    //Sistema de tiempo para banderas
    if(cont_t>limt)
    {
      Serial.print("Posicion del codigo: "+ String(modoOPERA));
      Serial.println("Final del codigo");
      Serial.print("Contador actual del motor: ");
      Serial.println(contadorpulsos);
      Serial.println(contadorobjetivo);
      Serial.print("Posicion de la compuerta actual: ");
      Serial.println(pos_comp1);
      Serial.println(Wind_Speed_Temp);
      Serial.println(preci_actual);
      Serial.println(cont_E);
      Serial.println(tEnvio1);
      Serial.println(tEnvio2);
      Serial.println(tEnvio);
      cont_t = 0;
    }
    wdt_reset();
    

    //Metodos de envio y recepcion
    ErrorRecibidoESP();
    ReciboESP();
    ReciboEstacion2();
  }
}
