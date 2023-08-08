/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package DAO;

import Dados.Dados;
import Modelo.Emprestimo;
import java.util.List;

/**
 *
 * @author mathe
 */
public class DAOEmprestimo implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Emprestimo emprestimo = (Emprestimo) obj;
        Dados.getListaEmprestimos().add(emprestimo);
    }

    @Override
    public Emprestimo localizar(int id) {
        int i;
        for(i = 0; i < Dados.getListaEmprestimos().size(); i++){
            if(Dados.getListaEmprestimos().get(i).getId() == id)
                return Dados.getListaEmprestimos().get(i);
        }
        return null;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Emprestimo original = (Emprestimo) objOriginal;
        Emprestimo novo = (Emprestimo) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.getListaEmprestimos().indexOf(original);
        if(index == -1) return;
        
        Dados.getListaEmprestimos().set(index, novo);
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        
        Dados.getListaEmprestimos().remove(obj);
    }

    @Override
    public List<Emprestimo> getLista() {
        return Dados.getListaEmprestimos();
    }
    
}
