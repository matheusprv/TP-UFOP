
package DAO;

import Dados.Dados;
import Modelo.Autor;
import java.util.List;


public class DAOAutor implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Autor autor = (Autor) obj;
        Dados.listaAutores.add(autor);
    }

    @Override
    public Autor localizar(int id) {
        List<Autor> listaAutores = Dados.listaAutores;
        
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
        
        int index = Dados.listaAutores.indexOf(original);
        if(index == -1) return;
        
        //Dados.listaAutores.set(index, novo);
        
        Dados.listaAutores.get(index).setBiografia(novo.getBiografia());
        Dados.listaAutores.get(index).setNome(novo.getNome());
        Dados.listaAutores.get(index).setSobreNome(novo.getSobreNome());

        
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        
        Dados.listaAutores.remove((Autor)obj);
    }

    @Override
    public List<Autor> getLista() {
        return Dados.listaAutores;
    }
    
}
