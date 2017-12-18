#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

void Default(char& suma, char& resta, char& producto, char& division, char& factorial, char& potencia, char& raiz){
	suma = '+';
	resta = '-';
	producto = '*';
	division = '/';
	factorial = '!';
	potencia = '^';
	raiz = 'r';
}

void Operadores(char& suma, char& resta, char& producto, char& division, char& factorial, char& potencia, char& raiz, bool& error){
	char c[6];
	ifstream filein;
	filein.open("configuracion.txt");
	if (filein.is_open() == false){ error = true; Default(suma, resta, producto, division, factorial, potencia, raiz);}
	else{error = false;
		for (int i=0; i<=6; i++){
			filein >> c[i];
		}filein.close();
		suma = c[0];
		resta = c[1];
		producto = c[2];
		division = c[3];
		factorial = c[4];
		potencia = c[5];
		raiz = c[6];
	}filein.close();
}

void opConfigDef(){
	char a, b, c, d, e, f, g, opcion;
	ofstream fileout;
	ifstream fileB_in;
	fileout.open("Default.txt");
	Default(a, b, c, d, e, f, g);
	fileout << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g;
	fileout.close();
	fileB_in.open("configuracion.txt");
	if (fileB_in.is_open() == true){cout << "Desea usar la configuracion de la ultima sesion?(s/n): ";
	cin >> opcion;
	//if (opcion == 's');
	if (opcion == 's'){fileB_in.close();}
	else if (opcion == 'n') {/*remove("configuracion.txt") ; */fileB_in.close(); remove("configuracion.txt");}}
	//fileout.open("configuracion.txt");
	//fileout.close();
	else cout << "";
}


void mostrarMenu(void){
	cout << "\t\t\tCALCULADORA\n";
	cout << "\n\t1.-Calculadora\n";
	cout << "\t2.-Configuracion\n";
	cout << "\n\tOpcion ? [ ]\b\b";
}


void leerOperando(char a, bool &error, bool &final, double &b){
	if (a == 'x') final = true;
	else{ b = a/2;
		if (!cin.fail()) b = a;
	}

}

void leerOperador(char a, bool& operador, bool& error){//devuelve true si el operador es binario, false si es unario y error si no existe
	bool ndefecto = false;
	error = false;
	char suma, resta, multiplicacion, division, factorial, potencia, raiz;
	Operadores (suma, resta, multiplicacion, division, factorial, potencia, raiz, ndefecto);//estas dos lineas se<--
	//if (ndefecto == true) Default(suma, resta, multiplicacion, division, factorial, potencia, raiz);//pueden sacar a una funcion<--
	if (a == suma || a == resta || a == multiplicacion || a == division || a == potencia)operador = true;//ya que creo que se repite
	else if (a == factorial || a == raiz) operador = false;
	else error = true;
}

double fact(double a, bool& error){
	error = false;
	if ((a - floor(a) != 0) || a < 0) error = true;
	else if (a == 0) return 1;
	else return a * fact(a-1, error);
}

double potencia(double base, double exponente, bool& error){
	error = false;
	if (exponente - floor(exponente) != 0) error = true;
	else if (exponente >= 0){
		if ((exponente == 0) && (base == 0)) error = true;
		else if (exponente == 0) return 1;
		else return base * potencia(base, exponente-1, error);
	}else if (exponente < 0){
		if (exponente == -1) return (1/base);
		else return (1/base) * potencia(base, (exponente+1), error);
	}
}

double division(double numerador, double denominador, bool& error){
	error = false;
	if (denominador == 0) error = true;
	else return numerador / denominador;
}

double suma(double a, double b, bool&error){
	return a + b;
}

double resta (double a, double b, bool&error){
	return a - b;
}

double producto (double a, double b, bool&error){
	return a * b;
}

double raiz( double a, bool& error){
	error = false;
	if (a < 0) error = true;
	else return sqrt(a);
}

void operacion(double a, char b, double c, bool& error, double& d){
	bool x = false, ndefecto = false; char opSuma, opRest, opProd, opDivi, opFact, opPote, opRaiz;
	Operadores (opSuma, opRest, opProd, opDivi, opFact, opPote, opRaiz, ndefecto);
	//if (ndefecto == true) Default(opSuma, opRest, opProd, opDivi, opFact, opPote, opRaiz);
	if ( b == opSuma)	 { d = suma(a, c, x);		 error = x;}
	else if (b == opRest){ d = resta (a, c, x);		 error = x;}
	else if (b == opProd){ d = producto (a, c, x);	 error = x;}
	else if (b == opDivi){ d = division (a, c, x);	 error = x;}
	else if (b == opFact){ d = fact (a, x);			 error = x;}
	else if (b == opPote){ d = potencia(a, c, x);	 error = x;}
	else if (b == opRaiz){ d = raiz(a, x);			 error = x;}
	else error = true;
}
void config(){
	bool x = false;
	char a, b, suma, resta, multiplicacion, division, factorial, potencia, raiz;
	ofstream fileout;
	ifstream filein;
	cout << "Desea utilizar la configuracion por defecto?(s/n): ";
	cin >> b;
	if (b == 's'){
		filein.open("configuracion.txt");
		if (filein.is_open()){ filein.close(); remove("configuracion.txt");}
	}
	else if (b == 'n'){
		Operadores(suma, resta, multiplicacion, division, factorial, potencia, raiz, x);
		fileout.open("configuracion.txt");
		cout << "Suma(" << suma << "): "; cin >> a; fileout << a << " ";
		cout << "Resta("<< resta <<"): "; cin >> a; fileout << a << " ";
		cout << "Producto("<< multiplicacion <<"): "; cin >> a; fileout << a << " ";
		cout << "Division("<< division << "): "; cin >> a; fileout << a << " ";
		cout << "Factorial("<< factorial << "): "; cin >> a; fileout << a << " ";
		cout << "Potencia("<< potencia << "): "; cin >> a; fileout << a << " ";
		cout << "Raiz("<< raiz <<"): "; cin >> a; fileout << a << " ";
		fileout.close();
	}else cout << "Esa opcion no te la he dado a elegir.\n";
}

void calc(){
	bool fin = false, matherror = false, syntaxerror = false, error=false, binario = false, endstream = false;
	char c, d, a;
	double op1 = 0, op2 = 0;
	while (!fin){
		cin >> op1;
		cin.get(c);
		while (c != '\n'){
			leerOperador(c, binario, error);
			if (binario == true){
				cin >> op2;
				operacion(op1, c, op2, error, op1);
			}else operacion(op1, c, 0, error, op1);
			cin.get(c);
		}if (error) cout << "Error\n";
		else cout << op1 << endl;
		error = false;
		cin.sync();
	}
}

void frac(){

}


int main(){
	int opcion;
	char a;
	bool salir = false;
	opConfigDef();
	do{
		mostrarMenu();
		cin >> opcion;
		cin.ignore(1, '\n');
		cin.fail();
		if (cin.fail()) cout << "Opcion no valida.\n";
		else if (opcion == 1) calc();
		else if (opcion == 2) config();
		else if (opcion == 5) salir = true;
		cin.clear();
		cin.sync();
	}while (!salir);
}