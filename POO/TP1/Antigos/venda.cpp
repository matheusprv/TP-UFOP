#include "venda.h"


Venda :: Venda(int id, double valor, int quantidade){
    this->id = id;
    this->valor = valor;
    this->quantidade = quantidade;
}

Venda :: ~Venda(){}

int Venda :: getId() const{
    return this->id;
}
void Venda :: setId(const int &id){
    this->id = id;
}

double Venda :: getValor() const{
    return this->valor;
}
void Venda :: setValor(const double &valor){
    this->valor = valor;
}

int Venda :: getQuantidade() const{
    return this->quantidade;
}
void Venda :: setQuantidade(const int &quantidade){
    this->quantidade = quantidade;
}

void Venda :: serialize(ostream& out) const{
    out 
    << string("Valor: ") << getValor() << "\n"
    << string("Quantidade: ") << getQuantidade() << "\n"
    << string("ID: ") << getId() << "\n\n";
}
ostream& operator <<(ostream& out, const Venda &obj){
    obj.serialize(out);
    return out;
}



