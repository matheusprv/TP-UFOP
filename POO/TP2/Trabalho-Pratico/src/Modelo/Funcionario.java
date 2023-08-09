
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
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        final Funcionario other = (Funcionario) obj;
        return super.equals(other) && this.matricula == other.matricula;
    }
}
