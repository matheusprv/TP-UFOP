#include "chefe.h"
#include "pessoa.h"

Chefe :: Chefe(const double & salario, const string &nome) : Pessoa(nome){
    this -> salario = salario;
}

Chefe :: ~Chefe(){
    vector<Funcionario*> funcionarios = getFuncionarios();

    for(Funcionario *func : funcionarios){
        free(func);
    }
}

vector<Funcionario*> Chefe :: getFuncionarios() const{
    return this -> funcionarios;
}

void cadastrarFuncionario(){

}

void listarFuncionarios(){
    vector<Funcionario*> funcs = getFuncionarios();

    for(Funcionario *func : funcs){
        cout << func;
    }

}

void checarPonto(){
    vector<Funcionario*> funcs = getFuncionarios();
}