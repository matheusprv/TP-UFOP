
package Principal;

import Modelo.Autor;
import Dados.Dados;
import Modelo.Categoria;
import DAO.*;
import Telas.MenuPrincipal;
import Telas.TelaCategorias;
import java.util.ArrayList;


public class TrabalhoPratico {


    public static void main(String[] args) {
        Dados dados = new Dados();
        /*DAOAutor daoAutor = new DAOAutor();
                
        Autor a1 = new Autor("Biografia", 0, "Nome", "Sobrenome");
        Autor a2 = new Autor("Biografia2", 1, "Nome2", "Sobrenome2");
        
        //Inserindo dados
        daoAutor.incluir(a1);
        daoAutor.incluir(a2);
        
        for(Autor a : Dados.getListaAutores()){
            System.out.println(a.toString());
        }
        
        //Localizando
        System.out.println(daoAutor.localizar(a2.getId()));
        
        //Atualizando
        Autor a3 = new Autor("Biografia3", 2, "Nome3", "Sobrenome3");
        daoAutor.atualizar(a2, a3);
        for(Autor a : Dados.getListaAutores()){
            System.out.println(a.toString());
        }
        System.out.println("\n");
            
        //Removendo
        daoAutor.remover(a3);
        for(Autor a : Dados.getListaAutores()){
            System.out.println(a.toString());
        }
        
        System.out.println("\n");
        
        for(Autor a : daoAutor.getLista()){
            System.out.println(a.toString());
        }*/
        
        /*MenuPrincipal menu = new MenuPrincipal();
        menu.setVisible(true);*/
        
        TelaCategorias categoria = new TelaCategorias();
        categoria.setVisible(true);
        
    }
    
}
