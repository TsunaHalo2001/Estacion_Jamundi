void ActualizarVarConsumo(){
  
  
    //Sensores analogos
    Sens_ConsumoV1=getConsumoV1();
    Sens_ConsumoC1=getConsumoC1();
    Sens_ConsumoC2=getConsumoC2();
    
    vdc_bat_comp2=(Sens_ConsumoV1*0.068)+22.0;
    idc_bat_comp2=Sens_ConsumoC1;
    cbat_comp2=Sens_ConsumoV1;
    idc_siscomp2= -1*Sens_ConsumoC2;
    valcon_siscomp2=vdc_bat_comp2*idc_siscomp2;
         
}

void capturaValoresControl()
{
  
  init_SensorUltrasonico(pin_trigger1);
  niv_compsal = get_nivel_lamina_agua(pin_echo1);
  
  init_SensorUltrasonico(pin_trigger2);
  niv_compsal_ext = get_nivel_lamina_agua(pin_echo2);
  
  init_SensorUltrasonico(pin_trigger3);
  niv_compsal_cau = get_nivel_lamina_agua(pin_echo3);
  
  pos_comp2 = contadorpulsos/pasototalcomp ;
  
}
