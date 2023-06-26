#ifndef VENDA_H
#define VENDA_H

#include <iostream>

using namespace std;

class Venda{
    int id;
    double valor;
    int quantidade;
public:
    Venda(int id = 0, double valor = 0.0, int quandidade = 0);
    ~Venda();
    
    int getId() const;
    void setId(const int &);

    double getValor() const;
    void setValor(const double &);

    int getQuantidade() const;
    void setQuantidade(const int &);

    void serialize(ostream&) const;
    friend ostream& operator <<(ostream& out, const Venda &);
};

#endif