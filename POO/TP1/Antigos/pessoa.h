#ifndef PESSOA_H
#define PESSOA_H


#include <iostream>
#include <string>
#include <ostream>
#include <vector>


using namespace std;

class Pessoa{
    string nome;
    int id;
    static int incrementador;

public:
    Pessoa(string nome = "");
    ~Pessoa();
    
    string getNome() const;
    void setNome(const string &);
    
    
    int getID() const;
    void setID(const int &);

    void serialize(ostream&) const;
    friend ostream& operator <<(ostream& out, const Pessoa &);
    
};

#endif