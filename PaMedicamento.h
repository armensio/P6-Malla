//
// Created by eduar on 28/09/2025.
//

#ifndef PROGRAMACION_PAMEDICAMENTO_H
#define PROGRAMACION_PAMEDICAMENTO_H
#include <string>
#include "Laboratorio.h"

using namespace std;

class PaMedicamento {
private:
    int id_num=0;
    string id_alpha="";
    string nombre="";

    Laboratorio *serve= nullptr;

public:
    PaMedicamento();
    PaMedicamento(int id_num, string id_alpha, string nombre);
    PaMedicamento(const PaMedicamento &orig);
    virtual ~PaMedicamento();

    int getIdNum() const;
    void setIdNum(int idNum);
    const string &getIdAlpha() const;
    void setIdAlpha(const string &idAlpha);
    const string &getNombre() const;
    void setNombre(const string &nombre);
    bool operator<(const PaMedicamento &rhs) const;

    Laboratorio* getServe() const;

    void servidoPor(Laboratorio *l);
};


#endif //PROGRAMACION_PAMEDICAMENTO_H
