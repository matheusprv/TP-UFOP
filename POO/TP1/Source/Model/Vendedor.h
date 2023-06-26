#ifndef VENDEDOR_H
#define VENDEDOR_H


#include <iostream>
#include <vector>
#include "Funcionario.h"
#include "Venda.h"

using namespace std;

class Vendedor : public Funcionario{
    vector<Venda> vendas;
public:
    Vendedor(string="", const Cadastro& = Cadastro(), double=0, double=0);
    virtual ~Vendedor();

    void cadastrarVenda(Venda&);
    void listarVendas();
    double calcularBonificacao();

    void serialize (ostream&);
    friend ostream&  operator<<(ostream&, Vendedor&);
};

#endif
