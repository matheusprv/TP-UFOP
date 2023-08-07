
package DAO;

import Dados.Dados;
import Modelo.Categoria;
import java.util.List;


public class DAOCategoria implements DAOInterface {

    @Override
    public void incluir(Object obj) {
        Categoria Categoria = (Categoria) obj;
        List<Categoria> listaCategorias = Dados.getListaCategorias();
        listaCategorias.add(Categoria);    
    }

    @Override
    public int localizar(int id) {
        List <Categoria> listaCategoria = Dados.getListaCategorias();
        
        for(int i = 0; i < listaCategoria.size(); i++)
            if(listaCategoria.get(i).getId() == id)
                return i;
        
        return -1;
    }

    @Override
    public void atualizar(Object objOriginal, Object objNovo) {
        Categoria original = (Categoria) objOriginal;
        Categoria novo = (Categoria) objNovo;
        
        if(original.equals(objNovo)) return;
        
        if(novo == null || original == null) return;
        
        int index = Dados.getListaCategorias().indexOf(original);
        if(index == -1) return;
        
        Dados.getListaCategorias().set(index, novo);
    }

    @Override
    public void remover(Object obj) {
        if(obj == null) return;
        Dados.getListaCategorias().remove(obj);
    }

    @Override
    public List<Categoria> getLista() {
        return Dados.getListaCategorias();
    }
    
}
