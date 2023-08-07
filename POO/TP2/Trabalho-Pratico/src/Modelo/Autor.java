package Modelo;

import java.util.Objects;

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
        final Autor other = (Autor) obj;
        return Objects.equals(this.biografia, other.biografia);
    }

    @Override
    public String toString() {
        return super.toString() + " | Autor{" + "biografia=" + biografia + '}';
    }
    
    
}