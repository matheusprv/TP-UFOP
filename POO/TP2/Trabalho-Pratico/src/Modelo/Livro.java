package Modelo;

import java.util.ArrayList;
import java.util.List;

public class Livro {
    private int id;
    private String titulo;
    private List<Integer> categoria;
    private List<String> autor;

    public Livro(int id, String titulo) {
        this.id = id;
        this.titulo = titulo;
        this.categoria = new ArrayList<>();
        this.autor = new ArrayList<>();
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public List<Integer> getCategoria() {
        return categoria;
    }

    public void setCategoria(List<Integer> categoria) {
        this.categoria = categoria;
    }

    public List<String> getAutor() {
        return autor;
    }

    public void setAutor(List<String> autor) {
        this.autor = autor;
    }

    
    
    
}
