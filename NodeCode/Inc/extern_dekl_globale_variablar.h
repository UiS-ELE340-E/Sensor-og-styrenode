//
// Fil: extern_dekl_globale_variablar.h
// m.t.240615

// Globale variablar kan bare deklarerast ein plass i programmet.
// I main.c kan ein inkludera fila "dekl_globale_variablar.h"
// I dei andre filene må ein inkludera såkalla extern-deklarasjonane
// som ein finn i fila "extern_dekl_globale_variablar.h"
//---------------------------------------------------------------------

//---------------------------------------
// Globale variablar
//---------------------------------------

//Control Card variables
//---------------------------------------
//Power
extern uint32_t prescalar;
extern uint32_t period;
extern uint32_t puls;
//PID
extern int16_t error;				// Error
extern int16_t error_past;
extern uint16_t up;					// Proportional quantity
extern uint16_t ui; 				// Integrator quantity
extern uint16_t ui_past;
extern uint16_t ud;					// Derivator quantity
extern uint16_t u;					// Power parameter
extern uint8_t direction;			// Direction pointer to LinMot

extern uint8_t IR_sensor_data_mask;
extern uint8_t accelerometer_data_mask;
extern uint16_t reference;

// Distance sensor data
//---------------------------------------
extern uint16_t sensor_data;
extern uint16_t distance;

// Interrupt variables
//---------------------------------------
extern volatile uint8_t USART3_rx[10];
extern volatile uint8_t USART3_rx_irq;

extern uint8_t node;

extern uint16_t sensor_data;

extern uint8_t communication;

extern uint8_t new_sample;
extern 	uint8_t slow_blink;

// DMA transfer variables
#define buffer_size 9
extern uint8_t transmit_buffer[buffer_size];		//USART 1
extern uint8_t data[buffer_size];

// For tilstandsmaskinen
//------------------------------------------------------
extern volatile uint8_t gyldig_trykk_av_USERbrytar;
extern uint8_t tilstand;

// For realisering av avprelling av brytar i programvare
//------------------------------------------------------
extern uint8_t brytar_var_nettopp_slept;
extern uint8_t nedtrykt_er_naa_USERbrytar;
extern uint8_t sleppteljar_USERbrytar;
extern uint8_t klar_for_nytt_trykk_av_USERbrytar;
extern uint8_t trykkteljar_USERbrytar;

// For realisering av brytarsjekk mm i SysTick-metoden
//------------------------------------------------------
extern uint8_t sample_time;
extern uint8_t  tikkteljar_avprelling;
extern uint16_t tikkteljar_diodar;
extern volatile uint8_t oppdater_diodar;

extern volatile uint8_t send_ny_tidsserie; // For � unng� at optimaliseringa fjernar tilh�yrande kode
extern uint16_t maaling_teljar;
extern uint16_t testmaaling;
extern uint16_t testteljar;

extern int8_t teikn;
extern uint8_t hex2ascii_tabell[16];

// Eksempel på variabeloppsett for ein PWM-kanal
//----------------------------------------------------

extern uint16_t PWM_periode; //Sjå dekl-fila
extern uint16_t PWM_vidde;
extern uint16_t PWM_preskalering;

// For realisering av sensoravlesing og tidsreferering av m�ledata
//----------------------------------------------------------------
extern uint16_t tikkteljar_sampling;
extern uint8_t  samplenr;
extern volatile uint8_t ny_maaling;

extern int16_t loggeverdi;
extern uint8_t diode_moenster;
extern int8_t  temperatur;

// Akselerometerspesifikke variablar
//-------------------------------------------------------
extern uint8_t buffer[6];

extern int16_t a_x;
extern int16_t a_y;
extern int16_t a_z;

extern int32_t a1;  //1.ordens filter basert p� 100Hz sampling og
extern int32_t b1;  //nedsampling til 10Hz => bandbreidde pi*5Hz
extern int32_t a_xf_k;
extern int32_t a_xf_k_1; //Foerre filterverdi
extern int32_t a_yf_k;
extern int32_t a_yf_k_1; //Foerre filterverdi
extern int32_t a_zf_k;
extern int32_t a_zf_k_1; //Foerre filterverdi

// For realisering av UART-kommunikasjon
//------------------------------------------------------
#define STX 0x02   // ASCII-koden for teiknet "Start of TeXt", meldingshovud her.
#define ETX 0x03   // ASCII-koden for teiknet "End of TeXt", meldingshale her.

extern uint8_t send_maalingar_til_loggar;
extern uint8_t send_maaling;
extern volatile uint8_t tikkteljar_uartkomm;
extern uint8_t legg_til_meldingshovud;
extern uint8_t legg_til_meldingshale;

extern uint8_t send_ei_brytarmelding_via_uart;
extern uint8_t  mottatt_data;
// Definisjonar og variablar for utskrift til LCD-skjerm
//-----------------------------------------------
#define LCD_Enable 0x8 //E=1
#define LCD_Disable 0x0 //E=0
#define LCD_Read 0x4 // R/*W=1
#define LCD_Write 0x0 // R/*W=0,
#define LCD_RS_data 0x2 // RS=1
#define LCD_RS_kommando 0x0 // RS=0

extern uint8_t skriv_til_LCD;
