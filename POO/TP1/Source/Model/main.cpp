// #include "Supervisor.h"
// #include "Vendedor.h"
// #include "Chefe.h"

// #include <iostream>
// using namespace std;

// int main(){

//     Cadastro cad = Cadastro("Mano Peixas", "123");
//     Chefe chefe = Chefe("Peixoto", cad, 50000);

//     Cadastro cad1 = Cadastro("PEDRIN", "123");
//     Vendedor vendedor = Vendedor("Pedro", cad1, 50, 50);

//     Venda venda;
//     for(int i = 0; i < 5; i++){
//         venda = Venda(i*i, i*25);
//         vendedor.cadastrarVenda(venda);
//     }

//     cad1 = Cadastro("LUCAS", "123");
//     Supervisor sup = Supervisor("Lucas", cad1, 500, 500);

//     sup.cadastrarVendedor(vendedor);
//     //sup.listarVendas();

//     chefe.cadastrarFuncionario(vendedor);
//     chefe.cadastrarFuncionario(sup);
//     chefe.listarFuncionarios();

//     //cout << sup << endl;
//     return 0;
// }