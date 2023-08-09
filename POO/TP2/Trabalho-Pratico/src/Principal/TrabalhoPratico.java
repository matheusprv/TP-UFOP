
package Principal;

import Dados.Dados;
import Telas.TelaLoginFuncionario;


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
        
        TelaLoginFuncionario tela = new TelaLoginFuncionario();
        tela.setVisible(true);
        
    }
    
}
