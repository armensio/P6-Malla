//
// Created by eduar on 14/10/2025.
//

#ifndef P1_LABORATORIO_H
#define P1_LABORATORIO_H
#include <string>
using namespace std;

class Laboratorio {
private:
    int id=0;
    string nombreLab="";
    string direccion="";
    string codPostal="";
    string localidad="";
public:
    Laboratorio();
    Laboratorio(int id, const string &nombreLab, const string &direccion, const string &codPostal,
                const string &localidad);
    Laboratorio(const Laboratorio &orig);
    virtual ~Laboratorio();

    int getId() const;
    void setId(int id);
    const string &getNombreLab() const;
    void setNombreLab(const string &nombreLab);
    const string &getDireccion() const;
    void setDireccion(const string &direccion);
    const string &getCodPostal() const;
    void setCodPostal(const string &codPostal);
    const string &getLocalidad() const;
    void setLocalidad(const string &localidad);
};


#endif //P1_LABORATORIO_H
