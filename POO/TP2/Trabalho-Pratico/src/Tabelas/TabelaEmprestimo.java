/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOEmprestimo;
import Modelo.Emprestimo;
import java.util.ArrayList;
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
    
    public void addEmprestimo(Emprestimo emprestimo){
        daoEmprestimo.incluir(emprestimo);
        this.fireTableDataChanged();
    }
    
    public void updateEmprestimo(Emprestimo emprestimoNovo, Emprestimo emprestimoVelho){
        daoEmprestimo.atualizar(emprestimoVelho, emprestimoNovo);
        this.fireTableDataChanged();
    }
    
    public void deletarFuncionario(Emprestimo emprestimo){
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
        return switch (columnIndex){
            case 0 -> emprestimos.get(rowIndex).getIdFuncionario();
            case 1 -> emprestimos.get(rowIndex).getIdUsuario();
            case 2 -> emprestimos.get(rowIndex).getIdLivro();
            case 3 -> emprestimos.get(rowIndex).getDataEmprestimo();
            default -> emprestimos.get(rowIndex).getId();
        };
    }    
}