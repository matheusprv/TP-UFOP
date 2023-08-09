/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package DAO;

import Dados.Dados;
import Modelo.Autor;
import Modelo.Categoria;
import Modelo.Livro;
import java.util.List;

/**
 *
 * @author mathe
 */
public class DAOLivro implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Livro livros = (Livro) obj;
        List<Livro> listaLivros = Dados.getListaLivros();
        listaLivros.add(livros);
    }

    public Livro localizar(int id) {        
        int i;
        for(i = 0; i < Dados.getListaLivros().size(); i++)
            if(Dados.getListaLivros().get(i).getId() == id)
                return Dados.getListaLivros().get(i);
    
        return null;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Livro original = (Livro) objOriginal;
        Livro novo = (Livro) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.getListaLivros().indexOf(original);
        if(index == -1) return;

        Dados.getListaLivros().set(index, novo);
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        Dados.getListaLivros().remove((Livro)obj);
    }

    @Override
    public List<Livro> getLista() {
        return Dados.getListaLivros();
    }
    
    public void adicionarCategoria(int id, Categoria categoria){
        Livro livro = localizar(id);
        livro.adicionarCategoria(categoria);
    }
    
    public void removerCategoria(int id, Categoria categoria){
        Livro livro = localizar(id);
        livro.removerCategoria(categoria);
    }
    
    public void adicionarAutor(int id, Autor autor){
        Livro livro = localizar(id);
        livro.adicionarAutor(autor);
    }
    
    public void removerAutor(int id, Autor autor){
        Livro livro = localizar(id);
        livro.removerAutor(autor);
    }
    
}
