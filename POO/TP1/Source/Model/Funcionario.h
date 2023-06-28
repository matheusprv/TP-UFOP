#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include "Pessoa.h"
#include "Ponto.h"
#include <vector>

class Funcionario : public Pessoa{
    double salarioHora;
    double salarioTotal;
    vector<Ponto> pontos;
    vector<int> minutosTrabalhados;
    
public:
    Funcionario(string="",  Cadastro* = new Cadastro(), double=0, double=0);
    virtual ~Funcionario();

    double getSalarioHora() const;
    void setSalarioHora(double);

    double getSalarioTotal() const;
    void setSalarioTotal(double);

    void registrarPonto(Ponto*);
    vector<Ponto> getPontos() const;

    //funcao abstrata, sera utilizada para o polimorfismo
    virtual void listarVendas() = 0;
    virtual double calcularBonificacao() = 0;

    void serialize(ostream&) const;
};

#endif