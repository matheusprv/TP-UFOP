#ifndef VENDEDOR_H
#define VENDEDOR_H

#include "venda.h"
#include "funcionario.h"

using namespace std;

class Vendedor : virtual public Funcionario{
    vector<Venda> vendas;

public:
    Vendedor();
    ~Vendedor();

    void cadastrarVenda(Venda venda);
    void listarVendas();

    void calcularSalario();
};

#endif