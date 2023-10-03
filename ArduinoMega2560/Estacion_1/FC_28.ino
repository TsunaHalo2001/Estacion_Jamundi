//Metodo del dispositivo FC28
float getHumedadValor(void) {
  
  float humedad_valor = 0.0;
  int humedad_conver = 0;
  humedad_conver = analogRead(pin_sensor_humedad_suelo);
  humedad_valor = 100-(humedad_conver * 0.09765625);  //Conversion para valores de 0 a 100

  return humedad_valor;

}
