/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOAutor;
import DAO.DAOLivro;
import Modelo.Autor;
import Modelo.Livro;
import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author mathe
 */
public class TabelaAutor extends AbstractTableModel{

    private static DAOLivro daoLivro = new DAOLivro();
    private static DAOAutor daoAutor = new DAOAutor();
    private static ArrayList<Autor> autores;
    String [] colunas = {"Nome", "Sobrenome", "Biografia", "ID"};
    
    public TabelaAutor(){
        autores = (ArrayList<Autor>) daoAutor.getLista();
        this.fireTableDataChanged();
    }
    
    public TabelaAutor(ArrayList<Autor> arr){
        this.autores = arr;
        this.fireTableDataChanged();
    }
    
    public void addAutor(Autor autor){
        daoAutor.incluir(autor);
        this.fireTableDataChanged();
    }
    
    public void updateAutor(Autor novo, Autor velho){
        daoAutor.atualizar(velho, novo);
        this.fireTableDataChanged();
    }
    
    public void deletarAutor(Autor autor){
        daoAutor.remover(autor);
        this.fireTableDataChanged();
    }
    
    public void addAutorLivro(Livro livro, Autor autor){
        //Verificando se o item esta na tabela ou nao. Caso nao esteja, entao adiciona
        if(autores.indexOf(autor) == -1){
            daoLivro.adicionarAutor(livro.getId(), autor);
            this.fireTableDataChanged();
        }
    }
    public void deletarAutorLivro(Autor autor, Livro livro){
        daoLivro.removerAutor(livro.getId(), autor);
        this.fireTableDataChanged();
    }
    
    @Override
    public int getRowCount() {
        return autores.size();
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
            case 0 -> autores.get(rowIndex).getNome();
            case 1 -> autores.get(rowIndex).getSobreNome();
            case 2 -> autores.get(rowIndex).getBiografia();
            default -> autores.get(rowIndex).getId();
        };
    }
    
}
