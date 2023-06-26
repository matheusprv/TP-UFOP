#include "Chefe.h"
#include "Supervisor.h"
#include "Vendedor.h"
#include <typeinfo>

Chefe :: Chefe(string nome, const Cadastro cadastro, double salario){
    Pessoa(nome, cadastro);
    this->salario = salario;
}

Chefe :: ~Chefe(){
    //Deletando todos os funcionarios
    // for(Funcionario * func : this->getFuncionarios()){
    //     delete func;
    // }
}

double Chefe :: getSalario() const{
    return salario;
}

void Chefe :: setSalario(double salario){
    this->salario = salario;
}

void Chefe :: cadastrarFuncionario(Funcionario& funcionario){
    funcionarios.push_back(&funcionario);
}

vector<Funcionario*> Chefe :: getFuncionarios() const{
    return funcionarios;
}

void Chefe :: listarFuncionarios () const{
    Supervisor * supervisorTemp;
    Vendedor * vendedorTemp;

    //Iterando pela lista de funcionarios
    for(Funcionario * func : this->getFuncionarios()){

        //Estou apontando para uma classe de supervisor? 
        if(typeid(*func) == typeid(class Supervisor)){
            supervisorTemp = dynamic_cast<Supervisor*>(func);
            cout << *supervisorTemp;
        }
        //Estou apontando para uma classe de vendedor?
        //else if(typeid(*func) == typeid(class Vendedor)){
        else{
            vendedorTemp = dynamic_cast<Vendedor*>(func);
            cout << *vendedorTemp;
        }

        cout << "==============================\n";

    }
}

