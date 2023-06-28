#include "Chefe.h"
#include "Supervisor.h"
#include "Vendedor.h"
#include <typeinfo>

Chefe :: Chefe(string nome, Cadastro * cadastro, double salario):Pessoa(nome, cadastro){
    this->salario = salario;
}

Chefe :: ~Chefe(){
    //Deletando todos os funcionarios
    for(Funcionario * func : this->getFuncionarios()){
        delete func;
    }
}

double Chefe :: getSalario() const{
    return salario;
}

void Chefe :: setSalario(double salario){
    this->salario = salario;
}

void Chefe :: cadastrarFuncionario(Funcionario* funcionario){
    funcionarios.push_back(funcionario);
}

vector<Funcionario*> Chefe :: getFuncionarios() const{
    return funcionarios;
}

int Chefe :: getQtdFuncionarios(){
    return funcionarios.size();
}

void Chefe :: listarFuncionarios () const{
    
    if(funcionarios.size()==0){
        cout << "Nenhum funcionário cadastrado\n" << endl;
        return;
    }

    cout << "==============================\n";

    Supervisor * supervisorTemp;
    Vendedor * vendedorTemp;

    //Iterando pela lista de funcionarios
    for(Funcionario * func : funcionarios){

        //Estou apontando para uma classe de supervisor? 
        if(typeid(*func) == typeid(class Supervisor)){
            supervisorTemp = dynamic_cast<Supervisor*>(func);
            cout << *supervisorTemp;
        }
        //Estou apontando para uma classe de vendedor?
        else{
            vendedorTemp = dynamic_cast<Vendedor*>(func);
            cout << *vendedorTemp;
        }

        cout << "==============================\n";
    }

    cout << "\n";
}

