#include "Pessoa.h"

int Pessoa :: incrementador = 0;

Pessoa :: Pessoa(string nome, Cadastro * cadastro){
    this->id = ++incrementador;
    this->nome = nome;
    this->cadastro = cadastro;
}

Pessoa :: ~Pessoa() {}

string Pessoa :: getNome() const{
    return nome;
}

void Pessoa :: setNome(string nome){
    this->nome = nome;
}

int Pessoa :: getId() const{
    return id;
}

Cadastro* Pessoa :: getCadastro() const{
    return cadastro;
}

void Pessoa :: setCadastro(Cadastro * cadastro){
    this->cadastro = cadastro;
}

void Pessoa :: serialize(ostream& out) const{
    out << "Nome: " << nome
        << "\nId: " << id
        << "\nLogin: " << cadastro->getLogin() << endl;
}

ostream & operator  << (ostream & out, const Pessoa & obj){
    obj.serialize(out);
    return out;
}