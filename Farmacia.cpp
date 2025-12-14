//
// Created by eduar on 25/10/2025.
//

#include "Farmacia.h"
#include "MediExpress.h"

Farmacia::Farmacia() {

}

Farmacia::Farmacia(const string &cif, const string &provincia, const string &localidad, const string &nombre,
                   const string &direccion, const string &codPostal, const UTM& cordenadas, MediExpress *linkMedi) : cif(cif), provincia(provincia), localidad(localidad),
                                                               nombre(nombre), direccion(direccion),
                                                               codPostal(codPostal), coordenadas(cordenadas), linkMedi(linkMedi){

}

Farmacia::~Farmacia() {

}

const string &Farmacia::getCif() const {
    return cif;
}

void Farmacia::setCif(const string &cif) {
    Farmacia::cif = cif;
}

const string &Farmacia::getProvincia() const {
    return provincia;
}

void Farmacia::setProvincia(const string &provincia) {
    Farmacia::provincia = provincia;
}

const string &Farmacia::getLocalidad() const {
    return localidad;
}

void Farmacia::setLocalidad(const string &localidad) {
    Farmacia::localidad = localidad;
}

const string &Farmacia::getNombre() const {
    return nombre;
}

void Farmacia::setNombre(const string &nombre) {
    Farmacia::nombre = nombre;
}

const string &Farmacia::getDireccion() const {
    return direccion;
}

void Farmacia::setDireccion(const string &direccion) {
    Farmacia::direccion = direccion;
}

const string &Farmacia::getCodPostal() const {
    return codPostal;
}

void Farmacia::setCodPostal(const string &codPostal) {
    Farmacia::codPostal = codPostal;
}

bool Farmacia::operator<(const Farmacia &rhs) const {
    if (cif < rhs.cif){
        return true;
    }else {
        return false;
    }
}

bool Farmacia::operator>(const Farmacia &rhs) const {
    if (cif > rhs.cif){
        return true;
    }else {
        return false;
    }
}

bool Farmacia::operator==(const Farmacia &rhs) const {
    return cif == rhs.cif;
}

void Farmacia::pedidoMedicam(int id_num, int n) {
    if(linkMedi) {
        linkMedi->suministrarFarmacia(this, id_num,n);
    }
}

void Farmacia::pedidoMedicam(string nombre, int n) {
    if(linkMedi) {
        vector<PaMedicamento*> medicamentos;
        medicamentos=linkMedi->buscarCompuesto(nombre);
        for (int i = 0; i < medicamentos.size(); i++) {
            linkMedi->suministrarFarmacia(this, medicamentos[i]->getIdNum(), n);
        }
    }
}

int Farmacia::buscaMedicamId(int id_num) {
    map<int,Stock>::iterator i=order.begin();
    Stock s(id_num,0);
    i=order.find(id_num);
    if(i!=order.end()){
        return i->second.getNumStock();
    }
    return 0;
}

vector<PaMedicamento*> Farmacia::buscaMedicamNombre(std::string nombre) {
    vector<PaMedicamento*> v;
    map<int,Stock>::iterator i=order.begin();
    while(i!=order.end()){
        if(i->second.getNumber()->getNombre().find(nombre)!=string::npos){
            v.push_back(i->second.getNumber());
        }
        i++;
    }
    return v;
}

void Farmacia::nuevoStock(PaMedicamento *pa, int n) {
    bool esta=false;
    if(!order.empty()){
        map<int,Stock>::iterator i=order.begin();
        while(i!=order.end() && !esta){
            if(pa->getIdNum()==i->second.getIdPaMed()){
                esta=true;
                Stock copia=i->second;
                copia.incrementa(n);
                order.erase(i);
                order.insert(std::pair<int, Stock>(copia.getIdPaMed(),copia));
            }
            i++;
        }
    }
    if(!esta){
        Stock s(pa->getIdNum(),n);
        s.setNumber(pa);
        order.insert(std::pair<int,Stock>(s.getIdPaMed(),s));
    }
}

int Farmacia::comprarMedicam(int id_num, int n, PaMedicamento *result) {
    if(!order.empty()) {
        if(buscaMedicamId(id_num)>=n){
            Stock s(id_num,0);
            map<int,Stock>::iterator i = order.find(id_num);
            result=order.find(id_num)->second.getNumber();
            Stock copia=i->second;
            copia.decrementa(n);
            order.erase(id_num);
            order.insert(std::pair<int,Stock>(copia.getIdPaMed(),copia));
        }else{
            pedidoMedicam(id_num,10);
        }
        return buscaMedicamId(id_num);
    }else{
        return 0;
    }
}

bool Farmacia::eliminarStock(int id_num) {
    if(!order.empty()){
        Stock s(id_num,0);
        int elementos_borrados=order.erase(id_num);
        if(elementos_borrados==1){
            return true;
        }
        return false;
    }else{
        return false;
    }
}

const UTM &Farmacia::getCoordenadas() const {
    return coordenadas;
}


