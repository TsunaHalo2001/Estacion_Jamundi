//interrupcion timer 
ISR(TIMER2_OVF_vect){
  //Contador de PWM
  cuenta++;
  //Condicion de PWM
  if(cuenta>=topee)
  {
    //PWM
    digitalWrite(Step,ESTADO);
    ESTADO = !ESTADO;
    cuenta=-1;

    if(ESTADO==true && calibracion == 1 && inicioC==true)
    {
      direccion = motor_Girar_Izquierda();
      contadorpulsos++;
    }
    
    //Direccion contra las manecillas del reloj
    if(ESTADO==true && calibracion == 0)
    {
      if(contadorobjetivo > contadorpulsos)
      {
        direccion = motor_Girar_Derecha();
        contadorpulsos++;
      }

      if(contadorobjetivo < contadorpulsos)
      {
        direccion = motor_Girar_Izquierda();
        contadorpulsos--;
      }

      if(contadorobjetivo == contadorpulsos)
      {
        direccion = motor_Parar();
      }

      if(contadorpulsos > rangocomp)
      {
        direccion = motor_Parar();
        contadorpulsos--;
      }

      if(contadorpulsos < 0)
      {
        direccion = motor_Parar();
        contadorpulsos++;
      }
    }
  }   
}

//Metodo que designa la posicion del motor
void  controlCompuertaAdm()
{
 
  //Error, si la compuerta esta por encima del setpoint el valor es negativo
  //si la compuerta esta por debajo del setpoint el valor es positivo
  error = setPoint - niv_compadm;

  //Si el valor de nivel esta entre el rango de tolerancia entonces la posicion sera el setpoint
  if((niv_compadm >=  (setPoint - tole_lamiagua)) && (niv_compadm <=  (setPoint + tole_lamiagua)) )
  {
    pasosautobuscar = setPoint;
  }
  //Si el valor de nivel esta por encima o debajo del setpoint entre un valor de tolerancia, la posicion sera el setpoint + el error
  else if(niv_compadm >= (setPoint - 10) && (niv_compadm <= (setPoint + 10)))
  {
    pasosautobuscar = (setPoint+error);
  }

  //Si el error es mucho menor la compuerta se cierra completamente
  else if(error<0)
  {
    pasosautobuscar = 0;
  }

  //Si el error es mucho mayor la compuerta se abre completamente
   else if(error>0)
  {
    pasosautobuscar = 100;
  }

  //Rutina de calibracion
  if(rangocomp<1000)
  {
    Serial.print("Posicion del codigo: ");
    Serial.println("Condicional de calibracion");
    Serial.print("Contador total posible del motor: ");
    Serial.println(rangocomp);
    Serial.print("Contador actual del motor: ");
    Serial.println(contadorpulsos);
    Serial.print("Posicion de la compuerta actual: ");
    Serial.println(pos_comp1);
    wdt_disable();
    //Se pone en modo de calibracion para la interrupcion
    calibracion = 1;
    //Se abre la compuerta hasta que se presione el boton y se setea el contador en 0
    while(inicioO == true)
    {
      direccion = motor_Girar_Derecha();
      detec_amax_comp1 = digitalRead(detc_amax_comp1);
      if(detec_amax_comp1 == 0)
      {
       inicioO = false;
       contadorpulsos=0;
      }
    }

    //Se cierra la compuerta hasta que se presione el boton mientras se acumula el contador
    while(inicioC == true)
    {
      direccion = motor_Girar_Izquierda();
      detec_ctot_comp1 = digitalRead(detc_ctot_comp1);
      
      //Muestra la cantidad actual del contadorpulsos
      if(sec<=segs)
      {
        Serial.println(contadorpulsos);
        segs=0;
      }
      segs++;
      delay(1);

      //Se presiona el boton y se registra la informacion en la EEPROM
      if(detec_ctot_comp1 == 0)
      {
         direccion = motor_Parar();
         inicioC = false;
         rangocomp = contadorpulsos;
    
         Serial.println(rangocomp);
    
         EEPROM[5] = rangocomp & 0b1111;
         delay(50);
         EEPROM[4] = (rangocomp>>4) & 0b1111;
         delay(50);
         EEPROM[3] = (rangocomp>>8) & 0b1111;
         delay(50);
         EEPROM[2] = (rangocomp>>12) & 0b1111;
         delay(50);
         EEPROM[1] = (rangocomp>>16) & 0b1111;
         delay(50);
         pasototalcomp = rangocomp/100;
         tolepaso = pasototalcomp/20;
         contadorpulsos=0;
         EEPROM[6]=0;
    
         calibracion = 0;
      }
    }
    wdt_enable(WDTO_8S);
  }
  //Se inicializan las variables diseñadas para el funcionamiento de la posicion
  pasototalcomp = rangocomp/100;
  tolepaso = 1;

  //Indicador de apertura maxima
  if(contadorpulsos >= rangocomp)
  {
    detec_amax_comp1 = 1;
  }
  
  //Indicador de cierre total
  else if(contadorpulsos <= 0)
  {
    detec_ctot_comp1 = 1;
  }
  else
  {
    detec_amax_comp1 = 0;
    detec_ctot_comp1 = 0;
  }

  //Giro del motor en modo automatico
  if(modoOPERA == 0)
  {
    
    
    contadorobjetivo = pasosautobuscar*pasototalcomp;
  }

  //Giro del motor en modo manual
  else if(modoOPERA == 1)
  {
    
    pasosbuscar = pasoscomp;
    contadorobjetivo = pasosbuscar*pasototalcomp;
  }

  //Giro del motor con el control manual
  else if(modoOPERA == 2)
  {
    
    //Antirebote del boton de bajar la compuerta
    if(digitalRead(bup)==LOW)
    {
      wdt_disable();
      
      while(digitalRead(bup)==LOW)
      {
        pasosmanualbuscar++;
        delay(500);
      }
      pasosmanualbuscar++;
      if(pasosmanualbuscar>100)
      {
        pasosmanualbuscar=100;
      }
      wdt_enable(WDTO_8S);
    }
    //Antirebote del boton de bajar la compuerta
    if(digitalRead(bdown)==LOW)
    {
      wdt_disable();
      
      while(digitalRead(bdown)==LOW)
      {
        pasosmanualbuscar--;
        delay(500);
      }
      pasosmanualbuscar--;
      if(pasosmanualbuscar<0)
      {
        pasosmanualbuscar=0;
      }
      wdt_enable(WDTO_8S);
    }
    
    contadorobjetivo = pasosmanualbuscar*pasototalcomp;
  }
}
