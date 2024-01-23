/*
PONTIFICIA UNIVERSIDAD CAT�LICA DEL PER�
Curso: Sistemas Digitales
Horario: H052D
Fecha: 13/09/2022
Autor: Anthony Valladolid Ballon
Estado: Probado en m�dulo Tiva TM4C123
Descripci�n:
El algoritmo sigue el siguiente flujo
1.- Encender el led de color blanco.
2.- El programa solicita el ingreso de un n�mero N entre 3 y 9. 
3.- Si el n�mero ingresado no est� en el rango vuelve al paso 2.
4.- Encender el led de color cian
5.- Solicitar N n�meros menores que 10.
6.- Mostrar mediante parpadeos rojos el mayor de los N n�meros ingresados.
7.- Mostrar mediante parpadeos azules el menor de los N n�meros ingresados.
8.- Mostrar mediante parpadeos verdes el promedio de los (N-2) n�meros intermedios.
9.- Volver al paso 1.
*/

//Librer�as
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "TivaES.h"

void SolicitaYParpadea(uint16_t);

//C�digo principal 
int main(void){
	uint16_t N;
	TivaES_Inicializa();   									//Setup de Puerto F
	while(1){
		TivaES_LedColor(BLANCO);							//Indicador de espera de lectura
		N=TivaES_SolicitaNumero(1,TRUE);			//Se limita la cantidad de d�gitos a 1
		if(N>=3){ 														//Se validad que N este entre 3 y 9
			TivaES_LedColor(CIAN);								
			SolicitaYParpadea(N);								//Solicitud de n�meros y respectivos parpadeos
		}		
	}

}

void SolicitaYParpadea(uint16_t N){
	uint8_t Max=0,Min=10,i=0,n_aux,prom;
	uint16_t suma=0;
	
	while(i<N){
		n_aux=TivaES_SolicitaNumero(1,TRUE); 			//Se solicita n de un d�gito 
		suma+=n_aux;															//Se calcula la suma parcial 
		if(n_aux>Max){ 														//Se busca nuevo mayor
			Max=n_aux;
		}
		if(n_aux<Min){														//Se busca nuevo m�nimo
			Min=n_aux;
		}
	i++;
	}
	prom=(suma-Min-Max)/(N-2);	//Promedio sin contar valores extremos
	TivaES_LedParpadeo(ROJO, Max);
	TivaES_LedParpadeo(AZUL, Min);
	TivaES_LedParpadeo(VERDE, prom);

} 