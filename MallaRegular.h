//
// Created by eduar on 05/12/2025.
//

#ifndef P6_MALLAREGULAR_H
#define P6_MALLAREGULAR_H
#include <list>
#include <vector>
#include <iostream>
using namespace std;


template<typename T>
class MallaRegular {
public:
    class Casilla {
    private:
        list<T> puntos;
        int tam=0;
    public:
        Casilla() {}
        void insertar(const T &dato){
            puntos.push_back(dato);
            tam++;
        }
        T* buscar(const T &dato){
            typename list<T>::iterator it;
            it=puntos.begin();
            for(;it!=puntos.end();++it){
                if(*it==dato){
                    return &(*it);
                }
            }
            return 0;
        }
        bool borrar(const T &dato){
            typename list<T>::iterator it;
            it=puntos.begin();
            for(;it!=puntos.end();++it){
                if(*it!=dato){
                    puntos.erase(it);
                    tam--;
                    return true;
                }
            }
            return false;
        }
        int getTam(){return tam;}
    };
private:
    float xMin,yMin,xMax,yMax;
    float tamCasillaX=1,tamCasillaY=1,nDiv;
    vector<vector<Casilla>> matriz;
    Casilla* obtenerCasilla(float x,float y){
        int i=(x-xMin)/tamCasillaX;
        int j=(y-yMin)/tamCasillaY;

        if(i >= matriz.size() || j >= matriz[i].size()){
            cerr << "ERROR: Indices fuera de rango - i: " << i << " j: " << j
                 << " (matriz: " << matriz.size() << "x" << matriz[i].size() << ")" << endl;
            cerr << "Coordenadas: x=" << x << " y=" << y << endl;
            cerr << "Limites: xMin=" << xMin << " xMax=" << xMax
                 << " yMin=" << yMin << " yMax=" << yMax << endl;
            return nullptr;
        }
        return &matriz[i][j];
    }
public:
    MallaRegular();
    MallaRegular(float xMin, float yMin, float xMax, float yMax, float nDiv);

    vector<T> buscarCercana(float xcentro, float ycentro, int n=1); //Implementar
    void insertar(float x, float y, const T &dato);//DIAPOSITIVA
    T* buscar(float x, float y, const T &dato);//DIAPOSITIVA
    bool borrar(float x, float y, const T &dato);//DIAPOSITIVA
    unsigned maxElementosPorCelda();
    float promedioElementosPorCelda();
};

template<typename T>
MallaRegular<T>::MallaRegular() {

}

template<typename T>
MallaRegular<T>::MallaRegular(float xMin, float yMin, float xMax, float yMax, float nDiv):xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax), nDiv(nDiv){
            tamCasillaX= (xMax-xMin) / nDiv;
            tamCasillaY= (yMax-yMin) / nDiv;
            matriz.insert(matriz.begin(), nDiv, vector<Casilla>(nDiv));
            //matriz.resize(nDiv, vector<Casilla>(nDiv));
}

template<typename T>
vector<T> MallaRegular<T>::buscarCercana(float xcentro, float ycentro, int n) {

}


template<typename T>
void MallaRegular<T>::insertar(float x, float y, const T &dato) {
    Casilla *c= obtenerCasilla(x,y);
    if(!c){
        cerr << "C APUNTA A NULL";
    }
    c->insertar(dato);
}

template<typename T>
T* MallaRegular<T>::buscar(float x, float y, const T &dato){
    Casilla *c= obtenerCasilla(x,y);
    return c->buscar(dato);
}

template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T &dato) {
    Casilla *c= obtenerCasilla(x,y);
    return c->borrar(dato);
}

template<typename T>
unsigned int MallaRegular<T>::maxElementosPorCelda() {
    unsigned int max=0;
    for(int i=0;i<nDiv;i++){
        for(int j=0;j<nDiv;j++){
            if(matriz[i][j].getTam()>max){
                max=matriz[i][j].getTam();
            }
        }
    }
    return max;
}

template<typename T>
float MallaRegular<T>::promedioElementosPorCelda() {
    int suma=0;
    for(int i=0;i<nDiv;i++){
        for(int j=0;j<nDiv;j++){
            suma+=matriz[i][j].getTam();
        }
    }
    return suma/(nDiv*nDiv);
}


#endif //P6_MALLAREGULAR_H
