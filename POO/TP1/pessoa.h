#include <iostream>
#include <string>
#include <ostream>


using namespace std;

class Pessoa{
    string nome, login, senha;
    int id;
    static int incrementador;

public:
    Pessoa(string nome = "", string  login = "", string senha = "");
    ~Pessoa();
    
    string getNome() const;
    void setNome(const string &);
    
    string getLogin() const;
    void setLogin(const string &);

    string getSenha() const;
    void setSenha(const string &);

    int getID() const;
    void setID(const int &);

    void serialize(ostream&) const;
    friend ostream& operator <<(ostream& out, const Pessoa &);
    
};

