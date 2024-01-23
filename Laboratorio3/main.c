/*
PONTIFICIA UNIVERSIDAD CATÓLICA DEL PERÚ
Curso: Sistemas Digitales
Horario: H052D
Fecha: 20/09/2022
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
#define SW4 0x20
#define ROJO        0x02      
#define AZUL        0x04     
#define VERDE       0x08     
#define MAGENTA     (ROJO|AZUL)
#define AMARILLO    (ROJO|VERDE)
#define BLANCO      (ROJO|VERDE|AZUL)
#define CIAN        (AZUL|VERDE)

//Prtotipo de funciones
void SetupPorts(void);
void Led(uint8_t );
void MostrarColoresYMaximo(uint8_t,uint8_t,uint8_t);
void MostrarMax(uint8_t );


//Programa principal
int main(void){
	
	uint8_t boton1=0;
	uint8_t boton2=0; 
	uint8_t boton4=0;
	uint16_t i=0; 	
	
	SetupPorts();
	
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
		}else if((GPIO_PORTA_DATA_R&SW4)!=0x00){//¿Botón 4 presionado?
			for(i=0;i<=5000;i++); //Retardo antirebote
			while((GPIO_PORTA_DATA_R&SW4) !=0x00);//Espera hasta que el botón sea soltado
			for(i=0;i<=5000;i++); //Retardo antirebote
			boton4++; //Se aumenta el contador asociado al botón 1			
		}
		MostrarColoresYMaximo(boton1,boton2,boton4);
		
	
	}
}

void SetupPorts(void)
{
	 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;					 //Activación de RELOJ del Puerto F 
	 while( (SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5)==0 ); //Espera que el RELOJ este activo
	
	 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;					 //Activación de RELOJ del Puerto A 
	 while( (SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0)==0 ); //Espera que el RELOJ este activo
	
	 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;					 //Activación de RELOJ del Puerto B 
	 while( (SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R1)==0 ); //Espera que el RELOJ este activo
	
	 GPIO_PORTF_LOCK_R = 0x4C4F434B; // Desbloquear puerto F
		
	//Entradas
	 GPIO_PORTF_CR_R |= SW2;			  // Se habilita PF0 (SW2)
	 GPIO_PORTF_DIR_R &= ~(0x11); 	// Configuración de PF4 y PF0 como entradas
	 GPIO_PORTF_AFSEL_R &= ~(0x11); // Desactivar funciones alternas de PF4 y PF0
	 GPIO_PORTF_PUR_R |= 0x11; 		  // Activa resistencias de pull-up 
	 GPIO_PORTF_DEN_R |= 0x11;			// Habilitación de funciones digitales
	 
	 GPIO_PORTA_DIR_R &= ~(0x20);   //PA5 como entrada
	 GPIO_PORTA_DEN_R |= 0x20;			//Funciones digitales de PA5

	 //Salidas
	 GPIO_PORTF_DIR_R |= 0xE;       //Pin PF1,PF2,PF3 como salida
	 GPIO_PORTF_DIR_R |= 0xE;       //Driver de corriente se asocia a la salidas PF1,PF2,PF3
	 GPIO_PORTF_DEN_R |= 0XE;       //Habilitar en PF1,PF2,PF3 la función digital
	 GPIO_PORTF_DATA_R &= ~(0XE);   //Apagado de LEDs
	 
	 GPIO_PORTB_DIR_R |= 0XF0;       //PB4,PB5,PB6,PB7 como salida
	 GPIO_PORTB_DIR_R |= 0XF0;       //Driver de corriente se asocia a la salidas PB4,PB5,PB6,PB7
	 GPIO_PORTB_DEN_R |= 0XF0;       //Habilitar en PB4,PB5,PB6,PB7 la función digital
	 GPIO_PORTB_DATA_R &= ~(0XF0);   //Apagado de LEDs
	 
}

void Led(uint8_t color){
	GPIO_PORTF_DATA_R=(GPIO_PORTF_DATA_R&0xFFFFFFFF1)|color;  //Se enciende unicamente los leds asociados al color
}

void MostrarColoresYMaximo(uint8_t boton1,uint8_t boton2,uint8_t boton4){
	uint8_t max;
	if(boton1==boton4 && boton2==boton4){ //Tres cantidades iguales
		Led(BLANCO);
		max=boton1;
	}else if(boton1==boton4 || boton2==boton1 || boton4==boton2){ //Dos cantidades iguales
		Led(AZUL);
		if(boton1>=boton4 && boton1>=boton2){
			max=boton1;
		}else if(boton2>=boton1 && boton2>=boton4){
			max=boton2;
		}else if(boton4>=boton2 && boton4>=boton1){
			max=boton4;
		}
	}else if(boton1>boton2 && boton1>boton4){ //Boton1 mayor cantidad de veces presionado
		Led(MAGENTA);
		max=boton1;
	}else if(boton2>boton1 && boton2>boton4){ //Boton2 mayor cantidad de veces presionado
		Led(AMARILLO);
		max=boton2;	
	}else{																		//Boton4 mayor cantidad de veces presionado
		Led(CIAN);
		max=boton4;	
	}
	MostrarMax(max);
	
}
void MostrarMax(uint8_t max){
	GPIO_PORTB_DATA_R=(GPIO_PORTB_DATA_R&0xFFFFFFF0F)|(max<<4); //Se limpia el arreglo de led y luego se escribe

}
	