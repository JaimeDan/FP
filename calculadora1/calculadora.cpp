#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

string nombreFich = "log.txt";
char a, c, d;
char salir = 'x', borrar = 'c', suma = '+', resta = '-';
char multiplicacion = '*', division = '/', potencia = '^'; 
char factorial = '!', raiz = 'r', guardarmem = 'm', usarmem = 'n';

//función factorial
int fact(int n){
    if (n == 0)
        return 1;
    else return fact(n-1)*n;
}
    
//función potencia
double exp(double a, int n){
    if (n == 0)
        return 1;
    else return exp(a, n-1)*a;
}

//función para la configuración de teclas
void config(){
    cin.sync();
    cout << "Configuracion" << endl;
    cout << "_____________" << endl;
    cout << "Desea volver a la configuracion por defecto?\nPulse S para la configuracion por defecto\nPulse cualquier otra tecla para configurar manualmente la calculadora" << endl;
    cin >> a; 
    if (a == 'S' || a == 's'){
        salir = 'x', borrar = 'c', suma = '+', resta = '-', multiplicacion = '*';
		division = '/', potencia = '^', factorial = '!', raiz = 'r';
		nombreFich = "log.txt";
    }
    else{
        cin.sync();
        do{
            cout << "Suma (" << suma << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') suma = suma;
            else cin >> suma;
            cin.sync();
            } while ((suma == resta) || (suma == multiplicacion) || (suma == borrar) || (suma == salir) || (suma == division) || (suma == potencia) || (suma == factorial) || (suma == raiz) || (suma == guardarmem) || (suma == usarmem));
        do{
            cout << "Resta (" << resta << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') resta = resta;
            else cin >> resta;
            cin.sync();
            } while ((resta == suma) || (resta == multiplicacion) || (resta == borrar) || (resta == salir) || (resta == division) || (resta == potencia) || (resta == factorial) || (resta == raiz) || (resta == guardarmem) || (resta == usarmem));
        do{
            cout << "Multiplicacion (" << multiplicacion << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') multiplicacion = multiplicacion;
            else cin >> multiplicacion;
            cin.sync();
            } while ((multiplicacion == suma) || (multiplicacion == resta) || (multiplicacion == borrar) || (multiplicacion == salir) || (multiplicacion == division) || (multiplicacion == potencia) || (multiplicacion == factorial) || (multiplicacion == raiz) || (multiplicacion == guardarmem) || (multiplicacion == usarmem));
        do{
            cout << "Division (" << division << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') division = division;
            else cin >> division;
            cin.sync();
            } while ((division == resta) || (division == multiplicacion) || (division == borrar) || (division == salir) || (division == suma) || (division == potencia) || (division == factorial) || (division == raiz) || (division == guardarmem) || (division == usarmem));
        do{
            cout << "Potencia (" << potencia << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') potencia = potencia;
            else cin >> potencia;
            cin.sync();
            } while (potencia == resta || potencia == multiplicacion || potencia == borrar || potencia == salir || potencia == suma || potencia == division || potencia == factorial || potencia == raiz || (potencia == guardarmem) || (potencia == usarmem));
        do{
            cout << "Factorial (" << factorial << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') factorial = factorial;
            else cin >> factorial;
            cin.sync();
            } while (factorial == resta || factorial == multiplicacion || factorial == borrar || factorial == salir || factorial == suma || factorial == division || factorial == potencia || factorial == raiz || (factorial == guardarmem) || (factorial == usarmem));
        do{
            cout << "Raiz (" << raiz << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') raiz = raiz;
            else cin >> raiz;
            cin.sync();
            } while (raiz == resta || raiz == multiplicacion || raiz == borrar || raiz == salir || raiz == suma || raiz == division || raiz == potencia || raiz == factorial || (raiz == guardarmem) || (raiz == usarmem));
        do{
            cout << "Salir (" << salir << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') salir = salir;
            else cin >> salir;
            cin.sync();
            } while (salir == resta || salir == multiplicacion || salir == borrar || salir == raiz || salir == suma || salir == division || salir == potencia || salir == factorial || (salir == guardarmem) || (salir == usarmem));
        do{
            cout << "Borrar (" << borrar << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') borrar = borrar;
            else cin >> borrar;
            cin.sync();
            } while (borrar == resta || borrar == multiplicacion || borrar == salir || borrar == raiz || borrar == suma || borrar == division || borrar == potencia || borrar == factorial || (borrar == guardarmem) || (borrar == usarmem));
        do{
            cout << "Guardar resultado en la memoria (" << guardarmem << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') guardarmem = guardarmem;
            else cin >> guardarmem;
            cin.sync();
            } while (guardarmem == resta || guardarmem == multiplicacion || guardarmem == salir || guardarmem == raiz || guardarmem == suma || guardarmem == division || guardarmem == potencia || guardarmem == factorial || (guardarmem == usarmem));
        do{
            cout << "Recuperar resultado de la memoria (" << usarmem << ")" << endl;
            cout << "Nueva tecla?: ";
            a = cin.peek();
            if (a == '\n') usarmem = usarmem;
            else cin >> usarmem;
            cin.sync();
            } while (usarmem == resta || usarmem == multiplicacion || usarmem == salir || usarmem == raiz || usarmem == suma || usarmem == division || usarmem == potencia || usarmem == factorial || (usarmem == guardarmem));
		cout << "Nombre del registro (" << nombreFich << ")" << endl;
		cout << "Nuevo nombre? (debe acabar en .txt): ";
		cin >> nombreFich;
    }

}
//calculadora
int calc(){
	int contador = 0;
    double op1 = 0, op2 = 0, mem = 0;
    bool error = 0, clear = 0;
    ofstream fout;
    fout.open(nombreFich);
    fout << "Historial de operaciones" << endl; 
    fout << "________________________" << endl;
	do{ 
        c = cin.peek();
        if (c == salir){
            fout << "\n\n________________\n";
            fout << "Fin del registro\n";

        }
        if (c != salir){
            if (isdigit(c) != 0){ 
                cin >> op1;
                fout << op1;
            }
            if ( c == usarmem) {
                op1 = mem; 
                cin >> c;
                fout << c;
            }            
            cin.get(c);
            fout << c;
            if (c == borrar) clear = 1;
			else if (c == guardarmem){
                mem = op1;
                cin.get(c);
            }else
             while (c != '\n'){

                if (c == suma || c == resta || c == multiplicacion || c == division || c == potencia){
                    d = cin.peek();
					//fout  << d ;//
					if (d == usarmem){
                        op2=mem;
                        cin.get(d);
                        fout << d;
                    }else if (d == borrar) clear = 1;
                    else{
                        cin >> op2;
                        fout << op2 ;
                    }
                    if ((cin.fail()) && (d != borrar) ){
						fout << d;
                        cout << "Operando no valido" << endl;
                        fout << "\nOperando no valido" << endl;

                    }
					else if ( c == suma ) op1 += op2;
                    else if ( c == resta ) op1 -= op2;
                    else if ( c == multiplicacion ) op1 *= op2;    
                    else if ( c == division ) op1 /= op2;
                    else if (c == potencia){
                        if (op2 - floor (op2) ==0){
                            if (op2 >=0 )
                                op1 = exp(op1, op2);
                            else if (op2 < 0)
                                op1 = 1.0 /(exp(op1, -op2));
                        }else{
                            op2 = 0;
                            error = 1;
                            cout << "Exponente no entero\n";
                            fout << "\nExponente no entero\n";

                        }
                    }
                }
                else if ( c == factorial){
                    if ((op1 >= 0) && (op1 - floor (op1) ==0) && op1 < 17)  op1 = fact(op1);
                    else if ((op1 >= 0) && (op1 - floor (op1) ==0) && op1 >= 17){
                        error = 1;
                        cout << "Desbordamiento\n";
                        fout << "\nDesbordamiento";
                    }else{
                        error = 1;
                        cout << "Funcion solo valida para numeros naturales\n";
                        fout << "\nFuncion solo valida para numeros naturales\n";

                    }
                }else if (c == raiz){
                    if (op1 >= 0)
                    op1 = sqrt(op1);
                    else {
                        error = 1;
                        cout << "Raiz negativa\n";
                        fout << "\nRaiz negativa\n";

                    }
                    }
                else if (c == borrar) clear = 1;
                else if (c == guardarmem) mem = op1;
                else{
                    error = 1;
                    cout << "Operando no valido" << endl;
                    fout << "\nOperando no valido" << endl;

                }
                error = error || cin.fail();
                cin.clear();
                if ((error == 1) || (clear == 1)) c='\n';
                else{ 
                    cin.get(c);
                    if (c != '\n')fout << c;

            } 
            }
            if ((error == 1) && (clear == 0)){
                cout << "Error.\n0" << endl;
                fout << "Error.\n0" << endl;

                op1 = 0, op2 = 0;
            }else if ((error == 0) && (clear == 1)){
                cout << "0" << endl;
				fout << "\n" << "0" << endl;
                op1 = 0, op2 = 0, clear = 0;
            }else if ((error == 0) && (clear == 0)){
                cout << op1 << endl;
                if (contador >= 1){
					fout << " = " << op1 << endl;
				}
				//fout << "= " << op1 << endl;
            }contador++;
            
            error = 0;
            cin.sync();
            
        }
    }while (c != salir);
    cin.clear();
    cin.sync();
    return 0;
}



int main(){
    int opcion;
      do{
       
        cout << "1.- Calculadora" << endl;
        cout << "2.- Configuracion" << endl;
        cout << "3.- Terminar" << endl;
        cout << "Opcion: ";
        cin >> opcion;
		cin.fail();
        if (cin.fail()) cout << "Opcion no valida!\n";
        else{
            if (opcion == 1) calc();
            else if (opcion == 2) config();
        }
        cin.clear();
        cin.sync();
        
    } while (opcion != 3);
    
} 