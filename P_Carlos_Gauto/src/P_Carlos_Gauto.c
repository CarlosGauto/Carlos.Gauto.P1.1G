#include "Validaciones.h"
#define TAM_A 10
#define TAM_AERO 5
#define TAM_TIPO 4

struct{
	int dia;
	int mes;
	int anio;
}typedef eFecha;

struct{
	int id;
	char descripcion[20];
}typedef eAerolinea;


struct{
	int id;
	char descripcion[20];
}typedef eTipo;

struct{
	int id;
	int idAerolinea;
	int idTipo;
	int capacidad;
	int isEmpty;
}typedef eAvion;

struct{
	int id;
	char descripcion[20];
	int precio;
}typedef eDestino;


struct{
	int id;
	int idAvion;
	int idDestino;
	eFecha fecha;
}typedef eVuelo;



int MenuDeOpciones(void);
int MenuModificacion(void);

int InicializarAvion(eAvion list[], int len);
int BuscarLibre(eAvion list[], int len);
eAvion CargarDatos(int* pid, eTipo listaTipo[],int tamTipo, eAerolinea listaAerolinea[], int tamAero);
void printAviones(eAvion listAvion[], int tamAvion, eAerolinea listAero[], int tamAero);
void printAerolinea(eAerolinea list[], int length);
void printAvionesConTipo(eAvion listAvion[], int tamAvion, eTipo listTipo[], int tamTipo);
void printTipo(eTipo list[], int length);
int EncontrarAvion(eAvion list[], int tamAvion, int id);
int CasosModificar(int opcion, eAvion list[], int tamAvion, int id, eTipo listaTipo[], int tamTipo);
void ListaAerolineas(eAerolinea list[], int tam);
void ListaTipo(eTipo list[], int tam);

int main(void) {
	setbuf(stdout,NULL);

	int idAvion = 1;
	int opcion;
	int opcionModificar;
	int r;
	int idEmpty;
	char auxChar[10];
	int idAux;
	int iEncontrada;
	int banderaPrimerAlta = 0;


	eAvion listAvion[TAM_A];
	eAerolinea listaAerolineas[TAM_AERO] = {{1000,"Lan"},{1001,"Iberia"},{1002,"Norwegian"},{1003,"American"},{1004,"Austral"}};
	eTipo listaTipos[TAM_TIPO] = {{5000,"Jet"},{5001,"Helice"},{5002,"Planeador"},{5003,"Carga"}};
	eDestino listaDestino[4] = {{20000,"Calafate",22250},{20001,"Miami",103000},{20002,"Madrid",84400},{20003,"Amsterdam",95600}};

	if(InicializarAvion(listAvion, TAM_A)){
		printf("BIENVENIDOS");
	}


	do{
		opcion = MenuDeOpciones();
		fflush(stdin);

		switch(opcion){

			case 1:
				printf("Alta\n");

				idEmpty = BuscarLibre(listAvion, TAM_A);

				if (idEmpty == -1){
					printf("No hay lugar vacio");
				}
				else{

					listAvion[idEmpty] = CargarDatos(&idAvion, listaTipos, TAM_TIPO, listaAerolineas, TAM_AERO);
					ProcesoCorrecto(listAvion[idEmpty].isEmpty, "No se pudo cargar","Se cargo el empleado");
					printAviones(listAvion, TAM_A,listaAerolineas, TAM_AERO);
					banderaPrimerAlta = 1;
				}

			break;

			case 2:
			if(banderaPrimerAlta){
				printf("Modificar avion\n");

				printAviones(listAvion, TAM_A,listaAerolineas, TAM_AERO);

				printf("\nIndique el id que desea modificar: ");
				fflush(stdin);
				scanf("%[^\n]",auxChar);
				idAux = ValidarEnteroSinRango(auxChar, "ERROR. Ingrese un id valido para Modificar: ");

				if(idAux == -1){
					printf("\nNo se realizo ninguna modificacion");
				}
				else{

					iEncontrada = EncontrarAvion(listAvion, TAM_A, idAux);
					if(iEncontrada == -1){
						printf("\nNo se encontro el AVION:");
					}
					else{
						opcionModificar = MenuModificacion();
						if(opcionModificar != 0){
							r = CasosModificar(opcionModificar, listAvion, TAM_A, iEncontrada, listaTipos, TAM_TIPO);
							ProcesoCorrecto(r, "Se realizo la Modificacion con Exito", "No se pudo realizar la Modificacion");
						}
					}
				}
			}else{
				printf("PRIMERO INGRESE UN ALTA");
			}
			break;
			if(banderaPrimerAlta){
				case 3:
						printf("Baja AVION\n");
						printAviones(listAvion, TAM_A,listaAerolineas, TAM_AERO);

						printf("\nIndique el id para la Baja: ");
						fflush(stdin);
						scanf("%[^\n]",auxChar);
						idAux = ValidarEnteroSinRango(auxChar, "ERROR. Ingrese un id valido para la Baja: ");

						if(idAux == -1){
							printf("\nERROR.REINTENTE LA BAJA");
						}
						else{
							iEncontrada = EncontrarAvion(listAvion, TAM_A, idAux);
							if(iEncontrada == -1){
								printf("\nNo se encontro el AVION");
							}
							else{
								printf("\nAvion encontrado, sera eliminado de la lista");
								listAvion[iEncontrada].isEmpty = 1;
							}
						}
			}else{
				printf("PRIMERO INGRESE UN ALTA");
			}
				break;

				case 5:
					ListaAerolineas(listaAerolineas, TAM_AERO);
				break;

				case 6:
					ListaTipo(listaTipos, TAM_TIPO);
				break;

				case 10:
					printf("PROGRAMA TERMINADO");
					break;

				default:
					printf("OPCION INGRESADA INCORRECTA");
				break;

		}

	}while(opcion != 10);


	return EXIT_SUCCESS;
}

int MenuDeOpciones(void)
{
	char opcion[5];
	int opcionValidada;
	printf("\n\n---MENU DE OPCIONES---\n");
	printf("\n1. ALTA AVION\n");
	printf("2. MODIFICAR AVION\n");
	printf("3. BAJA AVION\n");

	printf("5. LISTAR AEROLINEAS\n");
	printf("6. LISTAR TIPOS\n");
	printf("10. SALIR:\n");
	printf("Elija una opcion:\n");

	fflush(stdin);
	scanf("%[^\n]", opcion);

	opcionValidada = ValidarEnteroConMaxMin(opcion,"Error, ingrese una opcion correcta del ", 1, 10);

	return opcionValidada;
}
int MenuModificacion(void)
{
	char opcion[5];
	int opcionValidada;
	printf("\n\n---MENU DE MODIFICACION---\n");
	printf("\n1. TIPO\n");
	printf("2. CAPACIDAD\n");
	printf("Elija una opcion:\n");

	fflush(stdin);
	scanf("%[^\n]", opcion);

	opcionValidada = ValidarEnteroConMaxMin(opcion,"Error, ingrese una opcion correcta del ", 1, 5);

	return opcionValidada;
}

int InicializarAvion(eAvion list[], int len){
	int retorno = 0;

	if(list != NULL){
		for(int i = 0; i < len; i++){
			list[i].isEmpty = 1;
		}
		retorno = 1;
	}
	return retorno;
}
int BuscarLibre(eAvion list[], int len){
	int auxId = -1;

	if(list != NULL){
		for(int i = 0; i < len; i++){
			if(list[i].isEmpty == 1){
				auxId = i;
			}
		}

	}
	return auxId;
}
eAvion CargarDatos(int* pid, eTipo listaTipo[],int tamTipo, eAerolinea listaAerolinea[], int tamAero){

	eAvion auxAvion;
	char auxChar[15];

	printAerolinea(listaAerolinea,tamAero);

	printf("\nIngrese el id de la Aerolinea: ");
	fflush(stdin);
	scanf("%[^\n]", auxChar);

	auxAvion.idAerolinea = ValidarEnteroConMaxMin(auxChar, "ERROR. Ingrese un id Valido del ", 1000,1005);

	if(auxAvion.idAerolinea != 0 ){

		printTipo(listaTipo, tamTipo);
		printf("\nIngrese el id del TIPO: ");
		fflush(stdin);
		scanf("%[^\n]", auxChar);

		auxAvion.idTipo = ValidarEnteroConMaxMin(auxChar, "ERROR. Ingrese un id Valido del ", 5000,5004);

		if(auxAvion.idTipo != 0){

			printf("Ingrese la capacidad entre 10 y 300: ");
			fflush(stdin);
			scanf("%[^\n]", auxChar);
			auxAvion.capacidad = ValidarEnteroConMaxMin(auxChar, "ERROR. Ingrese una CAPACIDAD Valida de:", 10,300);

			if(auxAvion.capacidad != 0){

				auxAvion.id = *pid;
				(*pid)++;
				auxAvion.isEmpty = 0;

			}
			else
			{
				auxAvion.isEmpty = 1;
			}
		}
		else
		{
			auxAvion.isEmpty = 1;
		}
	}
	else
	{
		auxAvion.isEmpty = 1;
	}
	return auxAvion;
}

void printAerolinea(eAerolinea list[], int length)
{
	int i;
	printf("\nID   |DESCRIPCION\n");
	printf("-------------------------------------\n");
	for (i = 0; i < length; i++)
	{

		printf("%-5d|%-10s\n",list[i].id, list[i].descripcion);

	}

}
void printTipo(eTipo list[], int length)
{
	int i;
	printf("\nID   |DESCRIPCION\n");
	printf("-------------------------------------\n");
	for (i = 0; i < length; i++)
	{

		printf("%-5d|%-10s\n",list[i].id, list[i].descripcion);

	}

}
void printAviones(eAvion listAvion[], int tamAvion, eAerolinea listAero[], int tamAero){
	int i;
	printf("\nAvion| AEROLINEA |CAPACIDAD\n");
	printf("-------------------------------------\n");

	for (i = 0; i < tamAvion; i++)
	{
		for (int j = 0; j < tamAero; j++)
		{
			if(listAvion[i].isEmpty == 0 && listAvion[i].idAerolinea == listAero[j].id){

				printf("%-5d|%-10s|%-5d\n",listAvion[i].id, listAero[j].descripcion,listAvion[i].capacidad);
			}
		}
	}
}

int EncontrarAvion(eAvion list[], int tamAvion, int id)
{
	int retorno = -1;

	for(int i = 0; i < tamAvion; i++)
	{
		if(list[i].id == id && list[i].isEmpty == 0){
			retorno = i;
		}
	}

	return retorno;
}

int CasosModificar(int opcion, eAvion list[], int tamAvion, int id, eTipo listaTipo[], int tamTipo){

	char auxChar[10];
	int auxInt;
	int retorno;
	printAvionesConTipo(list, tamAvion, listaTipo, tamTipo);

	switch(opcion){

		case 1:

			printTipo(listaTipo, tamTipo);
			printf("\nIngrese el id del NUEVO TIPO: ");
			fflush(stdin);
			scanf("%[^\n]", auxChar);
			auxInt = ValidarEnteroConMaxMin(auxChar, "ERROR. Ingrese un id Valido del ", 5000,5004);
			if(auxInt != 0)
			{
				list[id].idTipo = auxInt;
				printAvionesConTipo(list, tamAvion, listaTipo, tamTipo);
				retorno = 1;
			}
			else
			{
				retorno = 0;
			}

		break;

		case 2:

			printf("\nIngrese la nueva capacidad de 10 a 300: ");
			fflush(stdin);
			scanf("%[^\n]", auxChar);
			auxInt = ValidarEnteroConMaxMin(auxChar, "ERROR. Ingrese una capacidad validad de ", 10,300);

			if(auxInt != 0)
			{
				list[id].capacidad = auxInt;
				printAvionesConTipo(list, tamAvion, listaTipo, tamTipo);
				retorno = 1;
			}
			else
			{
				retorno = 0;
			}

			break;

	}



	return retorno;
}

void printAvionesConTipo(eAvion listAvion[], int tamAvion, eTipo listTipo[], int tamTipo){
	int i;
	printf("\nLISTA DE AVIONES CON SU TIPO Y CAPACIDAD");
	printf("\nAvion| TIPO |CAPACIDAD\n");
	printf("--------------------------------\n");

	for (i = 0; i < tamAvion; i++)
	{
		for (int j = 0; j < tamTipo; j++)
		{
			if(listAvion[i].isEmpty == 0 && listAvion[i].idTipo == listTipo[j].id){

				printf("%-5d|%-10s|%-5d\n",listAvion[i].id, listTipo[j].descripcion,listAvion[i].capacidad);
			}
		}
	}
}
void ListaAerolineas(eAerolinea list[], int tam){
	int i;
	printf("\nLISTA DE Aerolinea");
	printf("\nID |Aerolinea\n");
	printf("--------------------------------\n");
	for (i = 0; i < tam; i++)
	{
		printf("%-5d|%-10s\n",list[i].id, list[i].descripcion);
	}

}
void ListaTipo(eTipo list[], int tam){
	int i;
	printf("\nLISTA DE Tipo");
	printf("\nID |Tipo\n");
	printf("--------------------------------\n");
	for (i = 0; i < tam; i++)
	{
		printf("%-5d|%-10s\n",list[i].id, list[i].descripcion);
	}

}

