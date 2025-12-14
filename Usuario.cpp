//
// Created by eduar on 05/12/2025.
//

#include "Usuario.h"
#include "MediExpress.h"

Usuario::Usuario() {

}

Usuario::Usuario(int id, const string &provincia, const UTM &coord, MediExpress *linkUser) : id(id), provincia(provincia), coord(coord), linkUser(linkUser){
    //linkUser=linkUser;
}

Usuario::~Usuario() {

}

int Usuario::getId() const {
    return id;
}

void Usuario::setId(int id) {
    Usuario::id = id;
}

const string &Usuario::getProvincia() const {
    return provincia;
}

void Usuario::setProvincia(const string &provincia) {
    Usuario::provincia = provincia;
}

const UTM &Usuario::getCoord() const {
    return coord;
}

void Usuario::setCoord(const UTM &coord) {
    Usuario::coord = coord;
}

vector<Farmacia*> Usuario::getFarmaciaCercana(int n) {
    if(linkUser!= nullptr){
        vector<Farmacia*> cercanas;
        cercanas=linkUser->buscarFarmacias(coord,n);
        return cercanas;
    }
}

vector<PaMedicamento*> Usuario::quieroMedicam(std::string nombre, Farmacia f) {
    f.comprarMedicam(f.buscaMedicamNombre(nombre)[0]->getIdNum(),1,f.buscaMedicamNombre(nombre)[0]);
}

int Usuario::comprarMedicam(int n, PaMedicamento pa, Farmacia f) {
    return f.comprarMedicam(pa.getIdNum(),n,&pa);
}
