
package Principal;

import DAO.DAOCategoria;
import DAO.DAOLivro;
import Dados.Dados;
import Modelo.Categoria;
import Modelo.Livro;
import Telas.TelaCategorias;
import Telas.TelaLivros;
import Telas.TelaLoginFuncionario;


public class TrabalhoPratico {


    public static void main(String[] args) {
        Dados dados = new Dados();
        
        DAOCategoria daoCategoria = new DAOCategoria();
        Categoria cat1 = new Categoria("Titulo");
        Categoria cat2 = new Categoria("Titulo1");

        daoCategoria.incluir(cat1);
        daoCategoria.incluir(cat2);
        daoCategoria.incluir(new Categoria("Titulo2"));
        daoCategoria.incluir(new Categoria("Titulo3"));
        
        Livro livro = new Livro("Um titulo");
        livro.adicionarCategoria(cat1);
        livro.adicionarCategoria(cat2);
        
        DAOLivro daoLivro = new DAOLivro();
        daoLivro.incluir(livro);

        
        TelaLivros categoria = new TelaLivros();
        categoria.setVisible(true);
        
        /*TelaLoginFuncionario tela = new TelaLoginFuncionario();
        tela.setVisible(true);*/
        
    }
    
}
