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
        MediExpress m("../pa_medicamentos.csv","../lab2.csv","../prueba.csv","../usuarios.csv",3310,0.65);
        cout << endl << endl;

        Farmacia *ubeda=m.buscarFarmacia("E23319585");


        m.suministrarFarmacia(ubeda,10904,10);
        m.suministrarFarmacia(ubeda,5551,10);
        m.suministrarFarmacia(ubeda,6283,10);
        vector<Usuario*> jaen;
        jaen=m.buscarUsuarios("Jaen");
        int contador=0;
        vector<PaMedicamento*> medicamentos;
        vector<Farmacia*> cercana;
        for(int i=0;i<jaen.size();i++){
            if((contador%3) == 0) {
                medicamentos=jaen[i]->quieroMedicam("MAGNESIO CLORURO HEXAHIDRATO", ubeda);
                if(!medicamentos.empty()){
                    cout << "Quedan " << jaen[i]->comprarMedicam(1,medicamentos[0],ubeda) << " " << medicamentos[0]->getNombre() << endl; //" Magnesios" << endl;
                    cout << "El usuario " << jaen[i]->getId() << " va a comprar 1 " << medicamentos[0]->getNombre() << endl;
                }else{
                    cout << "No hay magnesio en ubeda" << endl;
                }
            }
            if((contador%3) == 1) {
                medicamentos=jaen[i]->quieroMedicam("LIDOCAINA HIDROCLORURO", ubeda);
                if(!medicamentos.empty()){
                    cout << "Quedan " << jaen[i]->comprarMedicam(1,medicamentos[0],ubeda) << " " << medicamentos[0]->getNombre() << endl; //" Lidocainas" << endl;
                    cout << "El usuario " << jaen[i]->getId() << " va a comprar 1 " << medicamentos[0]->getNombre() << endl;
                }else{
                    cout << "No hay lidocaina en ubeda" << endl;
                }
            }
            if((contador%3) == 2) {
                medicamentos=jaen[i]->quieroMedicam("MENTA PIPERITA", ubeda);
                if(!medicamentos.empty()){
                    cout << "Quedan " << jaen[i]->comprarMedicam(1,medicamentos[0],ubeda) << " " << medicamentos[0]->getNombre() << endl;//" Mentas" << endl;
                    cout << "El usuario " << jaen[i]->getId() << " va a comprar 1 " << medicamentos[0]->getNombre() << endl;
                }else{
                    cout << "No hay menta en ubeda" << endl;
                }
            }


            cercana=jaen[i]->getFarmaciaCercana(1);
            if(cercana[0]->getLocalidad()=="UBEDA"){
                cout << "La farmacia más cercana al usuario " << jaen[i]->getId() << " es la de Úbeda" << endl;
            }
            contador++;
        }



        vector<Usuario*> sevilla=m.buscarUsuarios("Sevilla");
        vector<Farmacia*> cercana2;
        vector<PaMedicamento*> medicamentos2;
        int unidades=0;
        for(int i=0;i<sevilla.size();i++){
            cercana2=sevilla[i]->getFarmaciaCercana(1);
            m.suministrarFarmacia(cercana2[0],3629,10);
            medicamentos2=sevilla[i]->quieroMedicam("MAGNESIO",cercana2[0]);
            unidades=sevilla[i]->comprarMedicam(1,medicamentos2[0],cercana2[0]);
            cout << "Quedan " << unidades << medicamentos2[0]->getNombre() << endl;
            cout << "El usuario " << sevilla[i]->getId() << " va a comprar 1 " << medicamentos2[0]->getNombre() << " en la farmacia de Úbeda" << endl;
            if(unidades==0){
                cout << "Se han pedido 10 unidades de " << medicamentos2[0] << endl;
            }
        }

        vector<Farmacia*> farmacias_madrid=m.buscarFarmacias("MADRID");
        vector<PaMedicamento*> bismutos;
        vector<Usuario*> usuarios_madrid=m.buscarUsuarios("Madrid");
        vector<Farmacia*> cercana3;
        for(int i=0;i<farmacias_madrid.size();i++){
            m.suministrarFarmacia(farmacias_madrid[i],6847,10);
            bismutos=farmacias_madrid[i]->buscaMedicamNombre("BISMUTO");
            for(int j=0;j<usuarios_madrid.size();j++){
               cercana3=usuarios_madrid[j]->getFarmaciaCercana(3);
               if(cercana3[0]->getCif()==farmacias_madrid[i]->getCif() || cercana3[1]->getCif()==farmacias_madrid[i]->getCif() || cercana3[2]->getCif()==farmacias_madrid[i]->getCif()){
                   usuarios_madrid[j]->comprarMedicam(1,bismutos[0],farmacias_madrid[i]);
                   cout << "La farmacia " << farmacias_madrid[i]->getNombre() << " es una de las 3 mas cercanas del usuario " << usuarios_madrid[j]->getId() << endl;
               }
            }
            for(int k=0;k<bismutos.size();k++){
                farmacias_madrid[i]->eliminarStock(bismutos[k]->getIdNum());
            }
            if(farmacias_madrid[i]->buscaMedicamNombre("BISMUTO").empty()){
                cout << "Se ha eliminado correctamente los bismutos de la farmacia " << farmacias_madrid[i]->getNombre() << endl;
            }
        }


    }catch (exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}