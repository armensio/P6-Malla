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
        int tam;
    public:
        Casilla() {}
        void insertar(const T &dato){puntos.push_back(dato);tam++;}
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
    float xMin=-2,yMin=-2,xMax=5000,yMax=5000;
    float tamCasillaX=1,tamCasillaY=1;
    vector<vector<Casilla>> matriz;
    Casilla* obtenerCasilla(float x,float y){
        unsigned int i=(x-xMin)/tamCasillaX;
        unsigned int j=(y-yMin)/tamCasillaY;
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
MallaRegular<T>::MallaRegular(float xMin, float yMin, float xMax, float yMax, float nDiv):xMin(xMin), yMin(yMin), xMax(xMax), yMax(yMax){
            tamCasillaX= (xMax-xMin) / nDiv;
            tamCasillaY= (yMax-yMin) / nDiv;
            matriz.insert(matriz.begin(), nDiv, vector<Casilla>(nDiv));
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
    for(int i=0;i<xMax;i++){
        for(int j=0;j<yMax;j++){
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
    for(int i=0;i<xMax;i++){
        for(int j=0;j<yMax;j++){
            suma+=matriz[i][j].getTam();
        }
    }
    return suma/(xMax/tamCasillaX);
}


#endif //P6_MALLAREGULAR_H
