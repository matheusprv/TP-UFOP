#include "funcionario.h"

Funcionario :: Funcionario(const double &salarioHora,const string &funcao, const string &nome) : Pessoa(nome){
    this-> salarioHora = salarioHora;
    this-> funcao = funcao;   
}

Funcionario :: ~Funcionario(){}

void Funcionario :: cadastrarPonto(){

}

void Funcionario :: exibirSalario(){

}

string Funcionario :: getFuncao() const{
    return this->funcao;
}

void Funcionario :: setFuncao(const string &funcao){
    
}

ostream& operator<<(ostream& out, const Funcionario& funcionario){
    out << serialize;
    return out;
}

