/*
PONTIFICIA UNIVERSIDAD CATÓLICA DEL PERÚ
Curso: Sistemas Digitales
Horario: H052D
Fecha: 06/09/2022
Autor: Anthony Valladolid Ballon
Estado: Probado en módulo Tiva TM4C123
Descripción: Parpadeo en bucle siguiendo la secuencia de color verde por un tiempo T, en azul por un tiempo 2T y en rojo por un tiempo 3T
*/

//Bibliotecas
#include "stdint.h"
#include "tm4c123gh6pm.h"
//Constantes
#define T_DELAY 1600000

//Programa principal
int main(void){
	uint32_t i=0; 
	
	//Configuración de pines a usar 
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;       //Habilitar el reloj del puerto F
	while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5)==0);//Esperar a que se haya habilitado el reloj del puerto F
	GPIO_PORTF_DIR_R |= 0xE;                      //Pin PF1,PF2,PF3 como salida
	GPIO_PORTF_DIR_R |= 0xE;                      //Driver de corriente se asocia a la salidas PF1,PF2,PF3
	GPIO_PORTF_DEN_R |= 0XE;                      //Habilitar en PF1,PF2,PF3 la función digital
	
	//Lazo de funcionamiento del programa	
	while(1){
		GPIO_PORTF_DATA_R|=0x08;                //Encender LED VERDE
		for(i=0;i<=T_DELAY;i++){};                //Esperar
		GPIO_PORTF_DATA_R&=~0x08;               //Apagar LED VERDE

		GPIO_PORTF_DATA_R|=0x04;                //Encender LED AZUL
		for(i=0;i<=2*T_DELAY;i++){};                //Esperar
		GPIO_PORTF_DATA_R&=~0x04;               //Apagar LED AZUL

		GPIO_PORTF_DATA_R|=0x02;                //Encender LED ROJO
		for(i=0;i<=3*T_DELAY;i++){};                //Esperar
		GPIO_PORTF_DATA_R&=~0x02;               //Apagar LED ROJO
		
	}
}
