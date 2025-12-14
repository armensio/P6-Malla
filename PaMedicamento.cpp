//
// Created by eduar on 28/09/2025.
//

#include "PaMedicamento.h"

/**
 * Constructor por defecto
 */
PaMedicamento::PaMedicamento() {

}

/**
 * Constructor parametrizado
 * @param id_num El valor del id_num
 * @param id_alpha El valor de id_alpha
 * @param nombre El valor del nombre
 */
PaMedicamento::PaMedicamento(int id_num, string id_alpha, string nombre): id_num(id_num),id_alpha(id_alpha),nombre(nombre) {

}

/**
 * El constructor de copia
 * @param orig El medicamento que se quiere copiar
 */
PaMedicamento::PaMedicamento(const PaMedicamento &orig): id_num(orig.id_num), id_alpha(orig.id_alpha),nombre(orig.nombre) {

}

/**
 * Destructor
 */
PaMedicamento::~PaMedicamento() {

}

/**
 * Obtener el valor del id_num
 * @return El id_num
 */
int PaMedicamento::getIdNum() const {
    return id_num;
}

/**
 * Cambia el valor de id_num
 * @param idNum El valor que va a tener el parámetro
 */
void PaMedicamento::setIdNum(int idNum) {
    id_num = idNum;
}

/**
 * Obtener el valor del id_alpha
 * @return El valor de id_alpha
 */
const string &PaMedicamento::getIdAlpha() const {
    return id_alpha;
}

/**
 * Cambia el valor de id_alpha
 * @param idAlpha El valor que va a tener el parámetro
 */
void PaMedicamento::setIdAlpha(const string &idAlpha) {
    id_alpha = idAlpha;
}

/**
 * Obtener el valor del nombre
 * @return El valor de nombre
 */
const string &PaMedicamento::getNombre() const {
    return nombre;
}

/**
 * Cambia el valor del nombre
 * @param nombre El valor que va a tener el nombre
 */
void PaMedicamento::setNombre(const string &nombre) {
    PaMedicamento::nombre = nombre;
}

/**
 * Define el operador menor para que se ordenen los medicamentos teniendo en cuenta solo los identificadores
 * @param rhs Uno de los medicamentos que se va ha comparar
 * @return True si el primero es menor que segundo o False si ocurre lo contrario
 */
bool PaMedicamento::operator<(const PaMedicamento &rhs) const {
    if (id_num < rhs.id_num)
        return true;
    return false;
}

void PaMedicamento::servidoPor(Laboratorio *l) {
    /*
    if(serve!= nullptr) {
        delete serve;
    }*/
    serve = l;
}

Laboratorio *PaMedicamento::getServe() const {
    return serve;
}
