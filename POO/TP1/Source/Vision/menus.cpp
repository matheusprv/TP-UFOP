#include "menus.h"

void selecaoMenu(int &opcao, int min, int max){
    opcao = -1;
    do{
        if(!(cin >> opcao)){
            throw invalid_argument("A opção precisa ser ou "+ to_string(min) +" ou "+ to_string(max) +".\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }while (opcao < min || opcao > max);
}

void telaInicial(int &opcao){
    cout << "TELA INICIAL\n";
    cout << "\t1- Login\n";
    cout << "\t2- Sair do sistema\n";
    selecaoMenu(opcao, 1, 2);
}


bool validacaoFuncionario(string login, string password, vector<Funcionario*> funcionarios, Funcionario* ptrFunc){

    for (auto funcionario : funcionarios){
        Cadastro temp = funcionario->getCadastro();
        if(login == temp.getLogin() && password == temp.getSenha()){
            ptrFunc = funcionario;
            
            return true;
        }
    }
    
    return false;
}


bool validacaoChefe(string login, string password, const Chefe& chefe){
    Cadastro temp = chefe.getCadastro();

    return (login == temp.getLogin() && password == temp.getSenha());
}


bool telaLoginUsuario(const int &tipoLogin, const Chefe& chefe, Funcionario* funcionario){
    string login, password;
    
    cout << "Usuario: \n";
    cin >> login;
    cout << "Senha: \n"; 
    cin >> password;

    switch(tipoLogin){
        case 1: //chefe
            return validacaoChefe(login, password, chefe);
        break;

        default: //funcionario
            return validacaoFuncionario(login, password, chefe.getFuncionarios(), funcionario);
    }

}

void escolhaDeLogin(int &tipoLogin){
    cout << "Selecione seu Login:\n";
    cout << "\t1- Chefe\n";
    cout << "\t2- Funcionario\n";
    selecaoMenu(tipoLogin, 1, 2);
}

//Fazer o cadastro do funcionario e listar funcionarios
void menuChefe(Chefe& chefe){
    cout << "1 - Cadastrar Funcionarios \n";
    cout << "2 - Listar Funcionarios \n";
    
    int opcao;
    string nome, login, senha;
    double salarioHora, salarioTotal;
    switch(opcao){
    case 1:
         
    break;
    case 2:
        
    break;
    
    default:
        break;
    } 
}

void menuFuncionario(Funcionario* funcionario){
    cout << "1 - Registrar Ponto \n"
    << "2 - Listar Vendas \n"
    << "3 - Calcular Bonificação\n";

    int opcao;
    switch (opcao)
    {
    case 1:
        /* code */
    break;
    case 2:
    
    break;

    case 3:

    break;
    
    default:
        break;
    }
}