#include <iostream>
#include <string>
#include "PaMedicamento.h"
#include "MediExpress.h"

#include <list>
#include <vector>
using namespace std;

void mostrar_vector_labs(vector<Laboratorio*> vector, int cantidad_a_mostrar = UINT_MAX){
    int contador=0;
    if(cantidad_a_mostrar==UINT_MAX) {
        for (int i = 0; i < vector.size(); i++) {
            std::cout << ++contador
                      << " Laboratorio: ( Id=" << vector[i]->getId()
                      << " Nombre=" << vector[i]->getNombreLab()
                      << " Direccion" << vector[i]->getDireccion()
                      << " CodPostal" << vector[i]->getCodPostal()
                      << " Localidad" << vector[i]->getLocalidad()
                      << ")" << std::endl;
        }
    }else{
        for (int i = 0; i < cantidad_a_mostrar; i++) {
            std::cout << ++contador
                      << " Laboratorio: ( Id=" << vector[i]->getId()
                      << " Nombre=" << vector[i]->getNombreLab()
                      << " Direccion" << vector[i]->getDireccion()
                      << " CodPostal" << vector[i]->getCodPostal()
                      << " Localidad" << vector[i]->getLocalidad()
                      << ")" << std::endl;
        }
    }
}

void mostrar_farmacia(vector<Farmacia*> &vector){
    for(int i=0;i<100 && i<vector.size();i++){
            std::cout << i+1
                      << " Farmacia: ( CIF=" << vector[i]->getCif()
                      << " Provincia= " << vector[i]->getProvincia()
                      << " Localidad=" << vector[i]->getLocalidad()
                      << " Nombre=" << vector[i]->getNombre()
                      << " Direccion=" << vector[i]->getDireccion()
                      << " CodPostal=" << vector[i]->getCodPostal()
                      << ")" << std::endl;
    }
}


/**
 * @author Eduardo Calvo Almeida eca00028@red.ujaen.es
 */
int main() {
    try {
        MediExpress m("../pa_medicamentos.csv","../lab2.csv","../farmacias-coord.csv","../usuarios.csv",3310,0.65);
        cout << endl << endl;
        //m.mostrarEstadoTabla();


        // SEVILLA
        vector<Farmacia*> sevilla=m.buscarFarmacias("SEVILLA");
        PaMedicamento *pa;
        cout << endl << endl << endl;
        cout << "Farmacias en Sevilla: " << sevilla.size() << endl;
        int unidades;
        for(int i=0;i<sevilla.size();i++){
            for(int j=0;j<12;j++) {
                vector<PaMedicamento*> medicamentos2=sevilla[i]->buscaMedicamNombre("MAGNESIO");
                for(int k=0;k<medicamentos2.size();k++) {
                    unidades = sevilla[i]->comprarMedicam(medicamentos2[k]->getIdNum(), 1, pa);
                    cout << "En la farmacia " << sevilla[i]->getCif() << " hay " << unidades
                         << " unidades de " << medicamentos2[k]->getNombre() << endl;
                    if (unidades == 0) {
                        unidades = sevilla[i]->comprarMedicam(3640, 1, pa);
                        cout << "En la farmacia " << sevilla[i]->getCif() << " hay " << unidades
                             << " unidades de Oxido de magnesio" << endl;
                        if (unidades == 0) {
                            cout << "No hay ninguno de los medicamentos" << endl;
                        }
                    }
                }
            }
        }


        //vector<Farmacia*> jaen=m.buscarFarmacias("JAEN");
        //cout << "Farmacias en Jaen: " << jaen.size() << endl;
        //Esto es lo que debería poner pero no me coge ninguna farmacia, entonces he buscado a mano la única farmacia

        Farmacia *jaen=m.buscarFarmacia("E23319585");
        vector<PaMedicamento*> medicamentosMagnesio=jaen->buscaMedicamNombre("MAGNESIO CLORURO HEXAHIDRATO");




    }catch (exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}