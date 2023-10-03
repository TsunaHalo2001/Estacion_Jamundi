void init_SensorUltrasonico(int P_TRIGGE)
{
  // Ponemos el Triiger en estado bajo y esperamos 2 ms
  digitalWrite(P_TRIGGE,LOW);
  delayMicroseconds(2);
  
  // Ponemos el pin Trigger a estado alto y esperamos 10 ms
  digitalWrite(P_TRIGGE,HIGH);
  delayMicroseconds(10);
  
  // Comenzamos poniendo el pin Trigger en estado bajo
  digitalWrite(P_TRIGGE,LOW);
}

float get_nivel_lamina_agua(int P_ECH)
{
  
  // La función pulseIn obtiene el tiempo que tarda en cambiar entre estados, en este caso a HIGH
  unsigned long tiempo = pulseIn(P_ECH, HIGH);
  
  // La distancia del sensor se le resta a la formula para determinar la distancia dada por el, para determinar la altura de la lamina de agua
  float nivel_de_lamina = dis_sensor - (tiempo * 0.000001 * vel_soun / 2.0);
  

  return nivel_de_lamina;
}
