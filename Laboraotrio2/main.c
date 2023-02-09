/*
PONTIFICIA UNIVERSIDAD CAT�LICA DEL PER�
Curso: Sistemas Digitales
Horario: H052D
Fecha: 09/09/2022
Autor: Anthony Valladolid Ballon
Estado: Probado en m�dulo Tiva TM4C123
Descripci�n:
Programa que solicita un n�mero en el rango de 0 a 99, muestra el color blanco 
y espera que se presione y suelte el pulsador SW1 para mostrar las unidades y decenas
del n�mero ingresado acorde a ciertas condiciones.
*/

//Librer�as
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "TivaES.h"

//C�digo principal 
void main(void){
	uint16_t n;                             //N�mero ingresado por el usuario 
	uint8_t dec_n,uni_n,suma;               //Variables auxiliares
	TivaES_Inicializa();                    //Configuraci�n de los perif�ricos
	while(1){
		n=TivaES_SolicitaNumero(2,TRUE);			//Lectura del n�mero
		TivaES_LedColor(BLANCO);							//Se muestra el color blanco		
		TivaES_EsperaPulsador(SW1);						//Se espera que se presione el bot�n	
		dec_n=n/10; 													//C�lculo de decenas 
		uni_n=n%10;														//C�lculo de unidades 
		if(n<50){															//Si N<50
			TivaES_LedParpadeo(ROJO, dec_n);		//Se muestran las decenas a traves del led rojo
			TivaES_LedParpadeo(AZUL, uni_n);		//Se muestran las unidades a traves del led azul
		}else{																//Si no,
			suma=dec_n+uni_n;										//Se calcula la suma de decenas y unidades para
			TivaES_LedParpadeo(CIAN,suma);			//mostrarla con parpadeos de color CIAN.
		}
	}
}