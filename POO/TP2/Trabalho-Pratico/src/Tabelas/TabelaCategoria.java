/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Tabelas;

import DAO.DAOCategoria;
import Modelo.Categoria;
import java.util.ArrayList;
import javax.swing.table.AbstractTableModel;

/**
 *
 * @author mathe
 */
public class TabelaCategoria extends AbstractTableModel{
    
    static DAOCategoria daoCategoria = new DAOCategoria();
    static ArrayList<Categoria> categorias;
    String[] colunas = {"Nome", "id"};
    
    public TabelaCategoria(){
        //Marcando o ponteiro de categorias com o ponteiro do vetor de categorias dos dados
        categorias = (ArrayList<Categoria>) daoCategoria.getLista();
        this.fireTableDataChanged();
    }
    
    public void addCategoria(Categoria categoria){
        daoCategoria.incluir(categoria);
        this.fireTableDataChanged();
    }
    
    public void updateCategoria(Categoria catNova, Categoria catVelha){
        daoCategoria.atualizar(catVelha, catNova);
        this.fireTableDataChanged();
    }
    
    public void deletarCategoria(Categoria categoria){
        daoCategoria.remover(categoria);
        this.fireTableDataChanged();
    }
    
    @Override
    public int getRowCount() {
        return categorias.size();
    }

    @Override
    public int getColumnCount() {
        return 2;
    }
    
    @Override
    public String getColumnName(int column) {
        return colunas[column];
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return switch (columnIndex){
            case 0 -> categorias.get(rowIndex).getTitulo();
            default -> categorias.get(rowIndex).getId();
        };
    }
    
}
