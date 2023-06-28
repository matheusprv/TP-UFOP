#ifndef MENUCHEFE_H
#define MENUCHEFE_H

#include "../Model/Supervisor.h"
#include "../Model/Vendedor.h"
#include "../Model/Chefe.h"
#include "limits"
#include "menus.h"


void cadastrarSupervisor(Chefe& chefe);

Supervisor * selecionarSupervisor(Chefe &chefe);

void cadastrarVendedor(Chefe& chefe);

void cadastrarFuncionario(Chefe& chefe);

void menuChefe(Chefe& chefe);


#endif