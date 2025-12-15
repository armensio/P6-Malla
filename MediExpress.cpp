//
// Created by eduar on 14/10/2025.
//

#include "MediExpress.h"
#include <chrono>
#include <algorithm>
using namespace std;

MediExpress::MediExpress() {

}

MediExpress::MediExpress(const std::string &fichero_pamedicamentos, const std::string &fichero_laboratorios, const std::string &fichero_farmacias, const std::string &fichero_usuarios, int tam, float lambda) : idMedication(tam,lambda){

    std::ifstream is;
    std::stringstream columnas;
    std::string fila;
    int contador = 0;

    std::string id_number = "";
    std::string id_alpha = "";
    std::string nombre = "";

    list<PaMedicamento> lista_medicamentos;
    is.open(fichero_pamedicamentos); //carpeta de proyecto
    if (is.good()) {
        std::cout << endl << "Los 50 primeros medicamentos son: " << std::endl;
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, id_number, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, id_alpha, ';');
                getline(columnas, nombre, ';');

                PaMedicamento dato(stoi(id_number), id_alpha, nombre);

                idMedication.insertar(stoi(id_number),dato);

                id_medicamentosss.push_back(stoi(id_number));

                lista_medicamentos.push_back(dato);

                fila = "";
                columnas.clear();

                if (idMedication.numElementos() < 51) {
                    std::cout << ++contador
                              << " Medicamento: ( Id_number=" << id_number
                              << ")" << std::endl;
                }

            }
        }

        is.close();

    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    cout << endl << endl;
    //Busqueda de medicamentos en tabla hash
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<id_medicamentosss.size();i++){
        buscarCompuesto(id_medicamentosss[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Tiempo de búsqueda de medicamentos en tabla hash: " << duration.count() << " ms" << std::endl;

    // Busqueda de medicamentos en lista
    start = std::chrono::high_resolution_clock::now();
    list<PaMedicamento>::iterator i=lista_medicamentos.begin();
    while(i!=lista_medicamentos.end()){
        buscarCompuesto(i->getIdNum());
        i++;
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Tiempo de búsqueda de medicamentos en lista: " << duration.count() << " ms" << std::endl;


    // Creación de nombMedication
    for (int i = 0; i < id_medicamentosss.size(); i++) {
        PaMedicamento* medicamento = idMedication.buscar(id_medicamentosss[i]);
        stringstream s(medicamento->getNombre());
        string palabra;
        while (s >> palabra) {
            nombMedication.insert(make_pair(palabra, medicamento));
        }
    }

    cout << endl << endl;


    //Lectura de los laboratorios
    contador = 0;

    string id="";
    string nombreLab="";
    string direccion="";
    string codPostal="";
    string localidad="";


    is.open(fichero_laboratorios); //carpeta de proyecto
    if (is.good()) {
        std::cout << endl << endl << "Los 50 primeros laboratorios son: " << std::endl;
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, nombreLab, ';');
                getline(columnas, direccion, ';');
                getline(columnas, codPostal, ';');
                getline(columnas, localidad, ';');

                Laboratorio l(stoi(id), nombreLab, direccion,codPostal,localidad);
                labs.push_back(l);
                fila = "";
                columnas.clear();

                if (labs.size() < 51) {
                    std::cout << ++contador
                              << " Laboratorio: ( Id=" << id
                              << " Nombre=" << nombreLab
                              << " Direccion" << direccion
                              << " CodPostal" << codPostal
                              << " Localidad" << localidad
                              << ")" << std::endl;
                }

            }
        }

        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


    // Asigno los sobrantes a laboratorios de Madrid
    vector<Laboratorio *> madrid;
    madrid = buscarLabCiudad("Madrid");
    vector<PaMedicamento*> sin_labs=getMedicamentoSinLab();
    for(int i=0;i<sin_labs.size() && i<madrid.size();i++){
        sin_labs[i]->servidoPor(madrid[i]);
    }

    list<Laboratorio>::iterator j=labs.begin();
    //Enlace de medicamentos con laboratorios
    for(int i=0;i<id_medicamentosss.size() && j!=labs.end();i=i+2){
        buscarCompuesto(id_medicamentosss[i])->servidoPor(&(*j));
        buscarCompuesto(id_medicamentosss[i+1])->servidoPor(&(*j));
        j++;
    }

    //Cargo las farmacias
    contador = 0;

    std::string cif = "";
    std::string provincia = "";
    string cordx="";
    string cordy="";
    float xmax=0,xmin=10000,ymax=0,ymin=10000;

    is.open(fichero_farmacias); //carpeta de proyecto
    if (is.good()) {
        std::cout << endl << endl << "Las primeras 50 farmacias son: " << std::endl;
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, cif, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia, ';');
                getline(columnas, localidad, ';');
                getline(columnas, nombre, ';');
                getline(columnas, direccion, ';');
                getline(columnas, codPostal,';');
                getline(columnas, cordx,';');
                getline(columnas, cordy, '\r');

                UTM cordenadas(stof(cordx), stof(cordy));
                Farmacia f(cif,provincia,localidad,nombre,direccion,codPostal,cordenadas,this);
                pharmacy.insert(std::pair<string,Farmacia>(provincia,f));

                if(stof(cordx)<xmin){
                    xmin=stof(cordx);
                }
                if(stof(cordy)<ymin){
                    ymin=stof(cordy);
                }
                if(stof(cordx)>xmax){
                    xmax=stof(cordx);
                }
                if(stof(cordy)>ymax){
                    ymax=stof(cordy);
                }

                fila = "";
                columnas.clear();

                if (pharmacy.size() < 51) {
                    std::cout << ++contador
                              << " Farmacia: ( CIF=" << cif
                              << " Provincia= " << provincia
                              << " Localidad=" << localidad
                              << " Nombre=" << nombre
                              << " Direccion=" << direccion
                              << " CodPostal=" << codPostal
                              << ")" << std::endl;
                }

            }
        }

        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

    multimap<string,Farmacia>::iterator iter=pharmacy.begin();
    grid=MallaRegular<Farmacia*>(xmin-0.1,ymin-0.1,xmax+0.1,ymax+0.1,520);
    while(iter!=pharmacy.end()){
        grid.insertar(iter->second.getCoordenadas().getLongitud(),iter->second.getCoordenadas().getLatitud(),&iter->second);
        iter++;
    }

    cout << "Máximo de elementos por celda: " << grid.maxElementosPorCelda() << endl;
    cout << "Promedio de elementos por celda: " << grid.promedioElementosPorCelda() << endl;

    //LEO DE NUEVO LAS FARMACIAS

    vector<string> cifs;
    is.open(fichero_farmacias); //carpeta de proyecto
    if (is.good()) {
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, cif, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia, ';');
                getline(columnas, localidad, ';');
                getline(columnas, nombre, ';');
                getline(columnas, direccion, ';');
                getline(columnas, codPostal,';');
                getline(columnas, cordx,';');
                getline(columnas, cordy, '\r');

                cifs.push_back(cif);

                fila = "";
                columnas.clear();
            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }

// Asigno 100 medicamentos a cada farmacia que está en el vector de cofs
    int m=0;
    for(int i=0;i<cifs.size();i++){
        Farmacia *f= buscarFarmacia(cifs[i]);
        if(f){
            int c=0;
            while(c<100){
                PaMedicamento *medicamento= buscarCompuesto(id_medicamentosss[m]);
                f->nuevoStock(medicamento,10);

                c++;
                m++;
                if(m==id_medicamentosss.size()){
                    m=0;
                }
            }
        }
    }

    //LECTURA FICHERO USUARIOS
    is.open(fichero_usuarios); //carpeta de proyecto
    if (is.good()) {
        string coordx,coordy;
        while (getline(is, fila)) {

            //¿Se ha leído una nueva fila?
            if (fila != "") {

                columnas.str(fila);

                getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                getline(columnas, provincia, ';');
                getline(columnas, coordx, ';');
                getline(columnas, coordy, '\r');

                UTM coordenada(stof(coordx), stof(coordy));
                Usuario user(stoi(id),provincia,coordenada,this);
                users.insert(std::pair<int,Usuario>(stoi(id),user));

                fila = "";
                columnas.clear();
            }
        }
        is.close();
    } else {
        std::cout << "Error de apertura en archivo" << std::endl;
    }


}

MediExpress::~MediExpress() {

}

void MediExpress::suministrarMed(PaMedicamento *pa, Laboratorio *l) {
    pa->servidoPor(l);
}

Laboratorio* MediExpress::buscarLab(std::string nombreLab) {
    list<Laboratorio>::iterator i = labs.begin();
    while (i != labs.end()) {
        if (i->getNombreLab().find(nombreLab) != string::npos) {
            return &(*i);
        } else {
            i++;
        }
    }
    return nullptr;
}

vector<Laboratorio*> MediExpress::buscarLabCiudad(std::string nombreCiudad) {
    vector<Laboratorio*> laboratorios;
    list<Laboratorio>::iterator i=labs.begin();
    while(i!=labs.end()){
        if (i->getLocalidad().find(nombreCiudad) != string::npos) {
            laboratorios.push_back(&(*i));
        }
        i++;
    }
    return laboratorios;
}

vector<PaMedicamento*> MediExpress::buscarCompuesto(std::string nombrePA) {
     vector<PaMedicamento*> compuesto;

    vector<set<PaMedicamento*> > vector;
    std::stringstream separacion;
    string palabra;
    separacion.str(nombrePA);
    int i=0;
    while (getline(separacion, palabra, ' ')){
        set<PaMedicamento*> x;
        vector.push_back(x);
        multimap<string,PaMedicamento*>::iterator it= nombMedication.find(palabra);
        while (it!=nombMedication.end() && it->first==palabra){
            vector[i].insert(it->second);
            it++;
        }
        i++;
    }
    set<PaMedicamento*> a;
    set<PaMedicamento*> b;
    a=vector[0];
    for (int i = 1; i < vector.size(); i++) {
        set_intersection(vector[i].begin(), vector[i].end(), a.begin(), a.end(),
                         inserter(b, b.begin()));
        a=b;
        b.clear();
    }
    compuesto.insert(compuesto.begin(),a.begin(),a.end());
    return compuesto;
}

vector<PaMedicamento*> MediExpress::getMedicamentoSinLab() {
    vector<PaMedicamento*> medicamentos;
    for(int i=0;i<id_medicamentosss.size();i++){
        PaMedicamento *medicamento= buscarCompuesto(id_medicamentosss[i]);
        if(medicamento->getServe()== nullptr){
            medicamentos.push_back(medicamento);
        }
    }
    return medicamentos;
}

PaMedicamento* MediExpress::buscarCompuesto(int id_num) {
    return idMedication.buscar(id_num);
}

void MediExpress::suministrarFarmacia(Farmacia *f, int id_num, int n) {
    PaMedicamento *medicamento= buscarCompuesto(id_num);
    if(medicamento){
        f->nuevoStock(medicamento,n);
    }
}


Farmacia* MediExpress::buscarFarmacia(std::string cif) {
    multimap<string,Farmacia>::iterator i=pharmacy.begin();
    while(i!=pharmacy.end()){
        if(cif==i->second.getCif()){
            return &i->second;
        }
        i++;
    }
    return nullptr;
}

vector<Laboratorio*> MediExpress::buscarLabs(std::string nombrePA) {
    vector<Laboratorio*> v;
    for(int i=0;i<id_medicamentosss.size();i++){
        PaMedicamento *medicamento= buscarCompuesto(id_medicamentosss[i]);
        if(medicamento->getNombre().find(nombrePA)!= string::npos){
            if(medicamento->getServe()){
                v.push_back(medicamento->getServe());
            }
        }
    }
    return v;
}

vector<Farmacia*> MediExpress::buscarFarmacias(std::string provincia) {
    vector<Farmacia*> v;
    multimap<string,Farmacia>::iterator i=pharmacy.find(provincia);
    if(i!=pharmacy.end()){
        while(i->first==provincia) {
            v.push_back(&(*i).second);
            i++;
        }
    }
    return v;
}

bool MediExpress::eliminarMedicamento(int id_num) {
    bool eliminado=idMedication.borrar(id_num);
    multimap<string,Farmacia>::iterator i=pharmacy.begin();
    while(i!=pharmacy.end()){
        if(i->second.buscaMedicamId(id_num)>0){
            if (!i->second.eliminarStock(id_num)) {
                cerr << "[MediExpress::eliminarMedicameto] Error al intentar eliminar un medicamento del stock de una farmacia" << endl;
            }
        }
        i++;
    }
    if(eliminado){
        return true;
    }
    return false;
}

void MediExpress::mostrarEstadoTabla() {
    cout << "Lambda: 0.65" << endl;
    cout << "Factor de carga: " << idMedication.factorCarga() << endl;
    cout << "Tamaño físico de tabla: " << idMedication.getTamf() << endl;
    cout << "Tamaño lógico de tabla: " << idMedication.getTaml() << endl;
    cout << "Veces que han habido más de 10 colisiones:  " << idMedication.getMax10() << endl;
    cout << "El mayor número de colisiones ha sido: " << idMedication.getMaxColisiones() << endl;
    cout << "La media de colisiones por inserción es de: " << idMedication.promedioColisiones() << endl;
}

vector<Farmacia*> MediExpress::buscarFarmacias(UTM posicion, int n) {
    return grid.buscarCercana(posicion.getLongitud(),posicion.getLatitud(),n);
}

vector<Usuario*> MediExpress::buscarUsuarios(std::string provincia) {
    vector<Usuario*> resultado;
    map<int,Usuario>::iterator i=users.begin();
    while(i!=users.end()){
        if(i->second.getProvincia().find(provincia)!=string::npos){
            resultado.push_back(&i->second);
        }
        i++;
    }
    return resultado;
}
