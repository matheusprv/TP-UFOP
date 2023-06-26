#include "Supervisor.h"

Supervisor :: Supervisor(string nome, const Cadastro& cadastro, double salarioHora, double salarioTotal){
    setNome(nome);
    setCadastro(cadastro);
    setSalarioHora(salarioHora);
    setSalarioTotal(salarioTotal);
}

Supervisor :: ~Supervisor(){}

void Supervisor :: cadastrarVendedor(const Vendedor& vendedor){
    vendedores.push_back(vendedor);
}

void Supervisor ::  listarVendedores(){
    for(auto it : vendedores){
        cout << it;
    }
}

void Supervisor :: listarVendas(){
    for(auto vendedor : vendedores){
        vendedor.listarVendas();
    }
}

double Supervisor :: calcularBonificacao(){
    return 0;
}

void Supervisor :: serialize(ostream& out) {
    Funcionario::serialize(out);

    out << "\nBonificação: R$" << calcularBonificacao() << endl;
}

ostream& operator<<(ostream& out, Supervisor& s){
    s.serialize(out);

    return out;
}