#ifndef CADASTRO_H
#define CADASTRO_H


#include <iostream>
#include <string>

using namespace std;

class Cadastro{
    string login;
    string senha;
public:
    Cadastro(string login = "", string senha = "");
    ~Cadastro();

    string getLogin() const;
    void setLogin(const string &);

    string getSenha() const;
    void setSenha(const string &);
};

#endif