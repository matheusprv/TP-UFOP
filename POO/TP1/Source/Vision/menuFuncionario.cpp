#include "menuFuncionario.h"

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
    double valor = -1.0;
    int quantidade = -1;

    //Quantidade
    do{
        cout << "Informe a quantidade de itens da venda: ";
        cin >> quantidade;
        try{
            venda->setQuantidade(quantidade);
        }
        catch(invalid_argument &e){
            cout<<"Erro: "<<e.what();
        }
    }while(quantidade < 0);

    cout << "\n";

    //Valor
    do{
        cout << "Informe o valor individual do item: ";
        cin >> valor;
        try{
            venda->setValor(valor);
        }
        catch(invalid_argument &e){
            cout<<"Erro: "<<e.what();
        }
    }while(valor < 0);

    cout << "\n";
}