#ifndef SUPERVISOR_H
#define SUPERVISOR_H


#include <iostream>
#include <vector>
#include "Funcionario.h"
#include "Venda.h"
#include "Vendedor.h"

using namespace std;

class Supervisor : public Funcionario{
    vector<Vendedor> vendedores;
public:
    Supervisor(string="", const Cadastro& = Cadastro(), double=0.0, double=0.0);
    virtual ~Supervisor();

    void cadastrarVendedor(const Vendedor&);
    void listarVendedores();
    void listarVendas();
    double calcularBonificacao();

    void serialize(ostream&);
    friend ostream& operator<<(ostream&, Supervisor&);
};

#endif