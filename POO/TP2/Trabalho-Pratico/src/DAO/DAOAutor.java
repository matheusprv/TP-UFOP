
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
    public Autor localizar(int id) {
        List<Autor> listaAutores = Dados.getListaAutores();
        
        //Verificando se o autor esta no vetor
        for(int i = 0; i < listaAutores.size(); i++)
            if(listaAutores.get(i).getId() == id)
                return listaAutores.get(i);
        
        return null;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Autor original = (Autor) objOriginal;
        Autor novo = (Autor) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.getListaAutores().indexOf(original);
        if(index == -1) return;
        
        Dados.getListaAutores().set(index, novo);
        
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        
        Dados.getListaAutores().remove((Autor)obj);
    }

    @Override
    public List<Autor> getLista() {
        return Dados.getListaAutores();
    }
    
}
