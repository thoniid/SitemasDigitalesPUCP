/*
PONTIFICIA UNIVERSIDAD CATÓLICA DEL PERÚ
Curso: Sistemas Digitales
Horario: H052D
Fecha: 09/09/2022
Autor: Anthony Valladolid Ballon
Estado: Probado en módulo Tiva TM4C123
Descripción:
Programa que solicita un número en el rango de 0 a 99, muestra el color blanco 
y espera que se presione y suelte el pulsador SW1 para mostrar las unidades y decenas
del número ingresado acorde a ciertas condiciones.
*/

//Librerías
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "TivaES.h"

//Código principal 
void main(void){
	uint16_t n;                             //Número ingresado por el usuario 
	uint8_t dec_n,uni_n,suma;               //Variables auxiliares
	TivaES_Inicializa();                    //Configuración de los periféricos
	while(1){
		n=TivaES_SolicitaNumero(2,TRUE);			//Lectura del número
		TivaES_LedColor(BLANCO);							//Se muestra el color blanco		
		TivaES_EsperaPulsador(SW1);						//Se espera que se presione el botón	
		dec_n=n/10; 													//Cálculo de decenas 
		uni_n=n%10;														//Cálculo de unidades 
		if(n<50){															//Si N<50
			TivaES_LedParpadeo(ROJO, dec_n);		//Se muestran las decenas a traves del led rojo
			TivaES_LedParpadeo(AZUL, uni_n);		//Se muestran las unidades a traves del led azul
		}else{																//Si no,
			suma=dec_n+uni_n;										//Se calcula la suma de decenas y unidades para
			TivaES_LedParpadeo(CIAN,suma);			//mostrarla con parpadeos de color CIAN.
		}
	}
}