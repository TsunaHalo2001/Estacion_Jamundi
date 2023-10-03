// Creamos variables de consumo de la compuerta 1
float Vol_Bat1=0.0, Vol_Bat2=0.0, Vol_Bat=0.0;
float consumoV1=0.0, consumoV2=0.0;
float I_Bat1=0.0, I_Bat2=0.0;
float consumoC1=0.0,consumoC2=0.0;
float sensibilidad = 0.066;
int n_muestras=0;
float getConsumoV1(void){
  
  consumoV1=analogRead(Pin_ConsV1);
  Vol_Bat1=(consumoV1*m)-b;
  consumoV2=analogRead(Pin_ConsV2);
  Vol_Bat2=(consumoV2*m)-b;
  Vol_Bat=(Vol_Bat1+Vol_Bat2)/2;

  return Vol_Bat;
}

float getConsumoC1(void){
  float I_Bat1=0.0;
  consumoC1=analogRead(Pin_ConsC1)*(5.0/1023.0);
  I_Bat1=-((consumoC1-2.5)/sensibilidad);
  return I_Bat1;
}
float getConsumoC2(void){
 float I_Bat2=0.0;
  consumoC2=analogRead(Pin_ConsC2)*(5.0/1023.0);
  I_Bat2=-((consumoC2-2.5)/sensibilidad);
  return I_Bat2;
}
