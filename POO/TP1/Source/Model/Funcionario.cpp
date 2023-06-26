#include "Funcionario.h"

Funcionario::Funcionario(string nome, const Cadastro& cadastro, double salarioHora, double salarioTotal){
    Pessoa(nome, cadastro);
    this->setSalarioHora(salarioHora);
    this->setSalarioTotal(salarioTotal);
}

Funcionario :: ~Funcionario(){
    // for(Ponto ponto : pontos)
    //     delete ponto;
    
    // for(auto it : minutosTrabalhados)
    //     delete it;
}

double Funcionario :: getSalarioHora() const {
    return salarioHora;
}

void Funcionario :: setSalarioHora(double salarioHora) {
    if(salarioHora < 0)
        throw invalid_argument("O valor não pode ser menor que zero.\n");

    this->salarioHora = salarioHora;
}

double Funcionario :: getSalarioTotal() const {
    return salarioTotal;
}

void Funcionario :: setSalarioTotal(double salarioTotal) {
    if(salarioTotal < 0)
        throw invalid_argument("O valor não pode ser menor que zero.\n");

    this->salarioTotal = salarioTotal;
}

void Funcionario :: registrarPonto(const Ponto& ponto){
    this->pontos.push_back(ponto);
}

vector<Ponto> Funcionario :: getPontos() const {
    return pontos;
}

void Funcionario :: serialize(ostream& out) const{
    Pessoa::serialize(out);

    out << "\nSalário por Hora: R$" << salarioHora
        << "\nSalário Total: R$" << salarioTotal << endl;
}