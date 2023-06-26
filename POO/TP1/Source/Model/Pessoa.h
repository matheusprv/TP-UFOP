#ifndef PESSOA_H
#define PESSOA_H

#include "Cadastro.h"
#include <iostream>
#include <string>
using namespace std;

class Pessoa {
    int id;
    static int incrementador;
    string nome;
    Cadastro cadastro;

public:
    Pessoa(string="", const Cadastro& = Cadastro());
    virtual ~Pessoa();

    string getNome() const;
    void setNome(string);

    int getId() const;
    void setId(int);

    Cadastro getCadastro() const;
    void setCadastro(Cadastro);

    void serialize(ostream&) const;
    friend ostream & operator<< (ostream & out, const Pessoa & obj);
};

#endif