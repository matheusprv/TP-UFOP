#include "menus.h"

int main(){
    Cadastro cadastroChefe = Cadastro("admin", "admin");
    Chefe chefe = Chefe("Admin", cadastroChefe, 5000);

    Funcionario * funcionarioLogado = nullptr;

    int opcao; //opcao selecionada para o menu
    int tipoLogin; //1- Chefe    2- Funcionario

    do{
        telaInicial(opcao);

        switch(opcao){
            case 1:
                escolhaDeLogin(tipoLogin);
                if(telaLoginUsuario(tipoLogin, chefe, funcionarioLogado)){
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

            case 2:
                cout << "Saindo do sistema..." << endl;
            default:
                cout << "Opção Inválida!" << endl;
        }
    }while(opcao != 2);

    return 0;
}

