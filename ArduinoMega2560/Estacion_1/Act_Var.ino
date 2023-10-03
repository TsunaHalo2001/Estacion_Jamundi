void ActualizarVarAmb()
{
  if(cont_t>limt)
    {
      Serial.print("Posicion del codigo: ");
      Serial.println("Metodo de actualizacion de variables ambientales");
      Serial.print("Contador total posible del motor: ");
      Serial.println(rangocomp);
      Serial.print("Contador actual del motor: ");
      Serial.println(contadorpulsos);
      Serial.print("Posicion de la compuerta actual: ");
      Serial.println(pos_comp1);
    }
   DateTime now = rtc.now();
   annio=now.year();
   mes=now.month();
   dia=now.day();
   hora=now.hour();
   minn=now.minute();
   seg=now.second();

   //    Sensor radiacion
  radiacion_valor = getRadiationValue();
  radiacion_valor_prom=radiacion_valor_prom+radiacion_valor;
  radiacion_valor=0;
  //    Sensor Humedad del Suelo
  humedad_valor = getHumedadValor();
  humedad_valor_prom=humedad_valor_prom+humedad_valor;
  humedad_valor=0;
  //Sensor de Temperatura de Suelo
  sensorDS18B20.requestTemperatures();
  temp_suelo=sensorDS18B20.getTempCByIndex(0);
  temp_suelo_prom=temp_suelo_prom+temp_suelo;
  temp_suelo=0;

  //sensorVelViento
  Wind_Speed = getVelViento(windCont,timeWindSpeed);
  Wind_Speed_Temp= Wind_Speed_Temp + Wind_Speed;
  windCont = 0;
  
  //sensorPrecipitacion
  preci_actual = getPrecipitacion(rainCont, preci_actual);
  rainCont = 0;
  
  //Sensor de presion atmosferica
  char status;
  status = bmp180.startTemperature();//Inicio de lectura de temperatura
  if (status != 0)
  {
    delay(status); //Pausa para que finalice la lectura
    status = bmp180.getTemperature(T); //Obtener la temperatura
    T_prom = T_prom + T;
    if (status != 0)
    {
      status = bmp180.startPressure(3); //Inicio lectura de presión
      if (status != 0)
      {
        delay(status);//Pausa para que finalice la lectura
        status = bmp180.getPressure(P, T); //Obtenemos la presión
        P_prom = P_prom + (float)(P);
        if (status != 0)
        {
        }
      }
      P = 0;
    }
    T = 0;
  }
  //Sensor Humedad y Temperatura ambiente
  h = dht.readHumidity();
  h_prom = h_prom + h;
  h = 0;
  t = dht.readTemperature();
  t_prom = t_prom + t;
  t = 0;
  if (isnan(h) || isnan(t))
  {
  Serial.print("Error ");
  return;
  }
}

void ActualizarVarConsumo()
{
  if(cont_t>limt)
    {
      Serial.print("Posicion del codigo: ");
      Serial.println("Metodo de obtencion de variables de consumo");
      Serial.print("Contador total posible del motor: ");
      Serial.println(rangocomp);
      Serial.print("Contador actual del motor: ");
      Serial.println(contadorpulsos);
      Serial.print("Posicion de la compuerta actual: ");
      Serial.println(pos_comp1);
    }
  //Sensores analogos
  Sens_ConsumoV1=getConsumoV1();
  Sens_ConsumoC1=getConsumoC1();
  Sens_ConsumoC2=getConsumoC2();

  //Linealizacion de variables
  vdc_bat_comp1=(Sens_ConsumoV1*0.068)+22.0;
  idc_bat_comp1=Sens_ConsumoC1;
  cbat_comp1=Sens_ConsumoV1;
  idc_siscomp1= -1*Sens_ConsumoC2;
  valcon_siscomp1=vdc_bat_comp1*idc_siscomp1;
}

void actualizarVarControl() 
{
  
  init_SensorUltrasonico(pin_trigger1);
  niv_compadm = get_nivel_lamina_agua(pin_echo1);
  Serial.println(niv_compadm);
//
  init_SensorUltrasonico(pin_trigger2);
  niv_compadm_ext = get_nivel_lamina_agua(pin_echo2);
  Serial.println(niv_compadm_ext);
//
  init_SensorUltrasonico(pin_trigger3);
  niv_compadm_cau = get_nivel_lamina_agua(pin_echo3);
  Serial.println(niv_compadm_cau);
  
  pos_comp1 = contadorpulsos/pasototalcomp;
  pos1 = pos_comp1;
  EEPROM[6] = pos1;  
}
