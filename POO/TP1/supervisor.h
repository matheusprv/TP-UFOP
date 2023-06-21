#ifndef SUPERVISOR_H
#define SUPERVISOR_H


#include "funcionario.h"
#include "vendedor.h"

using namespace std;

class Supervisor : virtual public Funcionario{
    vector<Vendedor> vendedores;
public:
    Supervisor();
    ~Supervisor();
    
    void listarVendedores();
    void listarVendas();
    double calcularSalario();
};


#endif