void recepcionDeDatos()
{
  if(banderaESPRx == 1){
        contadorFRAMEESPRX=0;
        Serial.println("Acaba de llegar el dato: ");
        Serial.println(ESPString);
        
        
        ptr = strtok(ESPString,"X");
        ptr = strtok(ESPString,"/");
               
        while(ptr != NULL){
            switch(contadorFRAMEESPRX){
                case 1:  posSAL    = atoi(ptr); break;
                case 2:  modoOPERA = atoi(ptr); break;
                case 3: setPoint  = atoi(ptr); break;
                case 4: banderaEscaMae  = ptr; break;
            }
            ptr = strtok(NULL,delimitadores);
            contadorFRAMEESPRX++;
        }
        Serial.println("Se cargaron los siguientes datos");
        Serial.println("PosSAL: "+String(posSAL));
        pasoscomp = posSAL;
        Serial.println("MODO OPERA: "+String(modoOPERA));
        Serial.println("setPoint: "+String(setPoint));
        Serial.println("BanderaEscaMae: "+banderaEscaMae);

        if(digitalRead(man_auto)==LOW)
        {
          modoOPERA = 2;
        }
        
       
       banderaESPRx = 0;
    }
  
}

void envioDatos()
{

  if(banderaEscaMae == "T")
  {
    Serial.print("Nivel 1  ");
    Serial.println(niv_compsal);
    Serial.print("Nivel 3  ");
    Serial.println(niv_compsal_cau);
    //campos a enviar
    //envio variables de control  y consumo de la estacion 2 a la estacion 1   
    paqueteDeEnvioConsumo =String(vdc_bat_comp2, DEC)+"/"+String(idc_bat_comp2, DEC)+"/"+String(cbat_comp2, DEC)+"/"+String(idc_siscomp2, DEC)+"/"+String(valcon_siscomp2, DEC);
    paqueteDeEnvioControl =String(niv_compsal, DEC)+"/"+String(niv_compsal_cau, DEC)+"/"+String(niv_compsal_ext, DEC)+"/"+detec_amax_comp2+"/"+detec_ctot_comp2+"/"+String(pos_comp2, DEC);
    Serial2.println("S/"+paqueteDeEnvioConsumo+"/"+paqueteDeEnvioControl+"/T"); 
    Serial.println("S/"+paqueteDeEnvioConsumo+"/"+paqueteDeEnvioControl+"/T"); 
    //lcd.setCursor(0,2);
    //lcd.print(paqueteDeEnvioConsumo+"/"+paqueteDeEnvioControl+"/T"); 
    banderaEscaMae = "F";
    inicio = 0;
    fin = 0;
  }  
}

void serialEvent2() {
  if( Serial2.available()  ) {
    char inChar = (char)Serial2.read();
    
    if (inChar == 'S') {
       banderaL=1;
    }
      if(banderaL==1){
        ESPString[indiceESPRX]= inChar;
        if(inChar == '/')
      {
        contadorseparador++; 
      } 
    if (inChar == 'X') {
      if(contadorseparador == 5)
      {
        Serial.println("ajio ajio");
        banderaESPRx = 1;
        indiceESPRX=0;
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
    else{
      indiceESPRX++;
    
    }
    }
  }
}
