/*
PONTIFICIA UNIVERSIDAD CATÓLICA DEL PERÚ
Curso: Sistemas Digitales
Horario: H052D
Fecha: 13/09/2022
Autor: Anthony Valladolid Ballon
Estado: Probado en módulo Tiva TM4C123
Descripción:
El algoritmo sigue el siguiente flujo
1.- Encender el led de color blanco.
2.- El programa solicita el ingreso de un número N entre 3 y 9. 
3.- Si el número ingresado no está en el rango vuelve al paso 2.
4.- Encender el led de color cian
5.- Solicitar N números menores que 10.
6.- Mostrar mediante parpadeos rojos el mayor de los N números ingresados.
7.- Mostrar mediante parpadeos azules el menor de los N números ingresados.
8.- Mostrar mediante parpadeos verdes el promedio de los (N-2) números intermedios.
9.- Volver al paso 1.
*/

//Librerías
#include "stdint.h"
#include "tm4c123gh6pm.h"
#include "TivaES.h"

void SolicitaYParpadea(uint16_t);

//Código principal 
int main(void){
	uint16_t N;
	TivaES_Inicializa();   									//Setup de Puerto F
	while(1){
		TivaES_LedColor(BLANCO);							//Indicador de espera de lectura
		N=TivaES_SolicitaNumero(1,TRUE);			//Se limita la cantidad de dígitos a 1
		if(N>=3){ 														//Se validad que N este entre 3 y 9
			TivaES_LedColor(CIAN);								
			SolicitaYParpadea(N);								//Solicitud de números y respectivos parpadeos
		}		
	}

}

void SolicitaYParpadea(uint16_t N){
	uint8_t Max=0,Min=10,i=0,n_aux,prom;
	uint16_t suma=0;
	
	while(i<N){
		n_aux=TivaES_SolicitaNumero(1,TRUE); 			//Se solicita n de un dígito 
		suma+=n_aux;															//Se calcula la suma parcial 
		if(n_aux>Max){ 														//Se busca nuevo mayor
			Max=n_aux;
		}
		if(n_aux<Min){														//Se busca nuevo mínimo
			Min=n_aux;
		}
	i++;
	}
	prom=(suma-Min-Max)/(N-2);	//Promedio sin contar valores extremos
	TivaES_LedParpadeo(ROJO, Max);
	TivaES_LedParpadeo(AZUL, Min);
	TivaES_LedParpadeo(VERDE, prom);

} 