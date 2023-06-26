#include "Ponto.h"

Ponto::Ponto(const Hora & horarioEntrada, const Hora & horarioSaida, string data){
    this->horarioEntrada = horarioEntrada;
    this->horarioSaida = horarioSaida;
    this->data = data;
}

Ponto :: ~Ponto(){}

Hora Ponto :: getHorarioEntrada() const{
    return this->horarioEntrada;
}
void Ponto :: setHorarioEntrada(Hora horarioEntrada){
    this->horarioEntrada = horarioEntrada;
}

Hora Ponto :: getHorarioSaida() const{
    return this->horarioSaida;
}
void Ponto :: setHorarioSaida(Hora horarioSaida){
    this->horarioSaida = horarioSaida;
}

string Ponto :: getData() const{
    return this->data;
}
void Ponto :: setData(string data){
    this->data = data;
}


