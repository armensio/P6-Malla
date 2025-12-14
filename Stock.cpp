//
// Created by eduar on 04/11/2025.
//

#include "Stock.h"
#include <stdexcept>
using namespace std;

Stock::Stock() {

}

Stock::Stock(int idPaMed, int numStock) : id_PaMed(idPaMed), num_stock(numStock) {

}

Stock::Stock(const Stock &orig): id_PaMed(orig.id_PaMed), num_stock(orig.num_stock) {
    number=orig.number;
}

Stock::~Stock() {

}

int Stock::getIdPaMed() const {
    return id_PaMed;
}

void Stock::setIdPaMed(int idPaMed) {
    id_PaMed = idPaMed;
}

int Stock::getNumStock() const {
    return num_stock;
}

void Stock::setNumStock(int numStock) {
    num_stock = numStock;
}

PaMedicamento *Stock::getNumber() const {
    return number;
}

void Stock::setNumber(PaMedicamento *number) {
    Stock::number = number;
}

void Stock::decrementa(int n) {
    if(num_stock-n<0 || n<0){
        throw invalid_argument("[Stock::decrementa] No se puede decrementar esa cantidad de unidades");
    }
    num_stock-=n;
}

void Stock::incrementa(int n) {
    if(n<0){
        throw invalid_argument("[Stock::incrementa] No se puede incrementar esa cantidad de unidades");
    }
    num_stock+=n;
}

bool Stock::operator<(const Stock &rhs) const {
    return id_PaMed < rhs.id_PaMed;
}

