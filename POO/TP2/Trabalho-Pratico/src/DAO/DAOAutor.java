
package DAO;

import Dados.Dados;
import Modelo.Autor;
import java.util.List;


public class DAOAutor implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Autor autor = (Autor) obj;
        List<Autor> listaAutores = Dados.getListaAutores();
        listaAutores.add(autor);
    }

    @Override
    public int localizar(int id) {
        List<Autor> listaAutores = Dados.getListaAutores();
        
        //Verificando se o autor esta no vetor
        for(int i = 0; i < listaAutores.size(); i++)
            if(listaAutores.get(i).getId() == id)
                return i;
        
        return -1;
    }

    @Override
    public void atualizar(Object original, Object novo) {
        Autor autorOriginal = (Autor) original;
        Autor autorNovo = (Autor) novo;
        
        List<Autor> listaAutores = Dados.getListaAutores();
        
        //Procurando o index do elemento 
        int index = localizar(autorOriginal.getId());
        if(index == -1) return;
        
        listaAutores.get(index).setId(autorNovo.getId());
        
        //Terminar atualizar

    }

    @Override
    public void remover(Object obj) {
        List<Autor> listaAutores = Dados.getListaAutores();
        
        Autor itemRemover = (Autor) obj;
        
        //Procurando o index do elemento 
        int index = localizar(itemRemover.getId());
        if(index == -1) return;
        
        listaAutores.remove(index);
    }

    @Override
    public List<Object> getLista() {
        return (List<Object>) (Object) Dados.getListaAutores();
    }
    
}
