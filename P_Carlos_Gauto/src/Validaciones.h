#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int ValidarEnteroConMaxMin(char opcionIngresada[],char mensajeError[], int min, int max);
int ValidarEntero(char numero[]);
int funcionMaxMin(char opcionIngresada[],int min, int max);
int PedirString(char MSJ[], char ERRORMSJ[],char copiaParametro[], int max);
int ValidarLetras(char cadena[]);
float ValidarFloat(char numero[]);
float PedirFlotanteSinRango(char mensaje[], char mensajeError[]);
int ValidarEnteroSinRango(char opcionIngresada[],char mensajeError[]);
void ProcesoCorrecto(int retorno, char mensajeCorrecto[], char mensajeError[]);

#endif /* VALIDACIONES_H_ */
