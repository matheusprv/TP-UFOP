/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package DAO;

import Dados.Dados;
import Modelo.Usuario;
import java.util.List;

/**
 *
 * @author mathe
 */
public class DAOUsuario implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Usuario usuario = (Usuario) obj;
        Dados.getListaUsuarios().add(usuario);
    }

    @Override
    public Usuario localizar(int id) {
        int i;
        for(i = 0; i < Dados.getListaUsuarios().size(); i++){
            if(Dados.getListaUsuarios().get(i).getId() == id)
                return Dados.getListaUsuarios().get(i);
        }
        return null;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Usuario original = (Usuario) objOriginal;
        Usuario novo = (Usuario) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.getListaUsuarios().indexOf(original);
        if(index == -1) return;
        
        Dados.getListaUsuarios().set(index, novo);
    }

    @Override
    public void remover(Object obj) {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    @Override
    public List<Object> getLista() {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }
    
}
