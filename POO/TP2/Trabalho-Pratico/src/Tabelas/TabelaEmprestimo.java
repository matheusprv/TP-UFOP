/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOEmprestimo;
import DAO.DAOFuncionario;
import DAO.DAOLivro;
import DAO.DAOUsuario;
import Modelo.Emprestimo;
import Modelo.Usuario;
import java.util.ArrayList;
import java.util.Date;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author pedro
 */
public class TabelaEmprestimo extends AbstractTableModel{
    
    private DAOEmprestimo daoEmprestimo = new DAOEmprestimo();
    private ArrayList<Emprestimo> emprestimos;
    private String[] colunas = {"Funcionário", "Usuário", "Livro", "Data", "ID"};
    
    public TabelaEmprestimo(){
        //Marcando o ponteiro de categorias com o ponteiro do vetor de categorias dos dados
        emprestimos = (ArrayList<Emprestimo>) daoEmprestimo.getLista();
        this.fireTableDataChanged();
    }
    
    public TabelaEmprestimo(Usuario usuario){
        emprestimos = new ArrayList<>();
        
        ArrayList<Emprestimo> emprestimosTemp = (ArrayList<Emprestimo>) daoEmprestimo.getLista();
        
        if(emprestimosTemp == null) return;
        
        //Verificando quais sao os emprestimos do usuario
        for(Emprestimo emp : emprestimosTemp){
            if(emp.getIdUsuario() == usuario.getId())
                emprestimos.add(emp);
        }
        
        this.fireTableDataChanged();
    }
    
    public void addEmprestimo(Emprestimo emprestimo){
        daoEmprestimo.incluir(emprestimo);
        this.fireTableDataChanged();
    }
    
    public void updateEmprestimo(Emprestimo emprestimoNovo, Emprestimo emprestimoVelho){
        daoEmprestimo.atualizar(emprestimoVelho, emprestimoNovo);
        this.fireTableDataChanged();
    }
    
    public void deletarEmprestimo(Emprestimo emprestimo){
        daoEmprestimo.remover(emprestimo);
        this.fireTableDataChanged();
    }
    
    @Override
    public int getRowCount() {
        return emprestimos.size();
    }

    @Override
    public int getColumnCount() {
        return colunas.length;
    }
    
    @Override
    public String getColumnName(int column) {
        return colunas[column];
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        Object obj;
        
        switch (columnIndex){
            case 0 -> {
                DAOFuncionario daoFunc = new DAOFuncionario();
                int id = emprestimos.get(rowIndex).getIdFuncionario();
                obj = daoFunc.localizar(id).getNome();
            }
            case 1 -> {
                DAOUsuario daoUser = new DAOUsuario();
                int id = emprestimos.get(rowIndex).getIdUsuario();
                obj = daoUser.localizar(id).getNome();
            }
            case 2 -> {
                DAOLivro daoLivro = new DAOLivro();
                int id = emprestimos.get(rowIndex).getIdLivro();
                obj = daoLivro.localizar(id).getTitulo();
            }
            case 3 -> {
                //obj = 
                Date date = emprestimos.get(rowIndex).getDataEmprestimo();
                int dia = date.getDay();
                int mes = date.getMonth();
                int ano = date.getYear();
                obj = dia + "/" + mes + "/" + ano;
            }
            default -> obj = emprestimos.get(rowIndex).getId();
        }
        
        return obj;
    }    
}