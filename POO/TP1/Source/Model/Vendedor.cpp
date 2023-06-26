#include "Vendedor.h"

Vendedor::Vendedor(string nome, const Cadastro& cadastro, double salarioHora, double salarioTotal){
    //Funcionario(nome, cadastro, salarioHora, salarioTotal);
    setNome(nome);
    setCadastro(cadastro);
    setSalarioHora(salarioHora);
    setSalarioTotal(salarioTotal);
}

Vendedor::~Vendedor(){}

void Vendedor :: cadastrarVenda(Venda& venda){
    this->vendas.push_back(venda);
}

void Vendedor :: listarVendas(){
    for(auto it : vendas){
        cout << it;
    }
}

double Vendedor :: calcularBonificacao(){
    double bonificacao = 0.0;
    for(Venda v : vendas){
        bonificacao += 0.1 *(v.getValor() * v.getQuantidade());
    }
    return bonificacao;
}

void Vendedor :: serialize (ostream &out){
    Funcionario::serialize(out);

    out << "\nBonificação: R$" << calcularBonificacao() << endl;
}

ostream& operator<< (ostream& out, Vendedor& v){
    v.serialize(out);

    return out;
}