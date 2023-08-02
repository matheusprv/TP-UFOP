package Dados;

import Modelo.*;
import java.util.ArrayList;
import java.util.List;


public class Dados {
    private static List<Funcionario> listaFuncionarios;
    private static List<Usuario> listaUsuarios;
    private static List<Autor> listaAutores;
    private static List<Livro> listaLivros;
    private static List<Categoria> listaCategorias;
    private static List<Emprestimo> listaEmprestimos;
    
    
    public Dados(){
        this.listaFuncionarios = new ArrayList<>();
        this.listaUsuarios = new ArrayList<>();
        this.listaAutores = new ArrayList<>();
        this.listaLivros = new ArrayList<>();
        this.listaCategorias = new ArrayList<>();
        this.listaEmprestimos = new ArrayList<>();
    }

    public static List<Funcionario> getListaFuncionarios() {
        return listaFuncionarios;
    }

    public static List<Usuario> getListaUsuarios() {
        return listaUsuarios;
    }

    public static List<Autor> getListaAutores() {
        return listaAutores;
    }

    public static List<Livro> getListaLivros() {
        return listaLivros;
    }

    public static List<Categoria> getListaCategorias() {
        return listaCategorias;
    }

    public static List<Emprestimo> getListaEmprestimos() {
        return listaEmprestimos;
    }
    
    
    
}
