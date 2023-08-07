package DAO;

import Dados.Dados;
import Modelo.Funcionario;
import java.util.List;

public class DAOFuncionario implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Funcionario funcionario = (Funcionario) obj;
        List<Funcionario> listaFuncionarios = Dados.getListaFuncionarios();
        listaFuncionarios.add(funcionario);
    }

    @Override
    public int localizar(int id) {
        List<Funcionario> listaFuncionarios = Dados.getListaFuncionarios();

        // Verificando se o funcionario esta no vetor
        for (int i = 0; i < listaFuncionarios.size(); i++) {
            if (listaFuncionarios.get(i).getId() == id) {
                return i;
            }
        }

        return -1;
    }

    @Override
    public void atualizar(Object original, Object novo) {
        Funcionario funcionarioOriginal = (Funcionario) original;
        Funcionario funcionarioNovo = (Funcionario) novo;

        List<Funcionario> listaFuncionarios = Dados.getListaFuncionarios();

        // Procurando o index do elemento
        int index = localizar(funcionarioOriginal.getId());
        if (index == -1) {
            return;
        }

        Dados.getListaFuncionarios().set(index, funcionarioNovo);
        
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        
        Dados.getListaFuncionarios().remove(obj);
    }

    @Override
    public List<Funcionario> getLista() {
        return Dados.getListaFuncionarios();
    }
}
