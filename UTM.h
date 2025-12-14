//
// Created by eduar on 05/12/2025.
//

#ifndef P6_UTM_H
#define P6_UTM_H


class UTM {
private:
    float longitud=0;
    float latitud=0;
public:
    UTM();
    UTM(float longitud, float latitud);
    virtual ~UTM();

    float getLongitud() const;
    void setLongitud(float longitud);
    float getLatitud() const;
    void setLatitud(float latitud);
};


#endif //P6_UTM_H
