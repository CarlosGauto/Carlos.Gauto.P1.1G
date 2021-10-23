#include "Validaciones.h"

void ProcesoCorrecto(int retorno, char mensajeCorrecto[], char mensajeError[])
{
	if (retorno == 1)
	{
		printf("\n%s\n",mensajeCorrecto);
	}
	else
	{
		printf("\n%s\n",mensajeError);
	}

}

int ValidarEnteroConMaxMin(char opcionIngresada[],char mensajeError[], int min, int max)
{
	int resultadoValidado = 0;
	int contadorError;
	contadorError = 0;

	while(contadorError < 2)
	{
		contadorError++;
		if(ValidarEntero(opcionIngresada) == 0 || funcionMaxMin(opcionIngresada, min, max) == 0)
		{
			if(contadorError < 2){
				printf("%s""%d al ""%d : ", mensajeError, min, max);
				fflush(stdin);
				scanf("%[^\n]",opcionIngresada);
			}
		}
		else
		{
			resultadoValidado = atoi(opcionIngresada);
			break;
		}

	}
	return resultadoValidado;
}
int ValidarEntero(char numero[])
{
	int resultado = 1;
	int i;

	if(strlen(numero) > 0)
	{
		for(i = 0; i < strlen(numero); i++)
		{
			if(isdigit(numero[i]) == 0)
			{
				resultado = 0;
				break;
			}
		}
	}
	else
	{
		resultado = 0;
	}

	return resultado;
}
int funcionMaxMin(char opcionIngresada[],int min, int max)
{
	int resultado;
	int aux;

	aux = atoi(opcionIngresada);
	resultado = 1;

	if(aux > max || aux < min)
	{
		resultado = 0;
	}
	return resultado;
}

int PedirString(char MSJ[], char ERRORMSJ[],char copiaParametro[], int max){
	char parametro[1000];
	int retorno = -1;
	int contador;

	contador = 0;

	printf("%s", MSJ);
	fflush(stdin);
	scanf("%[^\n]", parametro);

	while(contador < 3)
	{
		contador++;
		if(ValidarLetras(parametro) == 0 || strlen(parametro) > max || strlen(parametro) == 0)
		{
			if(contador < 3){
				printf("%s", ERRORMSJ);
				fflush(stdin);
				scanf("%[^\n]", parametro);
				retorno = -1;
			}
		}
		else
		{
			fflush(stdin);
			strcpy(copiaParametro, parametro);
			retorno = 1;
			break;
		}
	}

	return retorno;
}

int ValidarLetras(char cadena[])
{
	int i;
	int resultado;

	for(i=0; i<strlen(cadena); i++)
	{
		if(isalpha(cadena[i]) != 0)
		{
			resultado = 1;
		}
		else
		{
			resultado = 0;
			break;
		}
	}

	return resultado;
}

float ValidarFloat(char numero[])
{
	float resultado = 1;
	int i;
	int contadorDePuntos = 0;

	if(strlen(numero) > 0)
	{
		for(i = 0; i < strlen(numero); i++)
		{
			if(isdigit(numero[i]) == 0 && numero[i] != ',' && numero[i] != '.')
			{
				resultado = 0;
				break;
			}
			else{
				if(numero[i] == ',' || numero[i] == '.'){
					numero[i] = '.';
					contadorDePuntos++;
				}
			}
		}
		if (contadorDePuntos > 1){
			resultado = 0;
		}
	}
	else
	{
		resultado = 0;
	}

	return resultado;
}

float PedirFlotanteSinRango(char mensaje[], char mensajeError[])
{
    char validaNumeroIngresado[15];
    float auxNumeroValidado = -1;
    int intentos = 0;

    printf("%s", mensaje);
    fflush(stdin);
    scanf("%[^\n]", validaNumeroIngresado);

    while(intentos < 2){

    	intentos++;
		if(ValidarFloat(validaNumeroIngresado) == 0)
		{
			if(intentos<2){
				printf("%s", mensajeError);
				fflush(stdin);
				scanf("%[^\n]", validaNumeroIngresado);
			}
		}
		else{
			auxNumeroValidado = atof(validaNumeroIngresado);
			break;
		}

    }

	return auxNumeroValidado;
}
int ValidarEnteroSinRango(char opcionIngresada[],char mensajeError[])
{
	int resultadoValidado = -1;
	int contadorError;
	contadorError = 0;

	while(contadorError < 3)
	{
		contadorError++;
		if(ValidarEntero(opcionIngresada) == 0)
		{
			if(contadorError < 3){
				printf("%s", mensajeError);
				fflush(stdin);
				scanf("%[^\n]",opcionIngresada);
			}
		}
		else
		{
			resultadoValidado = atoi(opcionIngresada);
			break;
		}

	}
	return resultadoValidado;
}


