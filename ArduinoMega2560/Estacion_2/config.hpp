#define CONFIG_HPP

#include <EEPROM.h>
#include <PinChangeInterrupt.h>
#include <avr/wdt.h>

#define Pin_ConsV1  A4
#define Pin_ConsV2  A6
#define Pin_ConsC1  A8
#define Pin_ConsC2  A10

#define pin_trigger1   12
#define pin_echo1      13
#define pin_trigger2   10
#define pin_echo2      11
#define pin_trigger3   8
#define pin_echo3      9
#define separador '/'
#define m  0.7906388361796               //0.4887585532746
#define b  323.7824161922831             //199.99999999996

//Envio y recepcion de datos

char *strtok(char *str1, const char *str2);//subfunción
char *ptr = NULL;

char banderaESPRx = 0, banderaESPRx2 = 0, banderaESPRx3 = 0;
int banderaL = 0, banderaL2 = 0, banderaL3 = 0, contadorseparador = 0;
char ESPString[100]="", indiceESPRX=0;
char ESPString2[150]="", indiceESPRX2=0;
char contadorFRAMEESPRX=0;

char delimitadores[]="/";

//

float Sens_ConsumoV1 = 0.0;  ////////////////////////////////////
float Sens_ConsumoV2 = 0.0;  //Variables de sensores de consumo//
float Sens_ConsumoC1 = 0.0;  ////////////////////////////////////
float Sens_ConsumoC2 = 0.0;  ////////////////////////////////////
float Vol_Bat1=0.0, Vol_Bat2=0.0, Vol_Bat=0.0;
float consumoV1=0.0, consumoV2=0.0;
float I_Bat1=0.0, I_Bat2=0.0;
float consumoC1=0.0,consumoC2=0.0;
float sensibilidad = 0.066;
int n_muestras=0;
float vdc_bat_comp1= 0.0, vdc_bat_comp2= 0.0; /////////////////////////////////////////
float idc_bat_comp1= 0.0, idc_bat_comp2= 0.0; //  Variables para consumo de baterias //
float cbat_comp1= 0.0, cbat_comp2= 0.0;       /////////////////////////////////////////
float idc_siscomp1= 0.0, idc_siscomp2= 0.0;   /////////////////////////////////////////
float valcon_siscomp1= 0.0, valcon_siscomp2= 0.0; /////////////////////////////////////

float niv_lamagua;
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
float niv_desagua;
float niv_desagua_analog;
float error =0.0;
float niv_salida = 0.0;
String niv_desagua_St;
bool inicioP=true;
bool inicioC = true, inicioO = true;
const int tole_lamiagua = 3;
float setPoint = 0;
//SoftwareSerial Serial2(0,1); //RX TX

// variable de control de la estación 2 
float niv_compsal = 0.0;  
float niv_compsal_cau = 0.0; 
float niv_compsal_ext = 0.0; 
bool detec_amax_comp2=0; 
bool detec_ctot_comp2=0;
float pos_comp2=0.0;
char pos2 = 0;

// variables extras 
String mensaje=" ";
String paqueteDeEnvioConsumo=" ";
String paqueteDeEnvioControl=" ";
int inicio=0, fin=0;
String banderaEscaMae="F";

const float vel_soun =  34300.0;
const float dis_sensor = 50; // cambiar por el valor de altura verdadero

const int Dir=34;
const int Step=32;
const int Ena=36;

const int detc_amax_comp2 = 29;
const int detc_ctot_comp2 = 28;
const int bup = 30;
const int bdown = 31;
const int man_auto = 27;
int mancon = 0;

//Variables de motor

int seg=0,sec=1000;
int cuenta = 0;
bool ESTADO = false;
signed long int contadorpulsos=0, conts=0, topemax=0, topemin=0, rangocomp=0, pasoscomp=0, pasosautocomp=0, pasototalcomp=0, tolepaso = 1, pasosautobuscar = 100, pasosbuscar = 100,pasosmanualbuscar=100, contadorobjetivo=0, rangocomp1 =0, rangocomp2 =0, rangocomp3 =0, rangocomp4 =0, rangocomp5 =0;
int topee=0;
int direccion = 0;
int calibracion = 0;

int posSAL,modoOPERA = 1;

int Cont_C = 0, Cont_N = 7200, cont_t=0;
int tConsumo = 4, tControl=7200, limt=20;

ISR(TIMER2_OVF_vect);
void serialEvent2();

void ActualizarVarConsumo();
void capturaValoresControl();
void  controlCompuertaAdm();
int motor_Girar_Derecha();
int motor_Girar_Izquierda();
int motor_Parar();
void recepcionDeDatos();
void envioDatos();
void init_SensorUltrasonico(int P_TRIGGE);
float get_nivel_lamina_agua(int P_ECH);
float getConsumoV1(void);
float getConsumoC1(void);
float getConsumoC2(void);
