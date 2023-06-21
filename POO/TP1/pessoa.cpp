#include "pessoa.h"

int Pessoa::incrementador = 0;

Pessoa :: Pessoa(string nome){
    this-> nome = nome;     
    this-> id = ++incrementador;
}

Pessoa :: ~Pessoa(){};

string Pessoa :: getNome() const {
    return this->nome;
}

void Pessoa :: setNome(const string &nome){ 
    this->nome = nome; 
}



int Pessoa :: getID() const {
    return this->id; 
}   
void Pessoa :: setID(const int &id){
    this->id = id;
}



void Pessoa :: serialize(ostream & out) const{
    out << string("Nome: ") << getNome()
        << string("\nID: ") << getID() 
        << "\n\n";
}

ostream& operator <<(ostream& out, const Pessoa &obj){
    obj.serialize(out);
    return out;
}