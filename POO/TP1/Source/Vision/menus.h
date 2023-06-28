#ifndef MENUS_H
#define MENUS_H

#include "../Model/Supervisor.h"
#include "../Model/Vendedor.h"
#include "../Model/Chefe.h"
#include "limits"

void selecaoMenu(int &opcao, int min, int max);

void telaInicial(int &opcao);

bool telaLoginUsuario(const int &tipoLogin, const Chefe& chefe, Funcionario** funcionario);

void escolhaDeLogin(int &tipoLogin);

void menuChefe(Chefe& chefe);

void menuFuncionario(Funcionario* funcionario);

void opcoesSupervisor(Supervisor* supervisor);

void opcoesVendedor(Vendedor *vendedor);

void cadastrarPonto(Ponto*);

void cadastrarVendaUnica(Venda*);

#endif