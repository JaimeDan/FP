#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

typedef struct {
	char suma;
	char resta;
	char producto;
	char division;
	char factorial;
	char potencia;
	char raiz;
	char simplificar;
	char salir;
	char borrar;
	char guardarMem;
	char cargarMem;
} ConfigTeclas;

int MCM(int n1, int n2){
    // Buscar los factores primos que dividen a n1 o a n2
    int resultado = 1; // El 1 siempre es un Cm
    int factor = 2;    // Empezamos en 2

    while((factor <= n1) || (factor <= n2)) {
        while((n1 % factor == 0) || (n2 % factor == 0)) {
            resultado *= factor;
            if (n1 % factor == 0) n1 /= factor;
            if (n2 % factor == 0) n2 /= factor;
        }
        if(factor == 2) factor++;  // Si factor es 2, el siguiente primo es 3
        else factor+=2;            // Si no, elegimos el siguiente número impar
    }
    return resultado;
}
int MCD(int n1, int n2) {
    // Buscar los factores primos que dividen tanto a n1 como a n2
    int resultado = 1; // El 1 siempre es un CD
    int factor = 2;    // Empezamos en 2

    while(factor <= n1 || factor <= n2) {
        while(!(n1 % factor) && !(n2 % factor)) {
            resultado *= factor;
            n1 /= factor;
            n2 /= factor;
        }
        if(factor == 2) factor++;  // Si factor es 2, el siguiente primo es 3
        else factor+=2;            // Si no, elegimos el siguiente número impar
    }
    return resultado;
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
void sumarFracciones(int num2, int denom2, int& num1, int& denom1){

	num1 = num1 * (denom2 / MCD (denom1, denom2)) + num2 * (denom1 / MCD (denom1, denom2));
	denom1 = MCM(denom1, denom2);
}
void restarFracciones(int num2, int denom2, int& num1, int& denom1){

	num1 = num1 * (denom2 / MCD (denom1, denom2)) - num2 * (denom1 / MCD (denom1, denom2));
	denom1 = MCM(denom1, denom2);
}
void multiplicarFracciones(int num2, int denom2, int& num1, int& denom1){

	num1 = num1 * num2 ;
	denom1 = denom1 * denom2;
}
void dividirFracciones(int num2, int denom2, int& num1, int& denom1, bool& error){
	if (num2 == 0) error = true;
	else{
		num1 = num1 * denom2 ;
		denom1 = denom1 * num2;
	}
}
void simplificarFracciones( int& num1, int& denom1){
	int aux=num1;
	num1 = num1 / MCD (num1, denom1);
	denom1 = denom1 / MCD (aux, denom1);
}

void potenciaFracciones(int num2, int& num1, int& denom1, bool& error, bool natural){
	if (natural == false) error = true;
	else{
		num1 = potencia (num1, num2, error) ;
		denom1 = potencia (denom1, num2, error);
	}
}
void leerFraccion (int& num, int& denom, bool& error, bool& natural){
	char c;
	cin >> num;
	c = cin.peek();
	if (c == '|'){ cin >> c; cin >> denom;}
	else{ denom = 1; natural = true;}
	error = cin.fail() || (denom == 0);
	if(error){ num=0; denom=1; cin.clear();cin.sync();}
}
void Default(ConfigTeclas& teclas){
	teclas.suma = '+';
	teclas.resta = '-';
	teclas.producto = '*';
	teclas.division = '/';
	teclas.factorial = '!';
	teclas.potencia = '^';
	teclas.raiz = 'r';
	teclas.simplificar = 's';
	teclas.salir = 'x';
	teclas.borrar = 'c';
	teclas.guardarMem = 'm';
	teclas.cargarMem = 'n';
}

void Operadores(ConfigTeclas& teclas){
	char c[11];
	ifstream filein;
	filein.open("configuracion.txt");
	if (filein.is_open() == false) Default (teclas);
	else{
		for (int i=0; i<=11; i++){
			filein >> c[i];
		}filein.close();
		teclas.suma = c[0];
		teclas.resta = c[1];
		teclas.producto = c[2];
		teclas.division = c[3];
		teclas.factorial = c[4];
		teclas.potencia = c[5];
		teclas.raiz = c[6];
		teclas.simplificar = c[7];
		teclas.salir = c[8];
		teclas.borrar = c[9];
		teclas.guardarMem = c[10];
		teclas.cargarMem = c[11];
	}filein.close();
}

void opConfigDef(){
	char opcion;
	ConfigTeclas teclas;
	ofstream fileout;
	ifstream fileB_in;
	fileout.open("Default.txt");
	Default(teclas);
	fileout << teclas.suma/* << "\n" */<< teclas.resta /* "\n" <<*/<< teclas.producto/* << "\n" */<< teclas.division/* << "\n" */<< teclas.factorial/* << "\n" */<< teclas.potencia/* << "\n" */<< teclas.raiz << teclas.simplificar/* << "\n"*/<<teclas.salir << teclas.borrar << teclas.guardarMem << teclas.cargarMem;
	fileout.close();
	fileB_in.open("configuracion.txt");
	if (fileB_in.is_open() == true){cout << "Desea usar la configuracion de la ultima sesion?(s/n): ";
	cin >> opcion;
	//if (opcion == 's');
	if (opcion == 's'){fileB_in.close();}
	else if (opcion == 'n') {/*remove("configuracion.txt") ; */fileB_in.close(); remove("configuracion.txt");}}
	//fileout.open("configuracion.txt");
	//fileout.close();
}


void mostrarMenu(){
	cout << "\t\t\tCALCULADORA\n";
	cout << "\n\t1.-Calculadora\n";
	cout << "\t2.-Configuracion\n";
	cout << "\t3.-Modo fracciones\n";
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
	ConfigTeclas teclas;
	error = false;
	//char suma, resta, multiplicacion, division, factorial, potencia, raiz, simplificar, dontCare;
	Operadores (teclas);//estas dos lineas se<--
	if (a == teclas.suma || a == teclas.resta || a == teclas.producto || a == teclas.division || a == teclas.potencia)operador = true;//ya que creo que se repite
	else if (a == teclas.factorial || a == teclas.raiz || a == teclas.simplificar) operador = false;
	else if (a == '\n') error = false;
	else error = true;
}

void operacion(double a, char b, double c, bool& error, double& d){
	ConfigTeclas teclas;
	bool x = false, ndefecto = false; char opSuma, opRest, opProd, opDivi, opFact, opPote, opRaiz, opSimpli, dontCare;
	Operadores (teclas);
	if ( b == teclas.suma)			{ d = suma(a, c, x);		 error = x;}
	else if (b == teclas.resta)		{ d = resta (a, c, x);		 error = x;}
	else if (b == teclas.producto)	{ d = producto (a, c, x);	 error = x;}
	else if (b == teclas.division)	{ d = division (a, c, x);	 error = x;}
	else if (b == teclas.factorial)	{ d = fact (a, x);			 error = x;}
	else if (b == teclas.potencia)	{ d = potencia(a, c, x);	 error = x;}
	else if (b == teclas.raiz)		{ d = raiz(a, x);			 error = x;}
	else error = true;
}
void operacionFracciones(int num2, int denom2, int& num1, int& denom1 , char operador, bool& error,  bool natural){
	bool x = false, ndefecto = false; //char opSuma, opRest, opProd, opDivi, opFact, opPote, opRaiz, opSimpli, dontCare;
	ConfigTeclas teclas;
	Operadores (teclas);
	if ( operador == teclas.suma) sumarFracciones(num2, denom2, num1, denom1);
	else if (operador == teclas.resta) restarFracciones(num2, denom2, num1, denom1);
	else if (operador == teclas.producto) multiplicarFracciones(num2, denom2, num1, denom1);
	else if (operador == teclas.division) dividirFracciones(num2, denom2, num1, denom1, error);
	else if (operador == teclas.simplificar) simplificarFracciones(num1, denom1);
	else if (operador == teclas.potencia) potenciaFracciones(num2, num1, denom1, error, natural);
	else error = true;
}

void compruebaTeclas(char& teclaAux, bool& teclasRepetidas, int& contadorTeclas){
	char teclasAnteriores[11];
	int i = 0;
	if (contadorTeclas == 0){
		teclasAnteriores[0] = teclaAux;
		if ((teclaAux == 'e')||(isdigit(teclaAux) == true)) teclasRepetidas = true;
		else contadorTeclas++;
	}else{
		if ((isdigit(teclaAux) == true)||(teclaAux) == 'e') teclasRepetidas = true;
		else if (teclasRepetidas == false){
			while((i<contadorTeclas)&&teclasRepetidas == false){
				teclasRepetidas = (teclaAux == teclasAnteriores[i]);
				teclasAnteriores[contadorTeclas] = teclaAux;
				i++;
			}i = 0;
		}
	}if (teclasRepetidas == false) contadorTeclas++;
	else cout << "\nEsa tecla ya esta asignada a otra variable.\n";
}

void configuraTeclas(ConfigTeclas& teclas){
	ofstream fileout;
	bool teclasRepetidas = false;
	char teclaAux, guardaTeclas[12];
	string nombreOperacion[12];
	int contadorTec = 0;
	Operadores(teclas);
	guardaTeclas[0] = teclas.suma;			nombreOperacion[0] = "Suma";
	guardaTeclas[1] = teclas.resta;			nombreOperacion[1] = "Resta";
	guardaTeclas[2] = teclas.producto;		nombreOperacion[2] = "Producto";
	guardaTeclas[3] = teclas.division;		nombreOperacion[3] = "Division";
	guardaTeclas[4] = teclas.factorial;		nombreOperacion[4] = "Factorial";
	guardaTeclas[5] = teclas.potencia;		nombreOperacion[5] = "Potencia";
	guardaTeclas[6] = teclas.raiz;			nombreOperacion[6] = "Raiz";
	guardaTeclas[7] = teclas.simplificar;	nombreOperacion[7] = "Simplificar";
	guardaTeclas[8] = teclas.salir;			nombreOperacion[8] = "Salir";
	guardaTeclas[9] = teclas.borrar;		nombreOperacion[9] = "Borrar";
	guardaTeclas[10] = teclas.guardarMem;	nombreOperacion[10]= "Guardar en memoria";
	guardaTeclas[11] = teclas.cargarMem;	nombreOperacion[11]= "Usar memoria";
	for (int i = 0; i <= 11; i++){
		do{ 
			teclasRepetidas = false;
			cout << nombreOperacion[i] << " (" << guardaTeclas[i] << "): ";
			cin >> teclaAux;
			compruebaTeclas(teclaAux, teclasRepetidas, contadorTec);
			guardaTeclas[i] = teclaAux;
		}while (teclasRepetidas == true);
	}fileout.open("configuracion.txt");
	for (int i = 0; i <= 11; i++){
		fileout << guardaTeclas[i] << " ";
	}fileout.close();
}

void config(ConfigTeclas& teclas){
	char teclaCaracter, opcion;
	ofstream fileout;
	ifstream filein;
	fileout.open("configuracion.txt");
	if (fileout.is_open() == false) configuraTeclas(ConfigTeclas& teclas);
	else{
		cout << "Desea utilizar la configuracion por defecto?(s/n): ";
		cin >> opcion;
		if (opcion == 's'){ //Default(teclas);}
			fileout.open("configuracion.txt");
			remove("configuracion.txt");
		}
		else if (opcion == 'n'){
			configuraTeclas(ConfigTeclas& teclas);
		}
	}
}

void calc(){
	bool fin = false, matherror = false, syntaxerror = false, error=false, binario = false, endstream = false;
	char c;
	ConfigTeclas teclas;
	double op1 = 0, op2 = 0;
	while (fin==false){
		c = cin.peek();
		if (c != teclas.salir){
			if (isdigit (c) != 0) cin >> op1;
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
		}else fin = true;
	}
}
void descartarEspacios(char& operador){
	do{
		cin.get(operador);
		} while (operador == ' ');
}
void frac(){
	int num1 = 0, denom1 = 1, num2 = 0, denom2 = 1;
	char c, operador;
	ConfigTeclas teclas;
	bool error = 0, clear = 0, binario = 0, natural = 0;
	do{
		c=cin.peek();
		if (c != teclas.salir){
		if (isdigit (c) != 0) leerFraccion (num1, denom1, error, natural);
		//else if (c=='n') { op1 = mem; cin >> c;}
		descartarEspacios(operador);
		leerOperador(operador, binario, error);
		//if (operador == 'c') clear = 1;
		//else if (operador == 'm') {mem = op1; cin.get (c);}
		while ((error == false) && (operador != '\n') ){
			if (binario == true) leerFraccion (num2, denom2, error, natural);
			operacionFracciones(num2, denom2, num1, denom1 , operador, error, natural);
			if (error) operador = '\n';
			else descartarEspacios(operador);
		}
		
	if (!error) cout << num1 << '|' << denom1 << endl;
	else {cout << "Error\n0\n"; error =0; cin.sync(); num1 = 0; denom1 = 1;}
}
	}while (c != teclas.salir);
}

int main(){
	int opcion;
	bool salir = false;
	opConfigDef();
	do{
		mostrarMenu();
		cin >> opcion;
		cin.ignore(1, '\n');
		cin.fail();
		if (cin.fail()) cout << "Opcion no valida.\n";
		else if (opcion == 1) calc();
		else if (opcion == 2) config(ConfigTeclas& teclas);
		else if (opcion == 3) frac();
		else if (opcion == 5) salir = true;
		cin.clear();
		cin.sync();
	}while (!salir);
}