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
    public Funcionario localizar(int id) {
        List<Funcionario> listaFuncionarios = Dados.getListaFuncionarios();

        // Verificando se o funcionario esta no vetor
        for (int i = 0; i < listaFuncionarios.size(); i++) {
            if (listaFuncionarios.get(i).getId() == id) {
                return listaFuncionarios.get(i);
            }
        }

        return null;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Funcionario original = (Funcionario) objOriginal;
        Funcionario novo = (Funcionario) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.getListaFuncionarios().indexOf(original);
        if(index == -1) return;
        
        Dados.getListaFuncionarios().set(index, novo);
        
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
