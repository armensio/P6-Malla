//
// Created by eduar on 05/12/2025.
//

#ifndef P6_USUARIO_H
#define P6_USUARIO_H
#include "UTM.h"
#include "Farmacia.h" //
#include <string>
using namespace std;

class Usuario {
private:
    int id=0;
    string provincia;
    UTM coord;
    MediExpress *linkUser= nullptr;

public:
    Usuario();
    Usuario(int id, const string &provincia, const UTM &coord, MediExpress *linkUser);
    virtual ~Usuario();

    int getId() const;
    void setId(int id);
    const string &getProvincia() const;
    void setProvincia(const string &provincia);
    const UTM &getCoord() const;
    void setCoord(const UTM &coord);

    vector<Farmacia*> getFarmaciaCercana(int n); //REVISAR
    vector<PaMedicamento*> quieroMedicam(string nombre,Farmacia *f); //Hecha mal?
    int comprarMedicam(int n,PaMedicamento *pa, Farmacia *f); //REVISAR
};


#endif //P6_USUARIO_H
