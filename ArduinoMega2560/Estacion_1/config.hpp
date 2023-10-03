#define CONFIG_HPP

#include <EEPROM.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SFE_BMP180.h>
#include <Wire.h>
#include "RTClib.h"
#include <PinChangeInterrupt.h>
#include <avr/wdt.h>

#define DHTPIN 7
#define DHTTYPE DHT22

/*Se definen los valores de m y b para la linealizacion. De forma que cuando el voltaje sea de 2V en la entrada, muestre en la salida 0% y cuando la entrada
  sea de 3V, muestre en la salida 100%.*/
#define m  0.7906388361796               //0.4887585532746
#define b  323.7824161922831             //199.99999999996
// Se definen los pines analogos donde se hará la conexion
#define Pin_ConsV1  A4
#define Pin_ConsV2  A6
#define Pin_ConsC1  A8
#define Pin_ConsC2  A10

//Pines para nivel de agua
#define pin_trigger1   12
#define pin_echo1      13
#define pin_trigger2   10
#define pin_echo2      11
#define pin_trigger3   8
#define pin_echo3      9

//Envio y recepcion de datos

char *strtok(char *str1, const char *str2);//subfunción
char *ptr = NULL;

char banderaESPRx = 0, banderaESPRx2 = 0, banderaESPRx3 = 0;
int banderaL = 0, banderaL2 = 0, banderaL3 = 0, contadorseparador = 0, contadorseparador2 = 0;
char ESPString[100]="", indiceESPRX=0;
char ESPString2[200]="", indiceESPRX2=0;
char contadorFRAMEESPRX=0;

int errorrecibo = 0;

char delimitadores[]="/";

String buffer_tx;
int annio, mes, dia, hora, minn, seg;

int posADM, posSAL = 0, modoOPERA = 1;

//Pines de sensores ambientales
 
const byte windPulsePin = 3;
const byte rainPulsePin = 2;

const int pin_sensor_radiacion = A0;
const int pin_sensor_humedad_suelo = A2;
const int pin_sensor_temp_suelo = 5;

//Parametros ambientales

#define Valor_Alerta 0.5             // Para lluvia  0.28 o menos ... Para lluvia Fuerte entre 0.28 y 0. 

//Pines de los motores

const int Dir=34;
const int Step=32;
const int Ena=36;

//pines para detectar la posicion de la compuerta 
const int detc_amax_comp1 = 29;
const int detc_ctot_comp1 = 28;
const int bup = 30;
const int bdown = 31;
const int man_auto = 27;
int mancon = 0;

//Parametros de nivel de agua

const float vel_soun = 34300.0;
const float dis_sensor = 50; // cambiar por el valor de altura verdadero

//Variables ambientales

float radiacion_valor = 0.0, radiacion_valor_prom=0.0;  //Variable para radiación solar
float humedad_valor = 0.0, humedad_valor_prom=0.0;    // Variable para humedad del suelo
float temp_suelo = 0.0, temp_suelo_prom=0.0;
float Wind_Speed =0.0;        //Variable para velocidad del viento
float Wind_Speed_Temp= 0.0;
float Wind_Speed_Prom= 0.0;
int Cont_Prom=0;
float h,t =0.0;   // Variables para temperatura y humedad ambiente
float h_prom = 0, t_prom = 0;
float timeWindSpeed = 0;  //CAMBIAR SEGUN TIEMPO DE MUESTREO
double preci_actual = 0;  //Variable para precipitacion
double preci_min = 0;
double T, P;              //Variable para temperatura y presion atmosferica del sensor de presion atmosferia (BMP180)
float T_prom = 0.0, P_prom = 0.0;
volatile int windCont = 0; //Variable volatil para la interrupción d velocidad de viento
volatile int rainCont = 0; //Variable volatil para la interrupción de precipitacion
const int Banda = 150;    
long windTime = 0;
long rainTime = 0;

//Variables de consumo

float Sens_ConsumoV1 = 0.0;  ////////////////////////////////////
float Sens_ConsumoV2 = 0.0;  //Variables de sensores de consumo//
float Sens_ConsumoC1 = 0.0;  ////////////////////////////////////
float Sens_ConsumoC2 = 0.0;  ////////////////////////////////////

float vdc_bat_comp1= 0.0, vdc_bat_comp2= 0.0; /////////////////////////////////////////
float idc_bat_comp1= 0.0, idc_bat_comp2= 0.0; //  Variables para consumo de baterias //
float cbat_comp1= 0.0, cbat_comp2= 0.0;       /////////////////////////////////////////
float idc_siscomp1= 0.0, idc_siscomp2= 0.0;   /////////////////////////////////////////
float valcon_siscomp1= 0.0, valcon_siscomp2= 0.0; /////////////////////////////////////

//Variables de nivel de agua

float error= 0.0;
bool inicioC = true, inicioO = true;
const int tole_lamiagua = 3;
float setPoint = 0;

//Variables de motor

int segs=0,sec=1000;
int cuenta = 0;
bool ESTADO = false;
signed long int contadorpulsos=0, topemax=0, topemin=0, rangocomp=0, pasoscomp=0, pasosautocomp=0, pasototalcomp=0, tolepaso = 0, pasosautobuscar = 0, pasosbuscar = 0,pasosmanualbuscar=0, contadorobjetivo = 0, rangocomp1= 0, rangocomp2= 0, rangocomp3= 0, rangocomp4= 0, rangocomp5= 0;
int topee=0;
int direccion = 0;
int calibracion = 0;

//Variables de envio

long int tMuestreo=50, tEnvio=3000, tEnvio1=1000, tEnvio2=2000, tEnvioAux=300, tControl=18000, limt=50;
long int casoA = 0, casoN = 0, casoC = 0;  
long int cont_M=0, cont_E=0, cont_A=0, cont_N=18000, cont_t=0;

//Variables de envio de nivel de agua
float niv_lamagua=0.0; 
float niv_compsal = 0.0; 
float niv_compadm = 0.0; 
float niv_compadm_ext = 0.0; 
float niv_compadm_cau = 0.0; 
float niv_compsal_cau = 0.0; 
float niv_compsal_ext = 0.0; 
bool detec_amax_comp1=0; 
bool detec_amax_comp2=0; 
bool detec_ctot_comp1=0;
bool detec_ctot_comp2=0;
float pos_comp1=0.0;
float pos_comp2=0.0;
char pos1=0;

//variables extras
int i = 0;
int j = 0;
float valorLamAgua[2]= {0,0};
float sensorValor = 0;
String mensaje = " ";
String Esc_a_Mae="F";
String banderaDeRecibido="F";
int tiempo = 0;
int inicio=0, fin=0;

//Definicion de sensores

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWireObjeto(pin_sensor_temp_suelo);
DallasTemperature sensorDS18B20(&oneWireObjeto);
SFE_BMP180 bmp180;
RTC_DS3231 rtc;

//Interrupciones
ISR(TIMER2_OVF_vect);
void serialEvent1();
void serialEvent2();
void windCounterInterrupt();
void rainCounterInterrupt();

//Metodos ambientales
float getTime (String daysOfTheWeek[7],String monthsNames[12]);
float getPrecipitacion (volatile int Cont, double preci_actual);
float getRadiationValue(void);
float getHumedadValor(void);
float getPresion(void);
float getVelViento(volatile int windCont, int TimeWindSpeed);
double getDirViento(void);

//Metodos de consumo

float getConsumoV1(void);
float getConsumoC1(void);
float getConsumoC2(void);

//Metodos de los motores

int motor_Girar_Derecha();
int motor_Girar_Izquierda();
int motor_Parar();

//Metodos de control

void  controlCompuertaAdm();

//Metodos de Nivel de agua

void init_SensorUltrasonico(int P_TRIGGE);
float get_nivel_lamina_agua(int P_ECH);

//Actualizacion de variables

void ActualizarVarAmb();
void ActualizarVarConsumo();
void actualizarVarControl();

//Envio y recepcion

void envioDatosaEsc();
void EnviarVarAmb();
void EnviarVarConsumo();
void EnviarVarControl();
void EnviarEsp();
void ErrorRecibidoESP();
void ReciboESP();
void ReciboEstacion2();
