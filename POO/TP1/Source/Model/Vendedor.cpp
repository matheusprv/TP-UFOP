#include "Vendedor.h"

Vendedor::Vendedor(string nome, Cadastro* cadastro, double salarioHora, double salarioTotal):Funcionario(nome, cadastro, salarioHora, salarioTotal){}

Vendedor::~Vendedor(){}

void Vendedor :: cadastrarVenda(Venda* venda){
    this->vendas.push_back(*venda);
}

void Vendedor :: listarVendas(){
    for(auto it : vendas){
        cout << it;
    }
}

double Vendedor :: calculaVendas(){
    double valorVendas = 0.0;

    for(Venda v : vendas){
        valorVendas += (v.getValor() * v.getQuantidade());
    }

    return valorVendas;
}

double Vendedor :: calcularBonificacao(){
    return 0.1 * calculaVendas();
}

void Vendedor :: serialize (ostream &out){
    Funcionario::serialize(out);

    out << "\nBonificação: R$" << calcularBonificacao() << endl;
}

ostream& operator<< (ostream& out, Vendedor& v){
    v.serialize(out);

    return out;
}

vector<Venda> Vendedor :: getVendas(){
    return this->vendas;
}