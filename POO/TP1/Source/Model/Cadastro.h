#ifndef CADASTRO_H
#define CADASTRO_H

#include <string>
using namespace std;

class Cadastro{
    string login;
    string senha;
public:
    Cadastro(string = "", string="");
    virtual ~Cadastro();
    string getLogin() const;
    void setLogin(string);
    string getSenha() const;
    void setSenha(string);
};
#endif