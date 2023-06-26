#ifndef PONTO_H
#define PONTO_H

#include "Hora.h"
#include <string>
using namespace std;

class Ponto{
    Hora horarioEntrada;
    Hora horarioSaida;
    string data;
public:
    Ponto(const Hora& = Hora(), const Hora& = Hora(), string = "");
    virtual ~Ponto();

    Hora getHorarioEntrada() const;
    void setHorarioEntrada(Hora);

    Hora getHorarioSaida() const;
    void setHorarioSaida(Hora);

    string getData() const;
    void setData(string);
};

#endif