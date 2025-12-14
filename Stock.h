//
// Created by eduar on 04/11/2025.
//

#ifndef P4_STOCK_H
#define P4_STOCK_H
#include "PaMedicamento.h"

class Stock {
private:
    int id_PaMed=0;
    int num_stock=0;

    PaMedicamento *number=nullptr;

public:
    Stock();
    Stock(int idPaMed, int numStock);
    Stock(const Stock &orig);
    virtual ~Stock();

    int getIdPaMed() const;
    void setIdPaMed(int idPaMed);
    int getNumStock() const;
    void setNumStock(int numStock);
    PaMedicamento *getNumber() const;
    void setNumber(PaMedicamento *number);

    bool operator<(const Stock &rhs) const;

    void decrementa(int n);
    void incrementa(int n);
};


#endif //P4_STOCK_H
