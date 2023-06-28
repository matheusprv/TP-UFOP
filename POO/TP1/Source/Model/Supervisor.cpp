#include "Supervisor.h"

Supervisor :: Supervisor(string nome, Cadastro * cadastro, double salarioHora, double salarioTotal):Funcionario(nome, cadastro, salarioHora, salarioTotal){
    vendedores.resize(0);
}

Supervisor :: ~Supervisor(){}

void Supervisor :: cadastrarVendedor(Vendedor * vendedor){
    vendedores.push_back(vendedor);
}

void Supervisor ::  listarVendedores(){
    for(auto it : vendedores){
        cout << it;
    }
}

void Supervisor :: listarVendas(){
    if(vendedores.size() == 0) {
        cout << "O supervisor não possui nenhum vendedor" << endl;
        return;
    }

    for(auto vendedor : vendedores){
        if((vendedor->getVendas()).size() != 0)
            vendedor->listarVendas();
    }
}

double Supervisor :: calcularBonificacao(){
    double bonificacao = 0.0;

    for(Vendedor * vendedor : vendedores){
        bonificacao += vendedor->calculaVendas();
    }

    bonificacao *= 0.01;

    return bonificacao;
}

void Supervisor :: serialize(ostream& out) {
    Funcionario::serialize(out);

    out << "\nBonificação: R$" << calcularBonificacao() << endl;
}

ostream& operator<<(ostream& out, Supervisor& s){
    s.serialize(out);

    return out;
}