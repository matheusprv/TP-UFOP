/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOAutor;
import Modelo.Autor;
import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author mathe
 */
public class TabelaAutor extends AbstractTableModel{

    static DAOAutor daoAutor = new DAOAutor();
    static ArrayList<Autor> autores;
    String [] colunas = {"Nome", "Sobrenome", "Biografia", "ID"};
    
    public TabelaAutor(){
        autores = (ArrayList<Autor>) daoAutor.getLista();
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
