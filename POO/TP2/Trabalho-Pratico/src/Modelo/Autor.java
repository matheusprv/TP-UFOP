package Modelo;

public class Autor extends Pessoa {
    private String biografia;

    public Autor(String biografia, int id, String nome, String sobreNome) {
        super(id, nome, sobreNome);
        this.biografia = biografia;
    }

    public String getBiografia() {
        return biografia;
    }

    public void setBiografia(String biografia) {
        this.biografia = biografia;
    }
}