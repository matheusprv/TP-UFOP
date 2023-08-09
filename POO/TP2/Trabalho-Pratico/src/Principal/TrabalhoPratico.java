
package Principal;

import DAO.DAOAutor;
import DAO.DAOCategoria;
import DAO.DAOFuncionario;
import DAO.DAOLivro;
import DAO.DAOUsuario;
import Dados.Dados;
import Modelo.Autor;
import Modelo.Categoria;
import Modelo.Funcionario;
import Modelo.Livro;
import Modelo.Usuario;
import Telas.MenuPrincipal;
import Telas.TelaCategorias;
import Telas.TelaEmprestimos;
import Telas.TelaLivros;


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


        Autor a1 = new Autor("biografia", "nome", "sobrenome");
        Autor a2 = new Autor("bio", "no", "sobre");

        DAOAutor daoAutor = new DAOAutor();
        daoAutor.incluir(a1);
        daoAutor.incluir(a2);

        MenuPrincipal menuPrincipal = new MenuPrincipal();
        menuPrincipal.setVisible(true);
        
        /*TelaLivros categoria = new TelaLivros();
        categoria.setVisible(true);*/
        
        /*TelaLoginFuncionario tela = new TelaLoginFuncionario();
        tela.setVisible(true);
        
        
        
        DAOUsuario daoUser = new DAOUsuario();
        daoUser.incluir(new Usuario(10, "Andre", "Oliveira"));
        
        DAOLivro daoLivro = new DAOLivro();
        daoLivro.incluir(new Livro("teste"));
        
        DAOFuncionario daoFunc = new DAOFuncionario();
        daoFunc.incluir(new Funcionario(10, "Jose", "Silva"));
        
        
        TelaEmprestimos tela = new TelaEmprestimos();
        tela.setVisible(true);*/
    }
    
}
