#include "menus.h"

int main(){
    Cadastro * cadastroChefe = new Cadastro("admin", "admin");
    Chefe chefe = Chefe("Admin", cadastroChefe, 5000);

    Supervisor * supervisor = new Supervisor("Matheus", new Cadastro("matheus", "123"), 0, 0);
    Vendedor * vendedor = new Vendedor("João", new Cadastro("joao", "123"), 0, 0);

    chefe.cadastrarFuncionario(supervisor);
    chefe.cadastrarFuncionario(vendedor);
    supervisor->cadastrarVendedor(vendedor);

    Funcionario * funcionarioLogado = nullptr;

    int opcao; //opcao selecionada para o menu
    int tipoLogin; //1- Chefe    2- Funcionario

    do{
        telaInicial(opcao);

        switch(opcao){
            case 1:
                escolhaDeLogin(tipoLogin);
                if(telaLoginUsuario(tipoLogin, chefe, &funcionarioLogado)){
                    cout << "Login feito com sucesso!" << endl;
                    
                    if(tipoLogin == 1){
                        menuChefe(chefe);
                    }
                    else{
                        menuFuncionario(funcionarioLogado); //! Fazer dynamic_cast do funcionario dentro da funcao para ter vendedor ou supervisor 
                    }
                }
                else
                    cout << "Usuário de login e/ou senha incorreto(s)!" << endl;
            break;

            default:
                cout << "Saindo do sistema..." << endl;
        }
    }while(opcao != 2);

    return 0;
}

