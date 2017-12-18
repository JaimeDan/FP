#include "funciones.h"

void limpiar(){
	cin.sync();
	cin.clear();
}


void getChars(tCadena& cadena){
	bool error = true;
	while (error){
		cin.getline(cadena, SIZE_CADENA);
		if (cin.fail() ||strlen(cadena) == 0){
			if (cin.fail()){
				cout << "Se ha superado el maximo permitido.\n";
				cin.ignore();
			}if (strlen(cadena) == 0) cout << "Se ha insertado una cadena vacia.\n";
			limpiar();
		}else error= false;
	}limpiar();
}


void leerNif(tCadena& nif){
	//stringstream ss;
	//int dni_n;
	//char letra;
	bool OK = false;
	while (!OK){
		limpiar();
		cin.getline(nif, 10);
		if (cin.fail()) cin.ignore();
		limpiar();
		//ss << dni_n;
		//dni = ss.str();
		OK = dniOK(nif);
		if (!OK) cout << ERROR;
	}
	//letra = letraDNI(dni_n);
	//dni = dni + letra;
	limpiar();
	nif[8] = toupper(nif[8]);
	
}

int getInt(){
	int entero;
	bool error = true;
	while (error){
		cin >> entero;
		if (cin.fail()){
			cout << ERROR;
			limpiar();
		}else error = false;
	}limpiar();
	return entero;
}

double getDouble(){
	double numero;
	bool error = true;
	while (error){
		cin >> numero;
		if (cin.fail()){
			cout << ERROR;
			limpiar();
		}else error = false;
	}limpiar();
	return numero;
}

char getChar(){
	char caracter;
	bool error = true;
	while (error){
		cin >> caracter;
		if (cin.fail()){
			cout << ERROR;
			limpiar();
		}else error = false;
	}limpiar();
	return caracter;
}

void EnterParaContinuar(){
	char c;
	limpiar();
	cout << "\n\nPulse Enter para continuar\n";
	cin.get(c);
}

bool getYesOrNo(){
	cin.sync();
	char caracter;
	bool gusto;
	bool error = true, fallo = false;
	while (error){
		cin.get(caracter);
		//cin.ignore();
		caracter = toupper(caracter);
		limpiar();
		error = false;
		if (caracter == 'S' ) gusto = true;
		else if (caracter == 'N') gusto = false;
		else{
			error = true;
			cout << ERROR;
		}
	}limpiar();
	return gusto;
}

bool dniOK(const tCadena dni) {
	bool ok = true;
	if (strlen(dni) != 9)
		ok = false;
	else if (!isalpha(dni[8])) ok = false;
	else {
		unsigned int i= 0;
		//ok = (dni[i] >= '0') && (dni[i] <= '9');
		while (i+1<strlen(dni)-1 && ok){
			i++;
			ok = (dni[i] >= '0') && (dni[i] <= '9');
		}
	}

   return ok;
}

char letraDNI(int dni){
	int suma = 0;
	char letra;
	char c[24] = "TRWAGMYFPDXBNJZSQVHLCKE";
	suma = dni % 23;
	letra = c[suma];
	return letra;	
}

