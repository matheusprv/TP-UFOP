#ifndef CHEFE_H
#define CHEFE_H

#include "pessoa.h"
#include "funcionario.h"


using namespace std;

class Chefe : virtual public Pessoa{
    double salario;
    vector<Funcionario*> funcionarios;

public:
    // Chefe(const double & salario = 0.0, const string nome, const string login, const string senha) : Pessoa (nome, login, senha){};
    Chefe(const double & salario = 0.0, const string &nome = "");
    ~Chefe();

    vector<Funcionario*> getFuncionarios() const;
    void                 cadastrarFuncionarios();
    void                 listarFuncionarios();
    void                 checarPonto();
    void                 calcularSalario();
    double               getSalario();
    void                 setSalario(double salario);
    


};

#endif