package DAO;

import java.util.List;


public interface DAOInterface {
    public void incluir(Object obj);
    public int localizar(int id);
    public void atualizar(Object original, Object novo);
    public void remover(Object obj);
    public List<Object> getLista();
}
