#include "cadastro.h"


Cadastro::Cadastro(string login, string senha){
    this->login = login;
    this->senha = senha;
}

Cadastro::~Cadastro(){}

string Cadastro :: getLogin() const{
    return this->login;
}
void Cadastro :: setLogin(const string &login){
    this->login = login;
}

string Cadastro :: getSenha() const{
    return this->senha;
}
void Cadastro :: setSenha(const string &senha){
    this->senha = senha;
}

