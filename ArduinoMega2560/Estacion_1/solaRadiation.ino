float getRadiationValue(void) {
  
  float radiacion_valor = 0.0;
  int radiacion_conver = 0;
  radiacion_conver = analogRead(pin_sensor_radiacion);
  radiacion_valor = radiacion_conver * 2.93255132; // Conversión para radiacion solar de 0 a 1800

  return radiacion_valor;

}
