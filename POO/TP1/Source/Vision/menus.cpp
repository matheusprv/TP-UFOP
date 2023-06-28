#include "menus.h"

void selecaoMenu(int &opcao, int min, int max){
    opcao = -1;
    do{
        if(!(cin >> opcao)){
            throw invalid_argument("A opção precisa ser um número entre ["+ to_string(min) +" e "+ to_string(max) +"].\n");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }while (opcao < min || opcao > max);

    cout << "\n";
}

void telaInicial(int &opcao){
    cout << "TELA INICIAL\n";
    cout << "\t1- Login\n";
    cout << "\t2- Sair do sistema\n";
    cout << "Opção: ";
    selecaoMenu(opcao, 1, 2);
}


bool validacaoLoginFuncionario(Cadastro cadastroLogin, vector<Funcionario*> funcionarios, Funcionario** ptrFunc){

    for (Funcionario * funcionario : funcionarios){
        //Comparando o login e senha passado com o que o cadastro de pessoa possui
        Cadastro * temp = funcionario->getCadastro();
        if(*temp == cadastroLogin){
            *ptrFunc = funcionario;

            return true;
        }
    }
    
    return false;
}


bool validacaoLoginChefe(Cadastro cadastroLogin, const Chefe& chefe){
    Cadastro * temp = chefe.getCadastro();

    return *temp == cadastroLogin;
}


bool telaLoginUsuario(const int &tipoLogin, const Chefe& chefe, Funcionario** funcionario){
    string login, password;
    
    cout << "Usuario: ";
    cin >> login;
    cout << "Senha: "; 
    cin >> password;

    Cadastro cadastroLogin = Cadastro(login, password);

    bool verificacao;

    switch(tipoLogin){
        case 1: //chefe
            verificacao = validacaoLoginChefe(cadastroLogin, chefe);
        break;

        default: //funcionario
            verificacao = validacaoLoginFuncionario(cadastroLogin, chefe.getFuncionarios(), funcionario);
    }

    cout << "\n";
    return verificacao;
}

void escolhaDeLogin(int &tipoLogin){
    cout << "Selecione seu Login:\n";
    cout << "\t1- Chefe\n";
    cout << "\t2- Funcionario\n";
    cout << "Opção: ";
    selecaoMenu(tipoLogin, 1, 2);
}


void cadastrarSupervisor(Chefe& chefe){
    string nome, login, senha;
    double salarioHora;

    cout << "Nome: ";
    cin >> nome;
    cout << "Login: ";
    cin >> login;
    cout << "Senha: ";
    cin >> senha;
    
    cout << "Salário Hora: ";
    while(!(cin >> salarioHora)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Salário Hora precisa ser um valor numérico.\nSalário Hora: ";
    }


    Cadastro * cadTemp = new Cadastro(login, senha);
    Supervisor * tempSuper = new Supervisor(nome, cadTemp, salarioHora, 0);

    chefe.cadastrarFuncionario(tempSuper);

}


//Seleciona o supervisor que o vendedor sera adicionado
Supervisor * selecionarSupervisor(Chefe &chefe){
    
    cout << "\nListando todos os supervisores disponíveis.\n";

    vector<Supervisor *> supervisores;
    Supervisor * supervisorTemp;

    //Gerando o vetor de supervisores e exibindo seus valores
    for(auto * funcionario : chefe.getFuncionarios()){

        if(typeid(*funcionario) == typeid(Supervisor)){

            supervisorTemp = dynamic_cast<Supervisor*>(funcionario);
            supervisores.push_back(supervisorTemp);

            cout << "Id: " << supervisorTemp->getId() << " - Nome: " << supervisorTemp->getNome() << endl;
        }
    }
    cout << "\n";

    //Selecionado o supervisor
    int opcaoId;

    while(true){
        cout << "Coloque o Id do supervisor responsável por este vendedor: ";
        while(!(cin >> opcaoId)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "O Id precisa ser um valor numérico.\n";
            cout << "Coloque o Id do supervisor responsável por este vendedor: ";
        }
        
        //Verificando se o ID do supervisor existe
        for (auto *supervisor : supervisores)
            if(opcaoId == supervisor->getId())
                return supervisor;
        
        cout << "Id de supervisor inválido.\n";
    }
}


void cadastrarVendedor(Chefe& chefe){

    if(chefe.getQtdFuncionarios()== 0){
        cout << "Não é possível cadastrar um vendedor, pois não há nenhum supervisor cadastrado.\n";
        return;
    }

    //Criando o vendedor
    string nome, login, senha;
    double salarioHora;

    cout << "Nome: ";
    cin >> nome;
    cout << "Login: ";
    cin >> login;
    cout << "Senha: ";
    cin >> senha;

    cout << "Salário Hora: ";
    while(!(cin >> salarioHora)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Salário Hora precisa ser um valor numérico.\nSalário Hora: ";
    }

    
    //Adicionando as informacoes do vendedor e colocando de inicio seu salario total com valor 0
    Vendedor *novoVendedor = new Vendedor(nome, new Cadastro(login, senha), salarioHora, 0);

    //Adicionando o vendedor no vetor de funcionarios do chefe
    chefe.cadastrarFuncionario(novoVendedor);

    //Gerando uma lista com todos os supervisores disponíveis
    Supervisor * supervisorTemp = selecionarSupervisor(chefe);
    supervisorTemp->cadastrarVendedor(novoVendedor);

    cout << "\n";

}


void cadastrarFuncionario(Chefe& chefe){

    int opcao = -1;
    
    do{
        cout << "1 - Cadastrar Supervisor \n" 
        << "2 - Cadastrar Vendedor \n" 
        << "3 - Voltar\n"
        << "Opção: ";
        selecaoMenu(opcao, 1, 3);

        switch(opcao){
            case 1:
                cadastrarSupervisor(chefe);
                break;
        
            case 2:
                cadastrarVendedor(chefe);
                break;
                
            default:
                break;     
        }

    }while(opcao != 3);
}

//Fazer o cadastro do funcionario e listar funcionarios
void menuChefe(Chefe& chefe){
    cout << "Olá, chefe " << chefe.getNome() << endl;
    int opcao;
    do{
        cout << "1 - Cadastrar Funcionários \n" 
             << "2 - Listar Funcionarios \n" 
             << "3 - Checar Ponto dos Funcionarios \n"
             << "4 - Calculo de salarios e bonificacoes \n" 
             << "5 - Voltar\n"
             << "Opção: ";
        
        selecaoMenu(opcao, 1, 5);

        switch(opcao){
            case 1:
                cadastrarFuncionario(chefe);
                break;
                
            case 2:
                chefe.listarFuncionarios();
                break;
            
            case 3:
                
                break;

            case 4:
                break;
            
            default:
                break;
        }
        
    }while(opcao != 5);
}

void menuFuncionario(Funcionario* funcionario){
    if(typeid(*funcionario) == typeid(class Vendedor)){
        Vendedor* vendedor = dynamic_cast<Vendedor*>(funcionario);
        opcoesVendedor(vendedor);
    }
    else { // typeid(*funcionario) == typeid(class Supervisor)
        Supervisor* supervisor = dynamic_cast<Supervisor*>(funcionario);
        opcoesSupervisor(supervisor);
    }
}

void opcoesSupervisor(Supervisor* supervisor){

    cout << "Olá, supervisor " << supervisor->getNome() << endl;

    int opcao;
    
    do{
        cout << "1 - Cadastrar Ponto \n"
            << "2 - Exibir Salário \n"
            << "3 - Listar Vendas \n"
            << "4 - Retornar a tela inicial\n"
            << "Opção: ";
            
        selecaoMenu(opcao, 1, 5); 

        Ponto* pontoUnico = new Ponto();

        switch(opcao){
            case 1:
                cadastrarPonto(pontoUnico);
                supervisor->registrarPonto(pontoUnico);
            break;

            case 2: 
                //salario + bonificacao complicadasso, mas não impossivel
                cout << "Not implemented" << endl;
            break;

            case 3:
                supervisor->listarVendas();
            break;
        
            default:
                cout<<"Retornando ao menu principal...\n";
            break;
        }
           
    }while(opcao != 4);

}

void opcoesVendedor(Vendedor *vendedor){

    int opcao;

    do{
        cout << "1 - Cadastrar Ponto \n"
            << "2 - Exibir Salário \n"
            << "3 - Cadastrar Venda \n"
            << "4 - Listar Vendas \n"
            << "5 - Retornar a tela inicial\n"
            << "Opção: ";

        selecaoMenu(opcao, 1, 6);

        Ponto* pontoUnico =  new Ponto();
        Venda* vendaUnica =  new Venda();

        switch (opcao){
            case 1:
                cadastrarPonto(pontoUnico);
                vendedor->registrarPonto(pontoUnico);
            break;

            case 2:

            break;

            case 3:
                cadastrarVendaUnica(vendaUnica);
                vendedor->cadastrarVenda(vendaUnica);
            break;

            case 4:
                vendedor->listarVendas();
            break;
        
            default:
                cout<<"Retornando ao menu principal...\n";
            break;
        }
        
    }while(opcao != 5);

}

void cadastrarPonto(Ponto* ponto){
    int hora, minuto;
    string data;
    
    //Data
    cout<< "Informe a data atual (formato 23 04 2023): ";
    cin>>data;

    //Horário de entrada
    cout << "Informe a hora de entrada (formato a ser digitado: hora minuto):";
    cin >> hora >> minuto;
    Hora horarioE;
    try{
        horarioE = Hora(hora, minuto);
    }
    catch(invalid_argument &e){
        cout<<"Erro:"<<e.what();
    }
    
    //Horário de saída
    cout << "Informe a hora de saida (formato a ser digitado: hora minuto):";
    cin >> hora >> minuto;
    
    Hora horarioS;
    try{
        horarioS = Hora(hora, minuto);
    }
    catch(invalid_argument &e){
        cout<<"Erro:"<<e.what();
    }
    
    //Criação do ponto
    ponto->setHorarioEntrada(horarioE);
    ponto->setHorarioSaida(horarioS);
    ponto->setData(data);
}

void cadastrarVendaUnica(Venda* venda)
{
    double valor;
    int quantidade;

    //Quantidade
    cout << "Informe a quantidade de itens da venda: ";
    cin >> quantidade;

    //Valor
    cout << "Informe o valor individual do item: ";
    cin >> valor;

    try{
        venda->setQuantidade(quantidade);
        venda->setValor(valor);
    }
    catch(invalid_argument &e){
        cout << "Erro: "<< e.what();
    }
}

