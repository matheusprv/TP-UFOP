/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOLivro;
import Modelo.Livro;
import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author mathe
 */
public class TabelaLivro extends AbstractTableModel{
    
    static DAOLivro daoLivro = new DAOLivro();
    static ArrayList<Livro> livros;
    String[] colunas = {"Título", "", "id"};
    
    public TabelaLivro(){
        //Marcando o ponteiro de categorias com o ponteiro do vetor de categorias dos dados
        livros = (ArrayList<Livro>) daoLivro.getLista();
        this.fireTableDataChanged();
    }
    
    public void addLivro(Livro livro){
        daoLivro.incluir(livro);
        this.fireTableDataChanged();
    }
    
    public void updateLivro(Livro livroNovo, Livro livroVelho){
        daoLivro.atualizar(livroVelho, livroNovo);
        this.fireTableDataChanged();
    }
    
    public void deletarLivro(Livro livro){
        daoLivro.remover(livro);
        this.fireTableDataChanged();
    }
    
    @Override
    public int getRowCount() {
        return livros.size();
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
            case 0 -> livros.get(rowIndex).getTitulo();
            default -> livros.get(rowIndex).getId();
        };
    }
    
}
