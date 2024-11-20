#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>

using namespace std;

// 2. Constantes
const int ANIO_ACTUAL = 2024;
const float PORCENTAJE_COLEGIO = 0.40;
const float PORCENTAJE_ADMISION = 0.60;
const float NOTA_MINIMA_ADMITIDO = 85.0;
const float NOTA_MINIMA_ESPERA = 75.0;

// 3. Variables globales
struct Estudiante {
    string cedula;
    string nombre;
    int anioNacimiento;
    int edad;
    float notaMatematicas;
    float notaEspanol;
    float notaCiencias;
    float notaEstudiosSociales;
    float promedioColegio;
    float notaExamenAdmision;
    float porcentajeCriterioColegio;
    float porcentajeExamenAdmision;
    float promedioAdmision;
    string calificacion;
};

vector<Estudiante> estudiantes;
int cantAdmitidos = 0;
int cantEspera = 0;
int cantNoAdmitidos = 0;
float sumaAdmitidos = 0;
float sumaEspera = 0;
float sumaNoAdmitidos = 0;

// 4. Prototipos
void menu();
void ingresarDatos();
void mostrarEstadisticas();
void mostrarGrafico();
string obtenerEntradaValida();
float obtenerNotaValida(string mensaje);
void limpiarPantalla();
void pausar();
bool validarCedula(string cedula);

// 5. Funciones
string obtenerEntradaValida() {
    string entrada;
    getline(cin, entrada);
    while (entrada.empty()) {
        cout << "La entrada no puede estar vacia. Intente nuevamente: ";
        getline(cin, entrada);
    }
    return entrada;
}

float obtenerNotaValida(string mensaje) {
    float nota;
    bool valido = false;
    do {
        cout << mensaje;
        if (cin >> nota) {
            if (nota >= 0 && nota <= 100) {
                valido = true;
            } else {
                cout << "La nota debe estar entre 0 y 100" << endl;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Por favor ingrese un numero valido" << endl;
        }
    } while (!valido);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return nota;
}

bool validarCedula(string cedula) {
    if (cedula.empty()) return false;
    for (size_t i = 0; i < estudiantes.size(); i++) {
        if (estudiantes[i].cedula == cedula) return false;
    }
    return true;
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

// 6. Procedimientos
void ingresarDatos() {
    char continuar;
    do {
        limpiarPantalla();
        cout << "=== INGRESO DE DATOS DEL ESTUDIANTE ===" << endl;
        
        Estudiante est;
        
        do {
            cout << "Cedula: ";
            est.cedula = obtenerEntradaValida();
        } while (!validarCedula(est.cedula));

        cout << "Nombre: ";
        est.nombre = obtenerEntradaValida();

        cout << "Year de Nacimiento (1900-" << ANIO_ACTUAL << "): ";
        do {
            cin >> est.anioNacimiento;
        } while (est.anioNacimiento < 1900 || est.anioNacimiento > ANIO_ACTUAL);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        est.edad = ANIO_ACTUAL - est.anioNacimiento;

        est.notaMatematicas = obtenerNotaValida("Nota Matematicas: ");
        est.notaEspanol = obtenerNotaValida("Nota Espanol: ");
        est.notaCiencias = obtenerNotaValida("Nota Ciencias: ");
        est.notaEstudiosSociales = obtenerNotaValida("Nota Estudios Sociales: ");
        est.notaExamenAdmision = obtenerNotaValida("Nota Examen de Admision: ");

        // Calculos
        est.promedioColegio = (est.notaMatematicas + est.notaEspanol + 
                              est.notaCiencias + est.notaEstudiosSociales) / 4.0;
        
        est.porcentajeCriterioColegio = est.promedioColegio * PORCENTAJE_COLEGIO;
        est.porcentajeExamenAdmision = est.notaExamenAdmision * PORCENTAJE_ADMISION;
        est.promedioAdmision = est.porcentajeCriterioColegio + est.porcentajeExamenAdmision;

        // Determinar calificacion
        if (est.promedioAdmision >= NOTA_MINIMA_ADMITIDO) {
            est.calificacion = "Admitido";
            cantAdmitidos++;
            sumaAdmitidos += est.promedioAdmision;
        } else if (est.promedioAdmision >= NOTA_MINIMA_ESPERA) {
            est.calificacion = "En Espera";
            cantEspera++;
            sumaEspera += est.promedioAdmision;
        } else {
            est.calificacion = "No Admitido";
            cantNoAdmitidos++;
            sumaNoAdmitidos += est.promedioAdmision;
        }

        estudiantes.push_back(est);

        // Mostrar resultados
        cout << "\n=== RESULTADOS DEL ESTUDIANTE ===" << endl;
        cout << "Cedula: " << est.cedula << endl;
        cout << "Nombre: " << est.nombre << endl;
        cout << "Year Nacimiento: " << est.anioNacimiento << endl;
        cout << "Edad: " << est.edad << endl;
        cout << "Notas:" << endl;
        cout << "  Matematicas: " << est.notaMatematicas << endl;
        cout << "  Espanol: " << est.notaEspanol << endl;
        cout << "  Ciencias: " << est.notaCiencias << endl;
        cout << "  Estudios Sociales: " << est.notaEstudiosSociales << endl;
        cout << "Promedio Colegio: " << fixed << setprecision(2) << est.promedioColegio << endl;
        cout << "Porcentaje Criterio Colegio: " << est.porcentajeCriterioColegio << endl;
        cout << "Porcentaje Examen Admision: " << est.porcentajeExamenAdmision << endl;
        cout << "Promedio Admision: " << est.promedioAdmision << endl;
        cout << "Calificacion: " << est.calificacion << endl;

        cout << "\nDesea continuar (S/N)? ";
        cin >> continuar;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (toupper(continuar) == 'S');
}

void mostrarEstadisticas() {
    limpiarPantalla();
    cout << "=== ESTADASTICAS ===" << endl << endl;
    
    float promedioAdmitidos = cantAdmitidos > 0 ? sumaAdmitidos / cantAdmitidos : 0;
    float promedioEspera = cantEspera > 0 ? sumaEspera / cantEspera : 0;
    float promedioNoAdmitidos = cantNoAdmitidos > 0 ? sumaNoAdmitidos / cantNoAdmitidos : 0;

    cout << "Cantidad Estudiantes Admitidos: " << cantAdmitidos << endl;
    cout << "Promedio Estudiantes Admitidos: " << fixed << setprecision(2) 
         << promedioAdmitidos << endl;
    
    cout << "\nCantidad Estudiantes En Espera: " << cantEspera << endl;
    cout << "Promedio Estudiantes En Espera: " << promedioEspera << endl;
    
    cout << "\nCantidad Estudiantes No Admitidos: " << cantNoAdmitidos << endl;
    cout << "Promedio Estudiantes No Admitidos: " << promedioNoAdmitidos << endl;

    pausar();
}

void mostrarGrafico() {
    limpiarPantalla();
    cout << "=== GRaFICO ESTUDIANTES SEG�N ESTADO ===" << endl << endl;
    
    cout << "Admitidos  ";
    for (int i = 0; i < cantAdmitidos; i++) cout << "*";
    cout << " (" << cantAdmitidos << ")" << endl;
    
    cout << "En Espera  ";
    for (int i = 0; i < cantEspera; i++) cout << "*";
    cout << " (" << cantEspera << ")" << endl;
    
    cout << "No Admitidos ";
    for (int i = 0; i < cantNoAdmitidos; i++) cout << "*";
    cout << " (" << cantNoAdmitidos << ")" << endl;

    pausar();
}

void menu() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << "1) Ingresar Datos" << endl;
        cout << "2) Estadasticas" << endl;
        cout << "3) Grafico" << endl;
        cout << "4) Salir" << endl;
        cout << "Ingrese su Opcion: ";
        
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: ingresarDatos(); break;
            case 2: mostrarEstadisticas(); break;
            case 3: mostrarGrafico(); break;
            case 4: cout << "Gracias por usar el sistema!" << endl; break;
            default: cout << "Opcion invalida" << endl; pausar();
        }
    } while (opcion != 4);
}

// 7. Cuerpo principal
int main() {
    menu();
    return 0;
}
