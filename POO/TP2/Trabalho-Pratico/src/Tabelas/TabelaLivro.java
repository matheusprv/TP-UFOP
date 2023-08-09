/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOLivro;
import Modelo.Autor;
import Modelo.Categoria;
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
    String[] colunas = {"Título", "Autor(es)", "Categoria(s)", "id"};
    
    public TabelaLivro(){
        //Marcando o ponteiro de livros com o ponteiro do vetor de livros dos dados
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
        
        if(columnIndex == 0) return livros.get(rowIndex).getTitulo();
        
        else if (columnIndex == 1){
            String strListaAutores = "";
            for(Autor aut : livros.get(rowIndex).getAutor()) 
                strListaAutores += aut.getNome() + ", ";
            
            if(strListaAutores.length() >= 2)
                return strListaAutores.substring(0, strListaAutores.length() - 2);
            else
                return strListaAutores;
        }
        
        else if (columnIndex == 2){
            String strListaCategorias = "";
            for(Categoria cat : livros.get(rowIndex).getCategoria()) 
                strListaCategorias += cat.getTitulo()+ ", ";
            
            if(strListaCategorias.length() >= 2)
                return strListaCategorias.substring(0, strListaCategorias.length() - 2);
            else
                return strListaCategorias;
        }
       
        else return livros.get(rowIndex).getId();
        
    }
    
}
