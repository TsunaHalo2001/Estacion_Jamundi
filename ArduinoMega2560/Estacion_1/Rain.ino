float getPrecipitacion(volatile int rainCont,double preci_actual) {
  
  double preci_temp = 0;

  preci_temp = rainCont * 0.2794; // Conversión para precipitación


    preci_actual =preci_actual + preci_temp;
    

  
  return preci_actual;
}

// Interrupción del pluviometro
void rainCounterInterrupt() {
  if (millis() - rainTime > Banda) {
    rainCont++;
    rainTime = millis();
    if (rainCont == 1) {
      preci_actual = getPrecipitacion(rainCont, preci_actual);
    }
  }
}
