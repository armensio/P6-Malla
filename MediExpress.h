//
// Created by eduar on 14/10/2025.
//

#ifndef P1_MEDIEXPRESS_H
#define P1_MEDIEXPRESS_H
#include "Laboratorio.h"
#include "PaMedicamento.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "Farmacia.h"
#include "ThashMedicam.h"
#include "Usuario.h"
#include "MallaRegular.h"

#include <list>
#include <vector>
#include <map>
#include <string>
using namespace std;

class MediExpress {
private:
    list<Laboratorio> labs;
    multimap<string,Farmacia> pharmacy;
    ThashMedicam idMedication;
    multimap<string,PaMedicamento*> nombMedication;
    vector<int> id_medicamentosss;
    map<int,Usuario> users; //NUEVO
    MallaRegular<Farmacia*> grid;

public:
    MediExpress();
    MediExpress(const string &fichero_pamedicamentos,const string &fichero_laboratorios,const string &fichero_farmacias,const std::string &fichero_usuarios,int tam,float lambda);
    ~MediExpress();

    void suministrarMed(PaMedicamento *pa,Laboratorio *l);
    Laboratorio* buscarLab(string nombreLab);
    vector<Laboratorio*> buscarLabCiudad(string nombreCiudad);
    vector<PaMedicamento*> buscarCompuesto(string nombrePA);
    vector<PaMedicamento*> getMedicamentoSinLab();

    PaMedicamento* buscarCompuesto(int id_num);
    void suministrarFarmacia(Farmacia *f, int id_num, int n);
    Farmacia* buscarFarmacia(string cif);
    vector<Laboratorio*> buscarLabs(string nombrePA);

    vector<Farmacia*> buscarFarmacias(string provincia);
    bool eliminarMedicamento(int id_num);

    void mostrarEstadoTabla();

    vector<Farmacia*> buscarFarmacias(UTM posicion,int n);

    vector<Usuario*> buscarUsuarios(string provincia);
};


#endif //P1_MEDIEXPRESS_H
