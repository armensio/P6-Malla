//
// Created by eduar on 05/12/2025.
//

#ifndef P6_MALLAREGULAR_H
#define P6_MALLAREGULAR_H
#include <list>
#include <vector>
#include <iostream>
using namespace std;

#include <map>
#include <cmath>

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
                if(*it==dato){
                    puntos.erase(it);
                    tam--;
                    return true;
                }
            }
            return false;
        }
        int getTam(){return tam;}
        typename list<T>::iterator begin() { return puntos.begin(); }
        typename list<T>::iterator end() { return puntos.end(); }
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
    vector<T> Ncercanos;
    map<float, T> cercanos;
    Casilla *c1;
    int p = nDiv;

    // Buscar el radio mínimo que contenga al menos n elementos
    for (int k = 1; k < nDiv; k++) {
        int cont = 0;
        for (float i = xcentro - (tamCasillaX * k); i < xcentro + (tamCasillaX * k); i += tamCasillaX) {
            for (float j = ycentro - (tamCasillaY * k); j < ycentro + (tamCasillaY * k); j += tamCasillaY) {
                if (i >= xMin && i <= xMax && j >= yMin && j <= yMax) {
                    c1 = obtenerCasilla(i, j);
                    if (c1) {
                        cont += c1->getTam();
                    }
                }
            }
        }
        if (cont >= n) {
            p = k + 1;
            break;
        }
    }

    // Recopilar todos los elementos en el radio encontrado y calcular distancias
    for (float i = xcentro - (tamCasillaX * p); i < xcentro + (tamCasillaX * p); i += tamCasillaX) {
        for (float j = ycentro - (tamCasillaY * p); j < ycentro + (tamCasillaY * p); j += tamCasillaY) {
            if (i >= xMin && i <= xMax && j >= yMin && j <= yMax) {
                c1 = obtenerCasilla(i, j);
                if (c1) {
                    // Acceder a la lista de puntos de la casilla
                    typename list<T>::iterator it;
                    // Necesitamos acceder a la lista privada, deberás añadir un método público en Casilla
                    // Por ahora, asumiendo que puedes acceder o crear un getter
                    for (it = c1->begin(); it != c1->end(); ++it) {
                        // Calcular distancia euclidiana
                        float dx = xcentro - (*it)->getCoordenadas().getLongitud();
                        float dy = ycentro - (*it)->getCoordenadas().getLatitud();
                        float distancia = sqrt(dx * dx + dy * dy);

                        cercanos.insert(make_pair(distancia, *it));
                    }
                }
            }
        }
    }

    // Quedarnos con los n más cercanos
    typename map<float, T>::iterator itm = cercanos.begin();
    for (int i = 0; i < n && itm != cercanos.end(); i++, ++itm) {
        Ncercanos.push_back(itm->second);
    }

    return Ncercanos;
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
