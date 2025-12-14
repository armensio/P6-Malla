//
// Created by eduar on 25/10/2025.
//

#ifndef P3_FARMACIA_H
#define P3_FARMACIA_H
#include "PaMedicamento.h"
#include <string>
#include "Stock.h"
#include <set>
#include <map>
#include <vector>
#include "UTM.h"
using namespace std;

class MediExpress;

class Farmacia {
private:
    string cif="";
    string provincia="";
    string localidad="";
    string nombre="";
    string direccion="";
    string codPostal="";
    MediExpress *linkMedi=nullptr;
    map<int,Stock> order;
    UTM coordenadas;

    void pedidoMedicam(int id_num,int n);
    void pedidoMedicam(string nombre, int n); //Rarete

public:
    Farmacia();

    Farmacia(const string &cif, const string &provincia, const string &localidad, const string &nombre,
             const string &direccion, const string &codPostal, const UTM& cordenadas, MediExpress *linkMedi= nullptr);

    virtual ~Farmacia();
    const string &getCif() const;
    void setCif(const string &cif);
    const string &getProvincia() const;
    void setProvincia(const string &provincia);
    const string &getLocalidad() const;
    void setLocalidad(const string &localidad);
    const string &getNombre() const;
    void setNombre(const string &nombre);
    const string &getDireccion() const;
    void setDireccion(const string &direccion);
    const string &getCodPostal() const;
    void setCodPostal(const string &codPostal);

    const UTM &getCoordenadas() const;


    bool operator<(const Farmacia &rhs) const;
    bool operator>(const Farmacia &rhs) const;
    bool operator==(const Farmacia &rhs) const;

    int buscaMedicamId(int id_num);
    vector<PaMedicamento*> buscaMedicamNombre(string nombre);
    void nuevoStock(PaMedicamento *pa, int n);
    int comprarMedicam(int id_num, int n, PaMedicamento *result);
    bool eliminarStock(int id_num);

};


#endif //P3_FARMACIA_H
