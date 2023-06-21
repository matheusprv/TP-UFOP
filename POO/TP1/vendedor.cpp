#include "vendedor.h"

Vendedor::Vendedor(const double &salarioHora,const string &funcao, const string &nome) : Funcionario(salarioHora, funcao, nome){}

Vendedor::~Vendedor(){}

void Vendedor :: cadastrarVenda(Venda venda){
    //parte comentada para adicionar ao menu
    /*Venda novaVenda;
    
    double valor;
    int quantidade;

    cin >> valor >> quantidade;

    novaVenda.setValor(valor);
    novaVenda.setQuantidade(quantidade);*/

    vendas.push_back(venda);
}

void Vendedor :: listarVendas(){

}

void Vendedor :: calcularSalario(){
 //calcular o salario e setar o salario total a partir dele
}