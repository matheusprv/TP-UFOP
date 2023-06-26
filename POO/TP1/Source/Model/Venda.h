#ifndef VENDA_H
#define VENDA_H

#include <iostream>
using namespace std;

class Venda{
    
    int id;
    double valor;
    int quantidade;

public: 
    Venda(double valor = 0.0, int quantidade = 0);
    virtual ~Venda();

    int getId() const;
    double getValor() const;
    int getQuantidade() const;

    void setId(int id);
    void setValor(double Valor);
    void setQuantidade(int quantidade);

    void serialize(ostream&) const;
    friend ostream& operator<<(ostream& out, const Venda & obj);

};

#endif