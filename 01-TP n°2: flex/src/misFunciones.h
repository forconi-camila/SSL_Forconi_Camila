/* Libreria de funciones para el programa */

#include <string.h>
#include <math.h>



struct NodoId
{
	char identificador[15];
	int vecesMencionado;
	struct NodoId *sig;
};

struct NodoLitCad 
{
	char string[15];
	int longitud;
	NodoLitCad* sig;
};

struct NodoPalRes 
{
	char palabra[15];
	NodoPalRes* sig;
};

struct NodoOctal
{
	char valorOctal[10];
	int valorDecimal;
	NodoOctal* sig;
};

struct NodoHexadecimal
{
	char valorHex[10];
	int valorDecimal;
	NodoHexadecimal* sig;
};

struct NodoDecimal
{
	int valor;
	NodoDecimal* sig;
};

struct NodoReal
{
	int mantisa;
	int parteEntera;
	NodoReal* sig;
};

struct NodoCaracter
{
	char caracter;
	NodoCaracter* sig;
};

struct NodoPuntOp
{
	char caracter;
	int cantidad;
	NodoPuntOp* sig;
}; 

struct NodoComent
{
	char comentario[50];
	bool deUnaLinea;
	NodoComent* sig;
};

struct NodoNoRec
{
	char noReconocido;
	int linea;
	NodoNoRec* sig;
};



// ---------------------------------------- LISTAS Y VARIABLES GLOBALES ----------------------------------

NodoId *listaIdentif = NULL;
NodoLitCad *listaLitCad = NULL;
NodoPalRes *listaPalRes = NULL;
NodoOctal *listaOctal = NULL;
NodoHexadecimal *listaHexadecimal = NULL;
NodoDecimal *listaDecimal = NULL;
NodoReal *listaReal = NULL;
NodoCaracter *listaCaracter = NULL;
NodoPuntOp *listaPuntOp = NULL;
NodoComent *listaComent = NULL;
NodoNoRec *listaNoRec = NULL;


// ---------------------------------------- FUNCIONES ----------------------------------------------------

void buscarInsertarIdentificador(char identif[15]){
	/*	
		Busca el identificador en la lista de identificadores y si no existe lo inserta en la lista.
		Si existe, incrementa en uno la cantidad de veces que se ha mencionado.
		Parametros:
			identif: identificador a buscar e insertar.
	*/

	NodoId *p, *ant;
	p = listaIdentif;

	while(p != NULL && strcmp(identif, p->identificador) < 0){
		ant = p;
		p = p->sig;
	}

	if(p != NULL && strcmp(identif, p->identificador) == 0)
        p->vecesMencionado++;
    else
    {
        NodoId* n = new NodoId;

        strcpy(n->identificador, identif);
		n->vecesMencionado = 1;
		n->sig = p;

        if(p != listaIdentif)
			ant->sig = n;
		else
			listaIdentif = n;
    }

	/* 
		la funcion strcmp(cadena1,cadena2) de la libreria string.h compara dos cadenas caracter por caracter.
			devuelve 0: si los strings son iguales
			devuelve un numero negativo: si la primera cadena es menor que la segunda cadena
			devuelve un numero positivo: si la primera cadena es mayor que la segunda cadena

		la funcion strcpy(destino,origen) de la libreria string.h copia una cadena a otro.
			Parametros:
				destino: cadena donde se copia la cadena de origen.
				origen: cadena que se copia.
	*/
}



void insertarLiteralCadena(char cadena[15], int longitud)
{
	/*
		Inserta una cadena en la lista de literales cadenas segun su longitud.
		Parametros:
			cadena: cadena a insertar
			longitud: longitud de la cadena
	*/

	NodoLitCad *p, *ant;
	p = listaLitCad;

	while(p != NULL && p->longitud < longitud)
	{
		ant = p;
        p = p->sig;
	}
	
	NodoLitCad *n = new NodoLitCad;

    strcpy(n->string, cadena);
	n->longitud = longitud;
	n->sig = p;

	if(p != listaLitCad)
		ant->sig = n;
	else
		listaLitCad = n;
}



void insertarPalReservada(char palabra[15]) {
	/*
		Inserta una palabra reservada en la lista de palabras reservadas en el orden en que aparece en el archivo.
		Parametros:
			palabra: palabra a insertar
	*/

	NodoPalRes *p, *ant;
	p = listaPalRes;
	
	while(p != NULL)
	{
		ant = p;
		p = p->sig;
	}
	
	NodoPalRes* n = new NodoPalRes;
	
	strcpy(n->palabra, palabra);
	n->sig = p;
		
	if(p != listaPalRes)
		ant->sig = n;
	else
		listaPalRes = n;
}



void buscarInsertarPuntuacionOperador(char caracter)
{
	/*
		Busca el caracter en la lista de puntuaciones de operadores y si no existe lo inserta en la lista.
		Si existe, incrementa en uno la cantidad de veces que se ha mencionado.
		Parametros:
			caracter: caracter a buscar e insertar.
	*/

	NodoPuntOp *p, *ant;
	p = listaPuntOp;
	
	while(p != NULL && caracter < p->caracter)
	{
		ant = p;
		p = p->sig;
	}
	
	if(p!=NULL && caracter == p->caracter)
		p->cantidad++;
	else
	{
		NodoPuntOp* n = new NodoPuntOp;
		n->caracter = caracter;
		n->cantidad = 1;
		n->sig = p;
		
		if(p != listaPuntOp)
			ant->sig = n;
		else
			listaPuntOp = n;
	}
}


void insertarComentario(char comentario[50], bool tipoDeComentario)
{
	/*
		Inserta un comentario en la lista de comentarios en el orden en que aparece en el archivo.
		Parametros:
			comentario: comentario a insertar
			tipoDeComentario: true si es un comentario de una linea, false si multilinea
	*/

	NodoComent *p, *ant;
	p = listaComent;
	
	while(p != NULL)
	{
		ant = p;
		p = p->sig;
	}
	
	NodoComent* n = new NodoComent;
	
	strcpy(n->comentario, comentario);
	n->deUnaLinea = tipoDeComentario;
	n->sig = p;
		
	if(p != listaComent)
		ant->sig = n;
	else
		listaComent = n;
}


void insertarNoReconocido(char caracter, int linea)
{
	/*
		Inserta un caracter no reconocido en la lista de caracteres no reconocidos en el orden en que aparece en el archivo.
		Parametros:
			caracter: caracter a insertar
			linea: numero de linea en la que se encuentra el caracter
	*/

	NodoNoRec *p, *ant;
	p = listaNoRec;
	
	while(p != NULL)
	{
		ant = p;
		p = p->sig;
	}
	
	NodoNoRec* n = new NodoNoRec;
	
	n->noReconocido = caracter;
	n->linea = linea;
	n->sig = p;
		
	if(p != listaNoRec)
		ant->sig = n;
	else
		listaNoRec = n;
}


// ---------------------------------------- CONSTANTES ENTERAS, REALES Y CARACTER ----------------------------------------
void insertarConstOctal(char valorOct[10])
{
	/*
		Inserta una constante octal en la lista de constantes octales en el orden en que aparece en el archivo.
		Parametros:
			valor: valor de la constante octal
	*/

	NodoOctal *p, *ant;
	p = listaOctal;
	
	while(p != NULL)
	{
		ant = p;
		p = p->sig;
	}

	NodoOctal *n = new NodoOctal;
	
	strcpy(n->valorOctal, valorOct);
	n->valorDecimal = hexADec(valorOct);
	n->sig = p;
		
	if(p != listaOctal)
		ant->sig = n;
	else
		listaOctal = n;
}

int octADec(char oct[])
{
	/*
		Convierte un constante entera octal a una decimal.
		Parametros:
			oct: valor octal a convertir
	*/

	int dec = 0;
	int i = 0;

	while (oct[i] != '\0')
	{
		if (oct[i] >= '0' && oct[i] <= '7')
			dec = dec * 8 + (oct[i] - '0');
		i++;
	}

	return dec;
}



void insertarConstHexadecimal(char valorHex[10])
{
	/*
		Inserta una constante hexadecimal en la lista de constantes hexadecimales en el orden en que aparece en el archivo.
		Parametros:
			valorHex: valor de la constante hexadecimal
	*/

	NodoHexadecimal *p, *ant;
	p = listaHexadecimal;
	
	while(p != NULL)
	{
		ant = p;
		p = p->sig;
	}

	NodoHexadecimal *n = new NodoHexadecimal;
	
	strcpy(n->valorHex, valorHex);
	n->valorDecimal = hexADec(valorHex);
	n->sig = p;
		
	if(p != listaHexadecimal)
		ant->sig = n;
	else
		listaHexadecimal = n;
}

int hexADec(char hex[])
{
	/*
		Convierte un constante entera hexadecimal a una decimal.
		Parametros:
			hex: valor hexadecimal a convertir
	*/

	int dec = 0;
	int i = 0;

	while (hex[i] != '\0')
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			dec = dec * 16 + (hex[i] - '0');
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			dec = dec * 16 + (hex[i] - 'A' + 10);
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			dec = dec * 16 + (hex[i] - 'a' + 10);
		
		i++;
	}

	return dec;
}



void insertarConstDecimal(int valorDec)
{
	/*
		Inserta una constante decimal en la lista de constantes decimales en el orden en que aparece en el archivo.
		Parametros:
			valorDec: valor de la constante decimal
	*/

	NodoDecimal *p, *ant;
	p = listaDecimal;
	
	while(p != NULL)
	{
		ant = p;
		p = p->sig;
	}

	NodoDecimal *n = new NodoDecimal;
	
	n->valor = valorDec;
	n->sig = p;
		
	if(p != listaDecimal)
		ant->sig = n;
	else
		listaDecimal = n;
}

int sumaTotalDecimales(){
	/*
		Suma el total de los valores de los decimales de la lista de constantes decimales.
	*/
	
	int sumaDecimales = 0;
	NodoDecimal *p = listaDecimal;
	
	while(p != NULL)
	{
		sumaDecimales += p->valor;
		p = p->sig;
	}

	return sumaDecimales;
}



void insertarConstReal(float valorReal)
{
	/*
		Inserta una constante real en la lista de constantes reales en el orden en que aparece en el archivo.
		Parametros:
			valorReal: valor de la constante real
	*/
	
	float mantisa, parteEntera;
  	mantisa = modf(numero, &parteEntera); 
	/* 
		la funcion modf() de la biblioteca math.h devuelve la parte decimal de un numero real
		y pone la parte entera en la variable cuya dirección mandamos con el operador de acceso
 	*/

	NodoReal *p, *ant;
	p = listaReal;
	
	while(p != NULL)
	{
		ant = p;
		p = p->sig;
	}

	NodoReal *n = new NodoReal;
	
	n->parteEntera = parteEntera;
	n->mantisa = mantisa;
	n->sig = p;
		
	if(p != listaReal)
		ant->sig = n;
	else
		listaReal = n;
}

float fractionalToDecimal(char fractional[])
{
	/*
		Convierte un numero real fraccionario a decimal.
		Parametros:
			fractional: valor real fraccionario a convertir
	*/

	float decimal = 0;
	
}



void insertarConstCaracter(int valorCaracter)
{
	/*
		Inserta una constante caracter en la lista de constantes caracteres en el orden en que aparece en el archivo.
		Parametros:
			valorCaracter: valor de la constante caracter
	*/

	char caracterChar = valorCaracter + '0';

	NodoCaracter *p, *ant;
	p = listaCaracter;
	
	while(p != NULL)
	{
		ant = p;
		p = p->sig;
	}

	NodoCaracter* n = new NodoCaracter;

	n->caracter = caracterChar;
	n->sig = p;

	if(p != listaCaracter)
		ant->sig = n;
	else
		listaCaracter = n;
}