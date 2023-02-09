/*
PONTIFICIA UNIVERSIDAD CATÓLICA DEL PERÚ
Curso: Sistemas Digitales
Horario: H052D
Fecha: 19/09/2022
Autor: Anthony Valladolid Ballon
Estado: Probado en módulo Tiva TM4C123
Descripción: El programa presenta un color determinado según la cantidad de veces que se presionan los botones 
*/

//Bibliotecas
#include "stdint.h"
#include "tm4c123gh6pm.h"
 
//Constantes
#define SW2 0x01
#define SW1 0x10
#define ROJO        0x02      
#define AZUL        0x04     
#define VERDE       0x08     
#define MAGENTA     (ROJO|AZUL)
#define AMARILLO    (ROJO|VERDE)
#define BLANCO      (ROJO|VERDE|AZUL)

//Prtotipo de funciones
void SetupPortF(void);
void Led(uint8_t );

//Programa principal
int main(void){
	
	uint8_t boton1=0;
	uint8_t boton2=0; 
	uint16_t i=0; 	
	
	SetupPortF();
	
	while(1){
		if((GPIO_PORTF_DATA_R&SW1)==0x00){ //¿Botón 1 presionado?
			for(i=0;i<=5000;i++); //Retardo antirebote
			while((GPIO_PORTF_DATA_R&SW1) ==0x00);//Espera hasta que el botón sea soltado
			for(i=0;i<=5000;i++); //Retardo antirebote
			boton1++; //Se aumenta el contador asociado al botón 1
		}else if((GPIO_PORTF_DATA_R&SW2)==0x00){ //¿Botón 2 presionado?
			for(i=0;i<=5000;i++);//Retardo antirebote
			while((GPIO_PORTF_DATA_R&SW2) ==0x00); //Espera hasta que el botón sea soltado
			for(i=0;i<=5000;i++); //Retardo antirebote
			boton2++;	//Se aumenta el contador asociado al botón 2
		}	
		
		if(boton1==boton2){Led(BLANCO); //Ambos botones fueron presionados la misma cantidad de veces
		}else if(boton1>boton2){Led(MAGENTA); //El botón 1 se presionó más veces que el botón 2
		}else{Led(AMARILLO);}					//El botón 2 se presionó más veces que el botón 1
		
	}
}

void SetupPortF(void)
{
	 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;					 //Activación de RELOJ del Puerto F 
	 while( (SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5)==0 ); //Espera que el RELOJ este activo
	 
	 GPIO_PORTF_LOCK_R = 0x4C4F434B; // Desbloquear puerto F
		
	//Entradas
	 GPIO_PORTF_CR_R |= SW2;			  // Se habilita PF0 (SW2)
	 GPIO_PORTF_DIR_R &= ~(0x11); 	// Configuración de PF4 y PF0 como entradas
	 GPIO_PORTF_AFSEL_R &= ~(0x11); // Desactivar funciones alternas de PF4 y PF0
	 GPIO_PORTF_PUR_R |= 0x11; 		  // Activa resistencias de pull-up 
	 GPIO_PORTF_DEN_R |= 0x11;			// Habilitación de funciones digitales

	 //Salidas
	 GPIO_PORTF_DIR_R |= 0xE;       //Pin PF1,PF2,PF3 como salida
	 GPIO_PORTF_DIR_R |= 0xE;       //Driver de corriente se asocia a la salidas PF1,PF2,PF3
	 GPIO_PORTF_DEN_R |= 0XE;       //Habilitar en PF1,PF2,PF3 la función digital
	 GPIO_PORTF_DATA_R &= ~(0XE);   //Apagado de LEDs
}

void Led(uint8_t color){
	GPIO_PORTF_DATA_R=(GPIO_PORTF_DATA_R&0xFFFFFFFF1)|color;  //Se enciende unicamente los leds asociados al color
}
	