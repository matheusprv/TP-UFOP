#include "Venda.h"
using namespace std;

int Venda :: incrementador = 0;

Venda :: Venda (double valor, int quantidade){
    this->id = ++incrementador;
    this->setValor(valor);
    this->setQuantidade(quantidade);
}

Venda :: ~Venda (){}

int Venda:: getId() const{
    return this->id;
}

double Venda:: getValor() const{
    return this->valor;
}

void Venda:: setValor(double valor){
    if(valor < 0)
        throw invalid_argument("O valor não pode ser menor que zero.\n");
    this->valor = valor;
}

int Venda:: getQuantidade() const{
    return this->quantidade;
}

void Venda:: setQuantidade(int quantidade){
    if(quantidade < 0)
        throw invalid_argument("A quantidade não pode ser menor que zero.\n");
    
    this->quantidade = quantidade;
}


void Venda :: serialize(ostream& out) const{
    out << "Id: " << this->id << "\n"
        << "Quantidade: " << this->quantidade << "\n"
        << "Valor: " << this->valor << "\n" << endl;
}

ostream & operator  << (ostream & out, const Venda & obj){
    obj.serialize(out);
    return out;
}