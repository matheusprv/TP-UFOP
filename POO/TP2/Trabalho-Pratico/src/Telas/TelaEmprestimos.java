/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JFrame.java to edit this template
 */
package Telas;

import DAO.DAOEmprestimo;
import DAO.DAOLivro;
import DAO.DAOUsuario;
import Modelo.Emprestimo;
import Modelo.Funcionario;
import Tabelas.TabelaEmprestimo;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.swing.JFormattedTextField;
import javax.swing.text.MaskFormatter;
import javax.swing.JOptionPane;

/**
 *
 * @author Pedro
 */
public class TelaEmprestimos extends javax.swing.JFrame {

    private Funcionario funcionario;
    
    MaskFormatter mfData;
    private boolean editarDeletar;
    private TabelaEmprestimo modelo;
    private DAOEmprestimo daoEmprestimo;
    /**
     * Creates new form TelaEmprestimos
     */
    public TelaEmprestimos(Funcionario funcionario) {
        try{
           mfData = new MaskFormatter("##/##/####");
        }catch(ParseException ex){
            System.out.println("Ocorreu um erro na criação da máscara de data");
        }
        
        initComponents();
        
        meuInitComponents(funcionario);
    }
    
    private void meuInitComponents(Funcionario funcionario){
        this.funcionario = funcionario;
        
        modelo = new TabelaEmprestimo();
        daoEmprestimo = new DAOEmprestimo();
       
        tableEmprestimos.setModel(modelo);
       
        habilitaDesabilitaEditarDeletar();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        txtIdUsuario = new javax.swing.JTextField();
        jLabel3 = new javax.swing.JLabel();
        txtIdLivro = new javax.swing.JTextField();
        jLabel2 = new javax.swing.JLabel();
        btnInserir = new javax.swing.JButton();
        btnEditar = new javax.swing.JButton();
        btnRemover = new javax.swing.JButton();
        jScrollPane1 = new javax.swing.JScrollPane();
        tableEmprestimos = new javax.swing.JTable();
        txtData = new javax.swing.JFormattedTextField(mfData);
        btnVoltar = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Empréstimos");

        jLabel1.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        jLabel1.setText("ID do usuário:");

        txtIdUsuario.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N

        jLabel3.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        jLabel3.setText("ID do Livro:");

        txtIdLivro.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N

        jLabel2.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        jLabel2.setText("Data do Empréstimo:");

        btnInserir.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        btnInserir.setText("Inserir");
        btnInserir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnInserirActionPerformed(evt);
            }
        });

        btnEditar.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        btnEditar.setText("Editar");
        btnEditar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnEditarActionPerformed(evt);
            }
        });

        btnRemover.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        btnRemover.setText("Remover");
        btnRemover.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRemoverActionPerformed(evt);
            }
        });

        tableEmprestimos.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {

            }
        ));
        tableEmprestimos.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                tableEmprestimosMouseClicked(evt);
            }
        });
        jScrollPane1.setViewportView(tableEmprestimos);

        txtData.addFocusListener(new java.awt.event.FocusAdapter() {
            public void focusLost(java.awt.event.FocusEvent evt) {
                txtDataFocusLost(evt);
            }
        });

        btnVoltar.setText("Voltar");
        btnVoltar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnVoltarActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap(54, Short.MAX_VALUE)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jLabel1)
                            .addComponent(jLabel2)
                            .addComponent(txtIdUsuario)
                            .addComponent(btnInserir, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(btnEditar, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(btnRemover, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jLabel3)
                            .addComponent(txtIdLivro)
                            .addComponent(txtData, javax.swing.GroupLayout.PREFERRED_SIZE, 260, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGap(28, 28, 28))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(btnVoltar)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 452, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 382, Short.MAX_VALUE))
                    .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                        .addComponent(btnVoltar)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(jLabel1)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(txtIdUsuario, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabel3)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(txtIdLivro, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabel2)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(txtData, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(btnInserir)
                        .addGap(18, 18, 18)
                        .addComponent(btnEditar)
                        .addGap(18, 18, 18)
                        .addComponent(btnRemover)))
                .addGap(12, 12, 12))
        );

        pack();
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents

    private void btnInserirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnInserirActionPerformed
        String data = txtData.getText();
        String idUsuario = txtIdUsuario.getText();
        String idLivro = txtIdLivro.getText();
        
        if(data.isBlank() || idUsuario.isBlank() || idLivro.isBlank()){
            JOptionPane.showMessageDialog(this, "Todos os campos devem estar preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
            return;
        }

        try{
            int idUser = Integer.parseInt(idUsuario);
            int idBook = Integer.parseInt(idLivro);
            if(!idsExistentes(idUser, idBook)){
                JOptionPane.showMessageDialog(this, "Não existe(m) usuário e/ou livro com esse(s) id(s).", "Erro", JOptionPane.ERROR_MESSAGE);
                return;
            }
            
            Date date = criaData(data);
            if(date == null)
                return;
            
            Emprestimo emprestimo = new Emprestimo(funcionario.getId(), idUser, idBook, date);
            this.modelo.addEmprestimo(emprestimo);
        }catch(Exception ex){
            System.err.println("\nExcecao: " + ex + "\n");
            JOptionPane.showMessageDialog(this, "Digite apenas números para os ids.", "Erro",JOptionPane.ERROR_MESSAGE);
        }

        reiniciaForm();
    }//GEN-LAST:event_btnInserirActionPerformed

    private void btnEditarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnEditarActionPerformed
        int idEmprestimo = (int) tableEmprestimos.getModel().getValueAt(tableEmprestimos.getSelectedRow(), 4);

        //Gerando o funcionario antigo
        Emprestimo antigo = daoEmprestimo.localizar(idEmprestimo);

        //Criando o novoobjeto autor
        String data = txtData.getText();
        String idUsuario = txtIdUsuario.getText();
        String idLivro = txtIdLivro.getText();
        
        if(data.isBlank() || idUsuario.isBlank() || idLivro.isBlank()){
            JOptionPane.showMessageDialog(this, "Todos os campos devem estar preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
            return;
        }
        
        try{
            int idUser = Integer.parseInt(idUsuario);
            int idBook = Integer.parseInt(idLivro);
             if(!idsExistentes(idUser, idBook)){
                JOptionPane.showMessageDialog(this, "Não existe(m) usuário e/ou livro com esse(s) id(s).", "Erro", JOptionPane.ERROR_MESSAGE);
                return;
            }
            
            Date date = criaData(data);
            if(date == null)
                return;
            
            Emprestimo novo = new Emprestimo(funcionario.getId(), idUser, idBook, date);
            this.modelo.updateEmprestimo(novo, antigo);
        }catch(Exception ex){
            System.err.println("\nExcecao: " + ex + "\n");
            JOptionPane.showMessageDialog(this, "Digite apenas números para os ids.", "Erro",JOptionPane.ERROR_MESSAGE);
        }

        reiniciaForm();
    }//GEN-LAST:event_btnEditarActionPerformed

    private void btnRemoverActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRemoverActionPerformed
        int idEmprestimo = (int) tableEmprestimos.getModel().getValueAt(tableEmprestimos.getSelectedRow(), 4);
        Emprestimo antigo = daoEmprestimo.localizar(idEmprestimo);
        this.modelo.deletarEmprestimo(antigo);
        reiniciaForm();
    }//GEN-LAST:event_btnRemoverActionPerformed
    
    private void tableEmprestimosMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_tableEmprestimosMouseClicked
        //Lendo a linha e coluna selecionada
        int linhaSelecionada = tableEmprestimos.getSelectedRow();
        
        Emprestimo emprestimo = daoEmprestimo.getLista().get(linhaSelecionada);
        
        txtIdUsuario.setText(""+emprestimo.getIdUsuario());
        txtIdLivro.setText(""+emprestimo.getIdLivro());
        
        int dia = emprestimo.getDataEmprestimo().getDay();
        int mes = emprestimo.getDataEmprestimo().getMonth();
        int ano = emprestimo.getDataEmprestimo().getYear();
        
        String data = dia +""+mes+""+ano;
        txtData.setText(data);
        
        habilitaDesabilitaEditarDeletar();
    }//GEN-LAST:event_tableEmprestimosMouseClicked

    private void txtDataFocusLost(java.awt.event.FocusEvent evt) {//GEN-FIRST:event_txtDataFocusLost
        SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
        
        try{
            Date date = sdf.parse(txtData.getText());
            txtData.setValue(sdf.format(date));
        }catch(ParseException ex){
            txtData.setFocusLostBehavior(JFormattedTextField.PERSIST);
            txtData.setText("");
            txtData.setValue(null);
        }
    }//GEN-LAST:event_txtDataFocusLost

    private void btnVoltarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnVoltarActionPerformed
        TelaMenuFuncionario tela = new TelaMenuFuncionario(funcionario);
        tela.setVisible(true);
        this.setVisible(false);
    }//GEN-LAST:event_btnVoltarActionPerformed

    private boolean idsExistentes(int idUser, int idLivro){
        DAOUsuario daoUser = new DAOUsuario();
        DAOLivro daoLivro = new DAOLivro();
        
        return daoUser.localizar(idUser) != null && daoLivro.localizar(idLivro) != null;
    }
    
    private Date criaData(String data){
        String dataStr[] = data.split("/");
        
        int dia = Integer.parseInt(dataStr[0]);
        int mes = Integer.parseInt(dataStr[1]);
        int ano = Integer.parseInt(dataStr[2]);
        
        if(dia<1 || dia>31 || mes<1 || mes>12 || ano>2023){
            JOptionPane.showMessageDialog(this, "Data inválida.", "Erro",JOptionPane.ERROR_MESSAGE);

            return null;
        }            
        
        return new Date(ano, mes, dia);
    }
    
    private void reiniciaForm(){
        txtData.setText("");
        txtIdUsuario.setText("");
        txtIdLivro.setText("");
        
        habilitaDesabilitaEditarDeletar();
        txtIdUsuario.requestFocus();
        tableEmprestimos.getSelectionModel().clearSelection();
    }
    
    private void habilitaDesabilitaEditarDeletar(){
        editarDeletar = tableEmprestimos.getSelectedRowCount() != 0;
       
       btnEditar.setEnabled(editarDeletar);
       btnRemover.setEnabled(editarDeletar);
    }
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnEditar;
    private javax.swing.JButton btnInserir;
    private javax.swing.JButton btnRemover;
    private javax.swing.JButton btnVoltar;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JTable tableEmprestimos;
    private javax.swing.JFormattedTextField txtData;
    private javax.swing.JTextField txtIdLivro;
    private javax.swing.JTextField txtIdUsuario;
    // End of variables declaration//GEN-END:variables
}
