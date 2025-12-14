//
// Created by eduar on 22/11/2025.
//

#include "ThashMedicam.h"
#include <iostream>

ThashMedicam::ThashMedicam() : tabla(tamf, Entrada()) {
}


ThashMedicam::ThashMedicam(int maxElementos, float lambda): tamf(primo_superior(maxElementos/lambda)), taml(),
                                                            maxColisiones(), max10(), sumCol(), tabla(tamf,Entrada()) {

}

ThashMedicam::ThashMedicam(const ThashMedicam &orig): tamf(orig.tamf), taml(orig.taml),
                                                      maxColisiones(orig.maxColisiones),
                                                      max10(orig.max10), sumCol(orig.sumCol),
                                                      tabla(orig.tabla){
}

ThashMedicam::~ThashMedicam() {
}

int ThashMedicam::exploracion_cuadratica(int clave, int intento) {
    //h(x)=(x+i^2)%t
    int posicion;
    posicion=(clave+(intento+(intento*intento)))%tamf;
    return posicion;
}

int ThashMedicam::exploracion_doble1(int clave, int intento) {
    //h(x)=(h1(x)+i*i*h2(x))%t
    //h1(x)=x%t
    //h2(x)=1+(x%q) con q primo < t
    int posicion_funcion1 = clave % tamf;
    int posicion_funcion2 = 1 + (clave % primo_inferior(tamf));

    int desplazamiento = intento * posicion_funcion2;
    int posicion_final = (posicion_funcion1 + desplazamiento) % tamf;

    if(posicion_final < 0) posicion_final += tamf;

    return posicion_final;
}

int ThashMedicam::exploracion_doble2(int clave, int intento) {
    //h(x)=((h1(x)*h1(x))+i*h2(x))%t
    //h1(x)=x%t
    //h2(x)=1+(x%q) con q primo < t
    int posicion_funcion1 = clave % tamf;
    int posicion_funcion2 = 1 + (clave % primo_inferior(tamf));

    int desplazamiento = intento + (intento * intento) * posicion_funcion2;
    int posicion_final = (posicion_funcion1 + desplazamiento) % tamf;

    if(posicion_final < 0) posicion_final += tamf;

    return posicion_final;
}

int ThashMedicam::primo_superior(int num) {
    bool esprimo=false;
    int aux=num+1;
    while(!esprimo){
        esprimo=true;
        for(int i=2;i<aux;i++){
            if(aux%i == 0){
                esprimo=false;
                break;
            }
        }
        aux++;
    }
    return aux-1;
}

int ThashMedicam::primo_inferior(int num) {
    bool esprimo= false;
    int aux=num-1;
    while (!esprimo){
        esprimo=true;
        for(int i=2;i<aux;i++){
            if(aux%i == 0){
                esprimo=false;
                break;
            }
        }
        aux--;
    }
    return aux+1;
}

bool ThashMedicam::insertar(int clave, PaMedicamento &pa) {
    bool esta=false;
    int intento=0;
    while(!esta) {
        //unsigned int pos= exploracion_cuadratica(clave,intento);
        //unsigned int pos= exploracion_doble1(clave,intento);
        unsigned int pos= exploracion_doble2(clave,intento);
        if (tabla[pos].marca == 'o') {
            if(tabla[pos].clave==clave){
                return false;
            }
            intento++;
        }else{
            tabla[pos].dato = pa;
            tabla[pos].clave = clave;
            tabla[pos].marca = 'o';
            taml++;
            if(intento>maxColisiones){
                maxColisiones=intento;
            }
            if(intento>10){
                max10++;
            }
            sumCol+=intento;
            return true;
        }
    }
    return false;
}

PaMedicamento* ThashMedicam::buscar(int clave) {
    bool encontrado=false;
    int intento=0;
    while(!encontrado){
        //unsigned int pos= exploracion_cuadratica(clave,intento);
        //unsigned int pos= exploracion_doble1(clave,intento);
        unsigned int pos= exploracion_doble2(clave,intento);
        if(tabla[pos].marca != 'v'){
            if(tabla[pos].clave == clave){
                return &tabla[pos].dato;
            }
            intento++;
        }else{
            return nullptr;
        }
    }
    return nullptr;
}

bool ThashMedicam::borrar(int clave) {
    bool encontrado=false;
    int intento=0;
    while(!encontrado){
        //unsigned int pos= exploracion_cuadratica(clave,intento);
        //unsigned int pos= exploracion_doble1(clave,intento);
        unsigned int pos= exploracion_doble2(clave,intento);
        if(tabla[pos].marca == 'o'){
            if(tabla[pos].clave == clave){
                tabla[pos].marca='d';
                taml--;
                return true;
            }
            intento++;
        }
    }
    return false;
}

int ThashMedicam::numElementos() {
    return taml;
}

int ThashMedicam::getTamf() const {
    return tamf;
}

void ThashMedicam::setTamf(int tamf) {
    ThashMedicam::tamf = tamf;
}

int ThashMedicam::getTaml() const {
    return taml;
}

void ThashMedicam::setTaml(int taml) {
    ThashMedicam::taml = taml;
}

int ThashMedicam::getMaxColisiones() const {
    return maxColisiones;
}

void ThashMedicam::setMaxColisiones(int maxColisiones) {
    ThashMedicam::maxColisiones = maxColisiones;
}

int ThashMedicam::getMax10() const {
    return max10;
}

void ThashMedicam::setMax10(int max10) {
    ThashMedicam::max10 = max10;
}

int ThashMedicam::getSumCol() const {
    return sumCol;
}

void ThashMedicam::setSumCol(int sumCol) {
    ThashMedicam::sumCol = sumCol;
}

float ThashMedicam::factorCarga() {
    float numerador=taml;
    float denominador=tamf;
    return numerador/denominador;
}

float ThashMedicam::promedioColisiones() {
    float numerador=sumCol;
    float denominador=taml;
    return numerador/denominador;
    //return (float)sumCol/(float)taml;
}



