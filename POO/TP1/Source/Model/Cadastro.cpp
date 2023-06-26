#include <iostream>
#include "Cadastro.h"
using namespace std;

Cadastro :: Cadastro(string login, string senha){
    this->login = login;
    this->senha = senha;
}

Cadastro :: ~Cadastro() {}

string Cadastro :: getLogin() const {
    return login;
}

void Cadastro :: setLogin(string login) {
    this->login = login;
}

string Cadastro :: getSenha() const {
    return senha;
}

void Cadastro :: setSenha(string senha) {
    this->senha = senha;
}