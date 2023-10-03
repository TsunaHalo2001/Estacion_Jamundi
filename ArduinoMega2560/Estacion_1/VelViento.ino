float getVelViento(volatile int windCont,int timeWindSpeed) {
   
  float windSpeed = (windCont) * 2.4 / timeWindSpeed;  // Conversión para velocidad del viento
  
  return windSpeed;

}

// Interrupciín del anemometro
void windCounterInterrupt()
{
  //   Debounce o Antirebote por código
  if (millis() - windTime > Banda)
  {

    windCont++;
    windTime = millis();
  }
}
