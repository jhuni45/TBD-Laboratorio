#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

const int N = 8;

vector<vector<double>> tabla = {{3.5,   2,   5,   3, -1,  -1,   5,  3},
                                {  2, 3.5,   1,   4,  4, 4.5,   2, -1},
                                { -1,   4,   1, 4.5,  1,   4,  -1, -1},
                                {4.5,  -1,   3,  -1,  4,   5,   3,  5},
                                {  5,   2,   5,   3, -1,   5,   5,  4},
                                {1.5, 3.5,   1, 4.5, -1, 4.5,   4,2.5},
                                {2.5,  -1,  -1,   4,  4,   4,   5,  3},
                                {  2,   2,  -1,   2,  1,   4,  -1, -1}};

string nombres[N] = {"Angelica", "Bill", "Chan", "Dan",
                     "Hailey", "Jordyn", "Sam", "Veronica"};

int encontrarIndice(string nombre){
    for(int i = 0; i < N; ++i)
        if(nombre == nombres[i]) return i;
    return -1;
}

float manhattan(int idNombre1, int idNombre2){
    float suma = 0;
    for(int i = 0; i < N; i++)
        if(tabla[i][idNombre1] != -1 && tabla[i][idNombre2] != -1){
            suma += abs(tabla[i][idNombre1] - tabla[i][idNombre2]);
        }
    return suma;
}

float euclidiana(int idNombre1, int idNombre2){
    float suma = 0;
    for(int i = 0; i < N; ++i)
        if(tabla[i][idNombre1] != -1 && tabla[i][idNombre2] != -1)
            suma += pow(tabla[i][idNombre1] - tabla[i][idNombre2], 2);

    return sqrt(suma);
}

float minkowski(int idNombre1, int idNombre2){
    float suma = 0, rpta = 0;
    float r=1;
    if(r=1)
        manhattan(idNombre1,idNombre2);
    else
        euclidiana(idNombre1,idNombre2);
    for(int i = 0; i < N; ++i){
        if(tabla[idNombre1][i] != -1 && tabla[idNombre2][i] != -1)
            suma += pow(abs(tabla[i][idNombre1] - tabla[i][idNombre2]), r);
    }
    rpta = pow(suma,1.0/r);
    return rpta;
}

float distanciaCoseno(int idNombre1, int idNombre2){
    float escalar = 0, normal1 = 0, normal2 = 0;
    for(int i = 0; i < N; ++i)
        if(tabla[idNombre1][i] != -1 && tabla[idNombre2][i] != -1)
        {
            escalar += (tabla[idNombre1][i] * tabla[idNombre2][i]);
            normal1 += pow(tabla[idNombre1][i], 2.0);
            normal2 += pow(tabla[idNombre2][i], 2.0);
        }

    normal1 = sqrt(normal1);
    normal2 = sqrt(normal2);

    return escalar / (normal1 * normal2);
}

float similitud(string nombre1, string nombre2, string funcion){
    int idNombre1 = encontrarIndice(nombre1);
    int idNombre2 = encontrarIndice(nombre2);
    if(funcion == "manhattan") return manhattan(idNombre1, idNombre2);
    else if(funcion == "euclidiana") return euclidiana(idNombre1, idNombre2);
    else if(funcion == "minkowski") return minkowski(idNombre1, idNombre2);
    else return distanciaCoseno(idNombre1, idNombre2);
}

int main(){
    cout << "La distancia manhattan es: " << similitud("Hailey", "Veronica", "manhattan") << endl;
    cout << "La distancia euclidiana es: " << similitud("Hailey", "Jordyn", "euclidiana") << endl;
    cout << "La distancia Coseno es: " << similitud("Angelica", "Bill", "minkowski") << endl;
    return 0;

}
