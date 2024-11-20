#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

struct Vehicle {
    int invoiceNumber;
    string plateNumber;
    string brand;
    string model;
    int vehicleType;
    int washType;
    int price;
};

vector<Vehicle> vehicles;
int invoiceCounter = 1;

void displayMenu();
void enterVehicleData();
void viewVehicleStatistics();
void viewWashStatistics();
void showVehicleGraph();
void showWashGraph();

int main() {
    int option;
    do {
        displayMenu();
        while (!(cin >> option)) {
            cout << "Entrada invalida. Por favor ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        switch (option) {
            case 1:
                enterVehicleData();
                break;
            case 2:
                viewVehicleStatistics();
                break;
            case 3:
                viewWashStatistics();
                break;
            case 4:
                showVehicleGraph();
                break;
            case 5:
                showWashGraph();
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
        }
    } while (option != 6);

    return 0;
}

void displayMenu() {
    cout << "\n--- Menu Principal ---\n";
    cout << "1- Ingresar Datos Vehiculos\n";
    cout << "2- Ver Estadisticas Vehiculos Lavados segun tipo de Vehiculo\n";
    cout << "3- Ver Estadisticas Vehiculos Lavados segun tipo de Lavado\n";
    cout << "4- Ver Grafico Vehiculos Lavados por Tipo de Vehiculo\n";
    cout << "5- Ver Grafico Vehiculos Lavados por Tipo de Lavado\n";
    cout << "6- Salir\n";
    cout << "Seleccione una opcion: ";
}

void enterVehicleData() {
    char continueInput;
    do {
        Vehicle vehicle;
        vehicle.invoiceNumber = invoiceCounter++;

        cout << "Ingrese numero de placa: ";
        getline(cin, vehicle.plateNumber);
        cout << "Ingrese marca del vehiculo: ";
        getline(cin, vehicle.brand);
        cout << "Ingrese modelo del vehiculo: ";
        getline(cin, vehicle.model);
        
        do {
            cout << "Ingrese tipo de vehiculo (1=Sencillo, 2=4x4, 3=Microbus o Camion): ";
            while (!(cin >> vehicle.vehicleType)) {
                cout << "Entrada invalida. Por favor ingrese un numero entre 1 y 3: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (vehicle.vehicleType < 1 || vehicle.vehicleType > 3);
        
        do {
            cout << "Ingrese tipo de lavado (1=Solo Lavado, 2=Lavado, Aspirado y Encerado): ";
            while (!(cin >> vehicle.washType)) {
                cout << "Entrada invalida. Por favor ingrese un numero entre 1 y 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (vehicle.washType < 1 || vehicle.washType > 2);

        switch (vehicle.vehicleType) {
            case 1: // Sencillo
                vehicle.price = (vehicle.washType == 1) ? 3000 : 5000;
                break;
            case 2: // 4x4
                vehicle.price = (vehicle.washType == 1) ? 5000 : 7000;
                break;
            case 3: // Microbus o Camion
                vehicle.price = (vehicle.washType == 1) ? 7000 : 12000;
                break;
        }

        cin.ignore();
        cout << "\n--- Factura ---\n";
        cout << "Factura #: " << vehicle.invoiceNumber << "\n";
        cout << "Placa: " << vehicle.plateNumber << "\n";
        cout << "Marca: " << vehicle.brand << "\n";
        cout << "Modelo: " << vehicle.model << "\n";
        cout << "Tipo de Vehiculo: " << ((vehicle.vehicleType == 1) ? "Sencillo" : (vehicle.vehicleType == 2) ? "4x4" : "Microbus o Camion") << "\n";
        cout << "Tipo de Lavado: " << ((vehicle.washType == 1) ? "Solo Lavado" : "Lavado, Aspirado y Encerado") << "\n";
        cout << "Precio a Pagar: " << vehicle.price << " colones\n";

        vehicles.push_back(vehicle);

        cout << "\nDesea continuar ingresando vehiculos? (S/N): ";
        cin >> continueInput;
        cin.ignore();
    } while (continueInput == 'S' || continueInput == 's');
}

void viewVehicleStatistics() {
    int simpleCount = 0, fourByFourCount = 0, heavyCount = 0;
    int simpleTotal = 0, fourByFourTotal = 0, heavyTotal = 0;

    for (const auto& vehicle : vehicles) {
        if (vehicle.vehicleType == 1) {
            simpleCount++;
            simpleTotal += vehicle.price;
        } else if (vehicle.vehicleType == 2) {
            fourByFourCount++;
            fourByFourTotal += vehicle.price;
        } else if (vehicle.vehicleType == 3) {
            heavyCount++;
            heavyTotal += vehicle.price;
        }
    }

    cout << "\n--- Estadisticas por Tipo de Vehiculo ---\n";
    cout << "Cantidad de Vehiculos Tipo Sencillos: " << simpleCount << "\n";
    cout << "Dinero Recaudado por Vehiculos Tipo Sencillos: " << simpleTotal << " colones\n";
    cout << "Cantidad de Vehiculos Tipo 4x4: " << fourByFourCount << "\n";
    cout << "Dinero Recaudado por Vehiculos Tipo 4x4: " << fourByFourTotal << " colones\n";
    cout << "Cantidad de Vehiculos Tipo Microbus o Camion: " << heavyCount << "\n";
    cout << "Dinero Recaudado por Vehiculos Tipo Microbus o Camion: " << heavyTotal << " colones\n";
}

void viewWashStatistics() {
    int simpleWashCount = 0, fullWashCount = 0;
    int simpleWashTotal = 0, fullWashTotal = 0;

    for (const auto& vehicle : vehicles) {
        if (vehicle.washType == 1) {
            simpleWashCount++;
            simpleWashTotal += vehicle.price;
        } else if (vehicle.washType == 2) {
            fullWashCount++;
            fullWashTotal += vehicle.price;
        }
    }

    cout << "\n--- Estadisticas por Tipo de Lavado ---\n";
    cout << "Cantidad de Vehiculos con Solo Lavado: " << simpleWashCount << "\n";
    cout << "Dinero Recaudado por Vehiculos con Solo Lavado: " << simpleWashTotal << " colones\n";
    cout << "Promedio Dinero Recaudado por Vehiculos con Solo Lavado: " << (simpleWashCount ? (simpleWashTotal / simpleWashCount) : 0) << " colones\n";
    cout << "Cantidad de Vehiculos con Lavado, Aspirado y Encerado: " << fullWashCount << "\n";
    cout << "Dinero Recaudado por Vehiculos con Lavado, Aspirado y Encerado: " << fullWashTotal << " colones\n";
    cout << "Promedio Dinero Recaudado por Vehiculos con Lavado, Aspirado y Encerado: " << (fullWashCount ? (fullWashTotal / fullWashCount) : 0) << " colones\n";
}

void showVehicleGraph() {
    int simpleCount = 0, fourByFourCount = 0, heavyCount = 0;

    for (const auto& vehicle : vehicles) {
        if (vehicle.vehicleType == 1) simpleCount++;
        else if (vehicle.vehicleType == 2) fourByFourCount++;
        else if (vehicle.vehicleType == 3) heavyCount++;
    }

    cout << "\n******* Grafico Vehiculos Lavados por Tipo de Vehiculo *******\n";
    cout << "Veh. Sencillos: ";
    for (int i = 0; i < simpleCount; ++i) cout << "*";
    cout << "\nVeh. 4x4: ";
    for (int i = 0; i < fourByFourCount; ++i) cout << "*";
    cout << "\nVeh. Pesados: ";
    for (int i = 0; i < heavyCount; ++i) cout << "*";
    cout << "\n<Pulse tecla para Abandonar>";
    cin.get();
}

void showWashGraph() {
    int simpleWashCount = 0, fullWashCount = 0;

    for (const auto& vehicle : vehicles) {
        if (vehicle.washType == 1) simpleWashCount++;
        else if (vehicle.washType == 2) fullWashCount++;
    }

    cout << "\n******* Grafico Vehiculos Lavados por Tipo de Lavado *******\n";
    cout << "Sencillo: ";
    for (int i = 0; i < simpleWashCount; ++i) cout << "*";
    cout << "\nCompleto: ";
    for (int i = 0; i < fullWashCount; ++i) cout << "*";
    cout << "\n<Pulse tecla para Abandonar>";
    cin.get();
}
