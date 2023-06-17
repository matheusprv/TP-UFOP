#include "pessoa.h"

int main(){

    Pessoa pessoas [6];
    pessoas[0] = Pessoa ("Matheus", "matheus", "123");
    pessoas[1] = Pessoa ("Felipe", "felipe", "123");
    pessoas[2] = Pessoa ("Pedro", "morais", "123");
    pessoas[3] = Pessoa ("Nicolas", "nicolas", "123");
    pessoas[4] = Pessoa ("Lucas", "lucas", "123");
    pessoas[5] = Pessoa ("Pedro", "Leão", "123");

    for (Pessoa p : pessoas){
        cout << p;
    }

    return 0;
}