#include <iostream>

using namespace std;


class Hora{
    int hora, minuto;  
    int dia, mes, ano;
    
public:
    Hora(int hora = 0, int minuto = 0, int dia = 0, int mes = 0, int ano = 0);
    ~Hora();
    
    int getHora() const;
    void setHora(const int &);
    
    int getMinuto() const;
    void setMinuto(const int &);
    
    int getDia() const;
    void setDia(const int &);
    
    int getMes() const;
    void setMes(const int &);

    int getAno() const;
    void setAno(const int &);
    
};


