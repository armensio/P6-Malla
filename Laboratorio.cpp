//
// Created by eduar on 14/10/2025.
//

#include "Laboratorio.h"

Laboratorio::Laboratorio() {

}

Laboratorio::Laboratorio(int id, const string &nombreLab, const string &direccion, const string &codPostal,
                         const string &localidad) : id(id), nombreLab(nombreLab), direccion(direccion),
                                                    codPostal(codPostal), localidad(localidad) {

}

Laboratorio::Laboratorio(const Laboratorio &orig):id(orig.id),nombreLab(orig.nombreLab),direccion(orig.direccion),
                                                    codPostal(orig.codPostal),localidad(orig.localidad){

}

Laboratorio::~Laboratorio() {

}

int Laboratorio::getId() const {
    return id;
}

void Laboratorio::setId(int id) {
    Laboratorio::id = id;
}

const string &Laboratorio::getNombreLab() const {
    return nombreLab;
}

void Laboratorio::setNombreLab(const string &nombreLab) {
    Laboratorio::nombreLab = nombreLab;
}

const string &Laboratorio::getDireccion() const {
    return direccion;
}

void Laboratorio::setDireccion(const string &direccion) {
    Laboratorio::direccion = direccion;
}

const string &Laboratorio::getCodPostal() const {
    return codPostal;
}

void Laboratorio::setCodPostal(const string &codPostal) {
    Laboratorio::codPostal = codPostal;
}

const string &Laboratorio::getLocalidad() const {
    return localidad;
}

void Laboratorio::setLocalidad(const string &localidad) {
    Laboratorio::localidad = localidad;
}

