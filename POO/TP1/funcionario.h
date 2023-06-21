#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H


#include "pessoa.h"

using namespace std;

class Funcionario : virtual public Pessoa{
    double salarioHora;
    string funcao;
    //vector<Ponto> pontos;
public:
    Funcionario(const double &salarioHora = 0.0, const string &funcao = "", const string &nome = "", const string &login = "", const string &senha = "");
    ~Funcionario();

    void cadastrarPonto();
    void exibirSalario();
    string getFuncao() const;
    void setFuncao(string funcao);
    friend ostream& operator <<(ostream&, const Funcionario&);
};

#endif