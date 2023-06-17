#include "pessoa.h"

int Pessoa::incrementador = 0;

Pessoa :: Pessoa(string nome, string usuarioLogin, string senha){
    this-> nome = nome;     
    this-> usuarioLogin = usuarioLogin; 
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


string Pessoa :: getUsuarioLogin() const {
    return this->usuarioLogin;
}
void Pessoa :: setUsuarioLogin(const string &usuarioLogin){
    this->usuarioLogin = usuarioLogin;
}

void Pessoa :: serialize(ostream & out) const{
    out << string("Nome: ") << getNome()
        << string("\nUsuarioLogin: ") << getUsuarioLogin()
        << string("\nSenha: ") << getSenha()
        << string("\nID: ") << getID() 
        << endl;
}

ostream& operator <<(ostream& out, const Pessoa &obj){
    obj.serialize(out);
    return out;
}