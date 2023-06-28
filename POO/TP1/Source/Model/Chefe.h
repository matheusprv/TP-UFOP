#ifndef CHEFE_H
#define CHEFE_H

#include "Funcionario.h"
#include <string>
#include <vector>
using namespace std;

class Chefe : public Pessoa{
    vector<Funcionario*> funcionarios;
    double salario;
    
public:
    Chefe(string= "", Cadastro* = new Cadastro(), double = 0.0);
    virtual ~Chefe();
    double getSalario() const;
    void setSalario(double);
    void cadastrarFuncionario(Funcionario*);
    vector<Funcionario*> getFuncionarios() const;
    int getQtdFuncionarios();

    void listarFuncionarios() const;
};

#endif