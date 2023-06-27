#ifndef VENDA_H
#define VENDA_H

#include <iostream>
using namespace std;

class Venda{
    int id;
    double valor;
    int quantidade;

public: 
    Venda(double = 0.0, int = 0);
    virtual ~Venda();

    int getId() const;
    double getValor() const;
    int getQuantidade() const;

    void setId(int);
    void setValor(double);
    void setQuantidade(int);

    void serialize(ostream&) const;
    friend ostream& operator<<(ostream&, const Venda&);
};

#endif