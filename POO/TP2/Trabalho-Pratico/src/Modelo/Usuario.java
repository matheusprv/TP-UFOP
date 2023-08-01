package Modelo;

public class Usuario extends Pessoa{
    private int regAcademico;

    public Usuario(int regAcademico, int id, String nome, String sobreNome) {
        super(id, nome, sobreNome);
        this.regAcademico = regAcademico;
    }

    public int getRegAcademico() {
        return regAcademico;
    }

    public void setRegAcademico(int regAcademico) {
        this.regAcademico = regAcademico;
    }
}