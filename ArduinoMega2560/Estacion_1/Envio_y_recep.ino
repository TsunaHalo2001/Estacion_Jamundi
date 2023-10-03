//Metodo de envio de datos a la 2da estacion
void envioDatosaEsc()
{
  if(tiempo>=5)
  {
    Esc_a_Mae = "T";
    Serial2.println("S/"+String(posSAL, DEC)+"/"+modoOPERA+"/"+String(setPoint, DEC)+"/"+Esc_a_Mae+"/X");
    Serial.println("S/"+String(posSAL, DEC)+"/"+modoOPERA+"/"+String(setPoint, DEC)+"/"+Esc_a_Mae+"/X");
    tiempo=0;
   }
   tiempo++;
  if(Esc_a_Mae == "F")
  {
    Serial2.println("S/"+String(posSAL, DEC)+"/"+modoOPERA+"/"+String(setPoint, DEC)+"/"+Esc_a_Mae+"/X");
    Serial.println("S/"+String(posSAL, DEC)+"/"+modoOPERA+"/"+String(setPoint, DEC)+"/"+Esc_a_Mae+"/X");
  }
}

//Metodo de envio de variables ambientales
void EnviarVarAmb()
{
  //Se asigna la trama de tiempo al buffer      
  buffer_tx = "T/"+String(annio, DEC)+"/"+String(mes, DEC)+"/"+String(dia, DEC)+"/"+String(hora, DEC)+"/"+String(minn, DEC)+"/"+String(seg, DEC)+"/"+"F";
  Serial1.println(buffer_tx);
  Serial.print("Fecha: ");
  Serial.print(dia);
  Serial.print(":");
  Serial.print(mes);
  Serial.print(":");
  Serial.print(annio);
  Serial.print("      ");
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minn);
  Serial.print(":");
  Serial.println(seg);
  Serial.println(" ");

  radiacion_valor_prom=radiacion_valor_prom/Cont_Prom;
  temp_suelo_prom=temp_suelo_prom/Cont_Prom;
  humedad_valor_prom=humedad_valor_prom/Cont_Prom;
  t_prom=t_prom/Cont_Prom;
  h_prom=h_prom/Cont_Prom;
  P_prom=P_prom/Cont_Prom;
  Wind_Speed_Prom=Wind_Speed_Temp/Cont_Prom;
  

  buffer_tx = " ";
  Serial1.println(buffer_tx);

  //Se asigna la trama ambiental al buffer
  buffer_tx = "A/"+String(radiacion_valor_prom, DEC)+"/"+String(humedad_valor_prom, DEC)+"/"+String(t_prom, DEC)+"/"+String(h_prom, DEC)+"/"+String(temp_suelo_prom, DEC)+"/"+String(Wind_Speed_Prom, DEC)+"/"+String(preci_actual, DEC)+"/"+String(P_prom, DEC)+"/F";

  Serial1.println(buffer_tx);
  Serial.println(buffer_tx);

  Serial.println(" ");
  Serial.print("Radiación:   ");
  Serial.print(radiacion_valor_prom);
  Serial.println(" W/m^2");
  Serial.print("Temp s:      ");
  Serial.print(temp_suelo_prom);
  Serial.println(" °C");
  Serial.print("Hum Suelo:   ");
  Serial.print(humedad_valor_prom);
  Serial.println(" %");
  Serial.print("Temp amb:    ");
  Serial.print(t_prom);
  Serial.println(" °C  (DHT)");
  Serial.print("Temp amb:    ");
  Serial.print(T_prom);
  Serial.println(" °C (BMP180)");
  Serial.print("Hum amb:     ");
  Serial.print(h_prom);
  Serial.println(" %");
  Serial.print("Vel viento:  ");
  Serial.print(Wind_Speed_Prom);
  Serial.println(" Km/h");
  Serial.print("Lluvia:      ");
  Serial.print(preci_actual);
  Serial.println(" mm");
  Serial.print("Presión atm: ");
  Serial.print(P_prom);
  Serial.println(" mmHg");
  Serial.println(" ");   
}

//Metodo de envio de variables de consumo
void EnviarVarConsumo()
{
  //Se asigna la trama de consumo al buffer
  buffer_tx = " ";
  Serial1.println(buffer_tx);
  buffer_tx = "C/"+String(vdc_bat_comp1, DEC)+
               "/"+String(idc_bat_comp1, DEC)+
               "/"+String(vdc_bat_comp2 , DEC)+
               "/"+String(idc_bat_comp2, DEC)+
               "/"+String(cbat_comp1, DEC)+
               "/"+String(cbat_comp2, DEC)+
               "/"+String(idc_siscomp1, DEC)+
               "/"+String(idc_siscomp2, DEC)+
               "/"+String(valcon_siscomp1, DEC)+
               "/"+String(valcon_siscomp2, DEC)+"/F";
  Serial1.println(buffer_tx);
  Serial.println(buffer_tx);
  Serial.print("Vol Carga:   ");
  Serial.print(vdc_bat_comp1);
  Serial.print(" V  ");
  Serial.print(vdc_bat_comp2);
  Serial.println(" V  ");
  Serial.print("Curr carga:  ");
  Serial.print(idc_bat_comp1);
  Serial.print(" %  ");
  Serial.print(idc_bat_comp2);
  Serial.println(" %  ");
  Serial.print("Carga:  ");
  Serial.print(cbat_comp1);
  Serial.print(" A  ");
  Serial.print(cbat_comp2);
  Serial.println(" A");
  Serial.print("Curr Cons: ");
  Serial.print(idc_siscomp1);
  Serial.print(" A");
  Serial.print(idc_siscomp2);
  Serial.println(" A");
  Serial.print("Cons Watts: ");
  Serial.print(valcon_siscomp1);
  Serial.print(" W");
  Serial.print(valcon_siscomp2);
  Serial.println(" W");
  Serial.println(" ");
}

//Metodo de envio de variables de control
void EnviarVarControl()
{
  //Se asigna la trama de control al buffer  
  buffer_tx = " ";
  Serial1.println(buffer_tx);
  niv_lamagua = niv_compadm;
  buffer_tx = "N/"+String(niv_lamagua, DEC)+
              "/"+String(niv_compadm, DEC)+
              "/"+String(niv_compsal, DEC)+
              "/"+String(detec_amax_comp1, DEC)+
              "/"+String(detec_ctot_comp1, DEC)+
              "/"+String(detec_amax_comp2, DEC)+
              "/"+String(detec_ctot_comp2, DEC)+
              "/"+String(pos_comp1, DEC)+"/"+String(pos_comp2, DEC)+"/"+String(niv_compadm_ext, DEC)+
              "/"+String(niv_compadm_cau, DEC)+"/"+String(niv_compsal_ext, DEC)+"/"+String(niv_compsal_cau, DEC)+"/F";
  
  Serial1.println(buffer_tx);
  Serial.println(buffer_tx);
  
  Serial.println(" ");    
}

//Metodo de envio a la ESP32 para que inicie el envio al servidor
void EnviarEsp()
{
  //Se envia la bandera
  Serial1.println("E/enviar/F");
   Serial.println("E/enviar/F");
   Serial.println(" ");
   Serial.println(" ");
}

//Metodo de recepcion de datos por parte de la ESP32
void ReciboESP()
{
  if(banderaESPRx == 1)
  {
    contadorFRAMEESPRX=0;
    Serial.println("Acaba de llegar el dato: ");
    Serial.println(ESPString);
    
    
    ptr = strtok(ESPString,"#");
    ptr = strtok(ESPString,"/");
           
    while(ptr != NULL)
    {
      switch(contadorFRAMEESPRX)
      {
        case 1:  posADM    = atoi(ptr); break;
        case 2:  posSAL    = atoi(ptr); break;
        case 3:  modoOPERA = atoi(ptr); break;
        case 4:  tEnvioAux    = atoi(ptr); break;
        case 5:  mes       = atoi(ptr); break;
        case 6:  dia       = atoi(ptr); break;
        case 7:  annio     = atoi(ptr); break;
        case 8:  hora      = atoi(ptr); break;
        case 9:  minn   = atoi(ptr); break;
        case 10: seg  = atoi(ptr); break;
        case 11: setPoint  = atoi(ptr); break;
      }
      ptr = strtok(NULL,delimitadores);
      contadorFRAMEESPRX++;
    }
    Serial.println("Se cargaron los siguientes datos");
    pasoscomp = posADM;
    Serial.println("PosADM: "+String(posADM));
    Serial.println("PosSAL: "+String(posSAL));
    Serial.println("tEnvio: "+String(tEnvio));
    tEnvio = tEnvioAux*10;
    Serial.println("mes: "+String(mes));
    Serial.println("dia: "+String(dia));
    Serial.println("annio: "+String(annio));
    Serial.println("hora: "+String(hora));
    Serial.println("minutos: "+String(minn));
    Serial.println("segundos: "+String(seg));
    Serial.println("setPoint: "+String(setPoint));
//
    
  banderaESPRx = 0;
  }
}

//Metodo de error de recepcion de datos por parte de la ESP32
void ErrorRecibidoESP()
{
  if(banderaESPRx3 == 1)
  {
    contadorFRAMEESPRX=0;
    Serial.println("Acaba de llegar el dato: ");
    Serial.println(ESPString);
    ptr = strtok(ESPString,"#");
    ptr = strtok(ESPString,"/");
           
    while(ptr != NULL)
    {
      switch(contadorFRAMEESPRX)
      {
        case 1:  errorrecibo   = atoi(ptr); break;
      }
      ptr = strtok(NULL,delimitadores);
      contadorFRAMEESPRX++;
    }
  Serial.println("ERROR RECIBIENDO TRAMA VOLVIENDO A ENVIAR");
  errorrecibo = 1;
  banderaESPRx3 = 0;
  }
}

//Metodo de recepcion de datos de la 2da estacion
void ReciboEstacion2()
{
  if(banderaESPRx2 == 1)
  {
    contadorFRAMEESPRX=0;
    Serial.println("Acaba de llegar el dato: ");
    Serial.println(ESPString2);
    
    
    ptr = strtok(ESPString2,"T");
    ptr = strtok(ESPString2,"/");
           
    while(ptr != NULL)
    {
      switch(contadorFRAMEESPRX)
      {
        case 1:  vdc_bat_comp2    = atof(ptr); break;
        case 2:  idc_bat_comp2    = atof(ptr); break;
        case 3:  cbat_comp2 = atof(ptr); break;
        case 4:  idc_siscomp2    = atof(ptr); break;
        case 5:  valcon_siscomp2       = atof(ptr); break;
        case 6:  niv_compsal       = atof(ptr); break;
        case 7:  niv_compsal_cau     = atof(ptr); break;
        case 8:  niv_compsal_ext      = atof(ptr); break;
        case 9:  detec_amax_comp2   = atoi(ptr); break;
        case 10: detec_ctot_comp2  = atoi(ptr); break;
        case 11: pos_comp2  = atof(ptr); break;
      }
      ptr = strtok(NULL,delimitadores);
      contadorFRAMEESPRX++;
    }
    banderaESPRx2 = 0;
    Serial.println("Se cargaron los siguientes datos");
    Serial.println("vdc_bat_comp2: "+String(vdc_bat_comp2));
    Serial.println("idc_bat_comp2: "+String(idc_bat_comp2));
    Serial.println("cbat_comp2: "+String(cbat_comp2));
    Serial.println("idc_siscomp2: "+String(idc_siscomp2));
    Serial.println("valcon_siscomp2: "+String(valcon_siscomp2));
    Serial.println("niv_compsal: "+String(niv_compsal));
    Serial.println("niv_compsal_cau: "+String(niv_compsal_cau));
    Serial.println("niv_compsal_ext: "+String(niv_compsal_ext));
    Serial.println("detec_amax_comp2: "+String(detec_amax_comp2));
    Serial.println("detec_ctot_comp2: "+String(detec_ctot_comp2));
    Serial.println("pos_comp2: "+String(pos_comp2));
    Serial.println(" ");  
  }
}

//Metodo de recepcion de datos por el Serial 1
void serialEvent1()
{
  if( Serial1.available()  ) 
  {
    char inChar = (char)Serial1.read();
    if (inChar == 'V')
    {
      banderaL2 = 1;
    }
    if (inChar == 'S')
    {
      banderaL3 = 1;
    }
    if(banderaL3 == 1)
    {
      ESPString[indiceESPRX]= inChar;
      if (inChar == '#')
      {
        banderaESPRx3 = 1;
        indiceESPRX=0;
        banderaL3=0;
      }
      else{
        indiceESPRX++;
      }
    }
    if(banderaL2 == 1)
    {
      ESPString[indiceESPRX]= inChar;
      if(inChar == '/')
        {
          contadorseparador2++;
          
        }
      if (inChar == '#')
      {
        Serial.println(contadorseparador2);
        if(contadorseparador2 == 12)
        {
          banderaESPRx = 1;
          indiceESPRX=0;
          banderaL2=0;
          contadorseparador2 = 0;
        }
        else
        {
          contadorseparador2 = 0;
          banderaESPRx = 0;
          indiceESPRX=0;
          banderaL2=0;
          Serial1.print("G/enviar/F");
          Serial.print("Error recibiendo datos volviendo a pedir...");
          Serial.print("G/enviar/F");
        }
      }
      else
      {
        indiceESPRX++;
        banderaESPRx = 0;
      }
    }
  }
}

//Metodo de recepcion de datos a traves del serial 2
void serialEvent2()
{
  if( Serial2.available()  )
  {
    char inChar2 = (char)Serial2.read();
    if (inChar2 == 'S')
    {
      banderaL=1;
    }
    if(banderaL==1)
    {
      ESPString2[indiceESPRX2]= inChar2;
      if(inChar2 == '/')
      {
        contadorseparador++;
      }
    if (inChar2 == 'T')
    {
      if(contadorseparador >= 12)
      {
        Serial.println("ajio ajio");
        banderaESPRx2 = 1;
        indiceESPRX2=0;
        banderaL=0;
        contadorseparador = 0;
      }
      else
      {
        contadorseparador = 0;
        indiceESPRX2=0;
        banderaL=0;
      }
    }
    else
    {
      indiceESPRX2++;
    }
   }
  }
}
