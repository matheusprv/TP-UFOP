#ifndef MENUS_H
#define MENUS_H

#include "../Model/Supervisor.h"
#include "../Model/Vendedor.h"
#include "../Model/Chefe.h"
#include "limits"

void selecaoMenu(int &opcao, int min, int max);

void telaInicial(int &opcao);

bool telaLoginUsuario(const int &tipoLogin, const Chefe& chefe, Funcionario* funcionario);

bool validacaoChefe(string login, string password, const Chefe& chefe);

bool validacaoFuncionario(string login, string password, vector<Funcionario*> funcionarios, Funcionario* ptrFunc);

void escolhaDeLogin(int &tipoLogin);

void menuChefe(Chefe& chefe);

void menuFuncionario(Funcionario* funcionario);

void opcoesSupervisor(Supervisor* supervisor);

void opcoesVendedor(Vendedor *vendedor);

#endif