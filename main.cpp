//Luis Q. C. - K1023
#include <iostream>
#include <fstream>

using namespace std;

int ordenAscendenteVector(int m[], int dim){
    int mayor = 0;
    int pos = 0;

    for (int i = 0; i < dim; i++)
        if(mayor < m[i]){
            mayor = m[i];
            pos = i;
        }

   return pos; 
}

void ordenAscendente_burbuja_matriz(float m[][2], int dim){  //Ordenamiento ascendente con metodo burbuja aplicado en una matriz
    float aux = 0;
    int auxP = 0;
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim - 1; j++)
            if(m[j][1] > m[j+1][1]){
                aux = m[j][1];
                m[j][1] = m[j+1][1];
                m[j+1][1] = aux;
                
                auxP = m[j][0];
                m[j][0] = m[j+1][0];
                m[j+1][0] = auxP;
            }
}

int main(){

    const int cantClientes {8};
    const int cantTiposProd {5};

    float pesoTrans[cantClientes][cantTiposProd] {};    //Matriz 8x5 que contendrá los pesos transportados según cliente-producto.
    float distReco[cantClientes][cantTiposProd] {};     //Matriz 8x5 que contendrá las distancias recorridas según cliente-producto.
    int cantEntregas[cantClientes][cantTiposProd] {};   // Matriz 8x5 con la cantidad de entregas según cliente-producto.
    int cantProdMayor[cantClientes] {};                 // Vector de 8 elementos que se usará más adelante para ordenar en forma ascendente
                                                        // los clientes con mayor peso transportado.
    float clienteMayorCantConPosiciones[cantTiposProd][2] {};   // Matriz 8x2 que contendrá por una parte índices (0-4)
                                                                // también almacenará los recorridos del cliente que más peso transportó en todos sus viajes.


    string nombreClien[cantClientes];
    string nombreProd[cantTiposProd];

    ifstream archilec;
    archilec.open("Nombres.txt");
    if(!archilec){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    for (int i = 0; i < cantClientes && archilec >> nombreClien[i]; i++);
    for (int i = 0; i < cantTiposProd && archilec >> nombreProd[i]; i++);

    archilec.close();
    
    archilec.open("Datos.txt");
    if(!archilec){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int nCliente, nProd;
    float cantPeso, cantDist;
    while (archilec >> nCliente >> nProd >> cantPeso >> cantDist)
    {
        pesoTrans[nCliente][nProd] += cantPeso;
        cantEntregas[nCliente][nProd]++;
        distReco[nCliente][nProd] += cantDist;
    }
    archilec.clear();

    // Punto 1

    cout << "=====================Punto 1=======================" << endl;
    cout << "Lista de tipos de producto por cliente que superan 13000kg\n" << endl;

    for (int i = 0; i < cantClientes; i++)
    {
        cout << nombreClien[i] << ": ";
        
        for (int j = 0; j < cantTiposProd; j++)
            if(pesoTrans[i][j] > 13000){
                cout << nombreProd[j] << ", ";
                cantProdMayor[i]++;
            }

        cout << endl;
    }

    // Punto 2
    cout << "\n=====================Punto 2=======================" << endl;
    cout << "Listado de KM recorridos por tipo de producto (en forma ascendente)\n" << endl;

    nCliente = ordenAscendenteVector(cantProdMayor, cantClientes);
    for (int i = 0; i < cantTiposProd; i++)
    {
        clienteMayorCantConPosiciones[i][1] = distReco[nCliente][i];
        clienteMayorCantConPosiciones[i][0] += i;
    }

    ordenAscendente_burbuja_matriz(clienteMayorCantConPosiciones, cantTiposProd);
    
    for (int i = 0; i < cantTiposProd; i++)
    {
            int pos = clienteMayorCantConPosiciones[i][0];
            cout << nombreProd[pos] << ": " << clienteMayorCantConPosiciones[i][1] << endl;
    }
    
    //Punto 3
    cout << "\n=====================Punto 3=======================" << endl;
    cout << "===================================================\n" << endl;

    nProd = clienteMayorCantConPosiciones[cantTiposProd-1][0];
    int sumaCant {};
    for (int i = 0; i < cantClientes; i++)
        sumaCant += cantEntregas[i][nProd];
    
    cout << "Cantidad de entregas para el tipo de producto " << nombreProd[nProd] << ": " << sumaCant << endl;

    return 0;
}