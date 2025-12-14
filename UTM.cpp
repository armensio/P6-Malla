//
// Created by eduar on 05/12/2025.
//

#include "UTM.h"

UTM::UTM() {

}

UTM::UTM(float longitud, float latitud) : longitud(longitud), latitud(latitud) {

}

UTM::~UTM() {

}

float UTM::getLongitud() const {
    return longitud;
}

void UTM::setLongitud(float longitud) {
    UTM::longitud = longitud;
}

float UTM::getLatitud() const {
    return latitud;
}

void UTM::setLatitud(float latitud) {
    UTM::latitud = latitud;
}
