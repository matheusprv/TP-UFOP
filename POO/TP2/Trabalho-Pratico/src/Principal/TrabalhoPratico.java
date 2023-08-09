
package Principal;

import Modelo.Autor;
import Dados.Dados;
import Modelo.Categoria;
import DAO.*;
import Telas.MenuPrincipal;
import Telas.TelaAutor;
import Telas.TelaCategorias;
import java.util.ArrayList;


public class TrabalhoPratico {


    public static void main(String[] args) {
        Dados dados = new Dados();
        
        /*DAOCategoria daoCategoria = new DAOCategoria();
        daoCategoria.incluir(new Categoria("Titulo"));
        daoCategoria.incluir(new Categoria("Titulo1"));
        daoCategoria.incluir(new Categoria("Titulo2"));
        daoCategoria.incluir(new Categoria("Titulo3"));
        
        TelaCategorias categoria = new TelaCategorias();
        categoria.setVisible(true);*/
        
        TelaAutor tela = new TelaAutor();
        tela.setVisible(true);
        
    }
    
}
