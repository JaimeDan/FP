#include "cliente.h"


tCliente leerCliente(){
	tCliente cliente;
	string nif, apellidos;
	do{
		cout << "Introduzca el NIF del cliente: ";
		limpiar();
		cliente.nif = leeNif();		
	}while (cin.fail());
	do{
		cout << "Introduzca el nombre del cliente: ";
		limpiar();
		cin >> cliente.nombre;
	}while (cin.fail());
	do{
		cout << "Introduzca los apellidos del cliente: ";
		limpiar();
		getline(cin, apellidos);
	}while (cin.fail());
	do{
		cout << "Introduzca el genero favorito del cliente: ";
		limpiar();
		cliente.genero = leerGenero();
	}while (cin.fail());
	cliente.pelis.cont = 0;
	return cliente;
}

string leeNif() {
	string dni;
	stringstream ss;
	int dni_n;
	char letra;
	bool OK = false;
	//do {
	while (!OK){
		cout << "D.N.I. (8 digitos): ";
		limpiar();
		cin >> dni_n;
		ss << dni_n;
		dni = ss.str();
		OK = dniOK(dni);
	}
	//} while (!dniOK(dni));
	/*do {
		cout << "Letra: ";
		cin.sync();
		cin >> letra;
		letra = toupper(letra);
	} while ((letra < 'A') || (letra > 'Z'));
	*/
	letra = letraDNI(dni_n);
	dni = dni + letra;
	return dni;
}

bool dniOK(string dni) {
   bool ok = true;
   if (dni.size() != 8)
      ok = false;
   else
      for (int i = 0; i < dni.size(); i++)
         if ((dni.at(i) < '0') || (dni.at(i) > '9'))
            ok = false;
   return ok;
}

char letraDNI(int dni){
	int suma = 0, digito;
	char letra;
	char c[24] = "TRWAGMYFPDXBNJZSQVHLCKE";
	/*while (dni >= 0){
		digito = dni%10;
		dni = (dni - digito)/10;
		suma += digito;
	}suma = suma%23;*/
	suma = dni % 23;
	letra = c[suma];
	return letra;	
}