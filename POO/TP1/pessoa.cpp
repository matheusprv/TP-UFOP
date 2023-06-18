#include "pessoa.h"

int Pessoa::incrementador = 0;

Pessoa :: Pessoa(string nome, string login, string senha){
    this-> nome = nome;     
    this-> login = login; 
    this-> senha = senha;
    this-> id = ++incrementador;
}

Pessoa :: ~Pessoa(){};

string Pessoa :: getNome() const {
    return this->nome;
}

void Pessoa :: setNome(const string &nome){ 
    this->nome = nome; 
}


string Pessoa :: getSenha() const {
    return this->senha;
}
void Pessoa :: setSenha(const string &senha){
    this->senha = senha;
}


int Pessoa :: getID() const {
    return this->id; 
}   
void Pessoa :: setID(const int &id){
    this->id = id;
}


string Pessoa :: getLogin() const {
    return this->login;
}
void Pessoa :: setLogin(const string &login){
    this->login = login;
}

void Pessoa :: serialize(ostream & out) const{
    out << string("Nome: ") << getNome()
        << string("\nLogin: ") << getLogin()
        << string("\nSenha: ") << getSenha()
        << string("\nID: ") << getID() 
        << "\n\n";
}

ostream& operator <<(ostream& out, const Pessoa &obj){
    obj.serialize(out);
    return out;
}