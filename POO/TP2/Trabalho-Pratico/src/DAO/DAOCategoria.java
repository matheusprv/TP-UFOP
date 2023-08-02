
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
    public void atualizar(Object original, Object novo) {
        throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    @Override
    public void remover(Object obj) {
        List <Categoria> listaCategoria = Dados.getListaCategorias();
        
        Categoria itemRemover = (Categoria) obj;
        
        int index = localizar(itemRemover.getId());
        if(index == -1) return;
        
        listaCategoria.remove(index);
    }

    @Override
    public List<Object> getLista() {
        return (List<Object>) (Object) Dados.getListaCategorias();
    }
    
}
