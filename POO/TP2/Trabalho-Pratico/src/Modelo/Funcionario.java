
package Modelo;


public class Funcionario extends Pessoa {
    private int matricula;

    public Funcionario(int matricula, int id, String nome, String sobreNome) {
        super(id, nome, sobreNome);
        this.matricula = matricula;
    }   
    
    public int getMatricula() {
        return matricula;
    }

    public void setMatricula(int matricula) {
        this.matricula = matricula;
    }
}
