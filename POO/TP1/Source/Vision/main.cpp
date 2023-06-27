#include "menus.h"

int main(){
    Cadastro cadastroChefe = Cadastro("admin", "admin");
    Chefe chefe = Chefe("Admin", cadastroChefe, 5000);

    Funcionario * funcionarioLogado = nullptr;

    int opcao;
    telaInicial(opcao);

    int tipoLogin;
    while(opcao != 2){
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

            default:
                cout << "Saindo do sistema..." << endl;
        }
    }

    return 0;
}

