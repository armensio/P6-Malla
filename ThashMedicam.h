//
// Created by eduar on 22/11/2025.
//

#ifndef P5_THASHMEDICAM_H
#define P5_THASHMEDICAM_H
#include "PaMedicamento.h"
#include <vector>

class ThashMedicam {
private:
    class Entrada {
    public:
        PaMedicamento dato;
        unsigned long clave;
        char marca;  //v(vacias), o(ocupada), d(disponible)

        Entrada(): dato(), clave(0), marca('v'){}
        ~Entrada(){};
    };
    int tamf=3400,taml=0,maxColisiones=0,max10=0,sumCol=0;
    vector<Entrada> tabla;
    int exploracion_cuadratica(int clave, int intento);
    int exploracion_doble1(int clave, int intento);
    int exploracion_doble2(int clave, int intento);

    int primo_superior(int num);
    int primo_inferior(int num);

public:
    ThashMedicam();
    ThashMedicam(int maxElementos, float lambda=0.7);
    ThashMedicam(const ThashMedicam &orig);

    virtual ~ThashMedicam();
    bool insertar(int clave, PaMedicamento &pa);
    PaMedicamento* buscar(int clave);
    bool borrar(int clave);
    int numElementos();

    int getTamf() const;
    void setTamf(int tamf);
    int getTaml() const;
    void setTaml(int taml);
    int getMaxColisiones() const;
    void setMaxColisiones(int maxColisiones);
    int getMax10() const;
    void setMax10(int max10);
    int getSumCol() const;
    void setSumCol(int sumCol);
    float factorCarga();
    float promedioColisiones();
};


#endif //P5_THASHMEDICAM_H
