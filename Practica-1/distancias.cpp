#include <iostream>
#include <cmath>
#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

typedef float real;
typedef vector<real> lista;
typedef vector<lista> matriz;

#define N 8

matriz poblation;
lista child;
string word;
real aux;
int SIZE;
char c;
int iter=0;

void show_matrix(){
    for (int i=0;i<poblation.size();i++){
        cout<<i+1<<")\t[ ";
        for (int j = 0; j <poblation[0].size(); j++){
            cout<<poblation[i][j]<<" - ";
        }
        cout<<" ]"<<endl;
    }
}

real manhattan(int pos1, int pos2){
    real suma = 0;
    for(int i = 0; i < N; i++)
        if(poblation[i][pos1] != -1 && poblation[i][pos2] != -1){
            suma += abs(poblation[i][pos1] - poblation[i][pos2]);
        }
    return suma;
}

real euclidiana(int pos1, int pos2){
    real suma = 0;
    for(int i = 0; i < N; ++i)
        if(poblation[i][pos1] != -1 && poblation[i][pos2] != -1)
            suma += pow(poblation[i][pos1] - poblation[i][pos2], 2);

    return sqrt(suma);
}

real minkowski(int pos1, int pos2, int r){
    real suma = 0, rpta = 0;
    for(int i = 0; i < N; ++i){
        if(poblation[pos1][i] != -1 && poblation[pos2][i] != -1)
            suma += pow(abs(poblation[i][pos1] - poblation[i][pos2]), r);
    }
    rpta = pow(suma,1.0/r);
    return rpta;
}

void prepros(){
    ifstream file;
    ofstream out;
    file.open("movie.csv");
    out.open("inputmovie.csv");
    int cont_coma=0, cont_salt=0;
    if (file.is_open()) {
        #pragma omp parrallel for num_threads(8) default (none)\
        private (file,word)        
        for (;file.get(c); ){
            #pragma omp critical
            if(c==10)
                cont_salt++;
            if (c==','){
                cont_coma++;
                out<<' ';
            }
            else
                out<<c;
        }
    }else
        cout << "Error opening file";
    cout<<"comas "<<cont_coma<< "  a :  "<<cont_salt<<endl;
    SIZE=cont_coma/cont_salt;
    file.close();
    out.close();
}


void read(){
    ifstream file;
    file.open("inputmovie.csv");
    if (file.is_open()) {
        #pragma omp parrallel for num_threads(8) default (none)\
        private (file,word)        
        for (;file>>word; ){
            #pragma omp critical
            if (isdigit(word[0]) || word[0]=='-'){
                aux= stof(word);
                child.push_back(aux);
                iter++;
            }
            if (iter>=SIZE){
                iter=0;
                poblation.push_back(child);
                child.clear();
            }
            //cout<<word<<endl;
        }
    }else
        cout << "Error opening file";
    file.close();
}

int main(){
    double wtimestart = omp_get_wtime();
    prepros();
    read();
    cout<<"M: "<<manhattan(4,7)<<endl;
    cout<<"E: "<<euclidiana(4,5)<<endl;
    cout<<"Mi: "<<minkowski(4,7,1)<<endl;
    clock_t fin =clock();
    double wtimefin = omp_get_wtime();
    cout<<"omp time: "<<(wtimefin-wtimestart)<<endl;
	show_matrix();
    return 0;
}