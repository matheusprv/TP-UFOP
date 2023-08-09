/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JFrame.java to edit this template
 */
package Telas;

import DAO.DAOCategoria;
import Modelo.Categoria;
import Tabelas.TabelaCategoria;
import javax.swing.JOptionPane;
import javax.swing.table.DefaultTableModel;

/**
 *
 * @author mathe
 */
public class TelaCategorias extends javax.swing.JFrame {

    private boolean editarDeletar;
    private int linhaSelecionada;
    private DAOCategoria daoCategoria;
    
    TabelaCategoria modelo;
    
    /**
     * Creates new form Categorias
     */
    public TelaCategorias() {
        initComponents();
        meuInitComponents();
    }
    
    private void meuInitComponents(){
        modelo = new TabelaCategoria();
        tableCategorias.setModel(modelo);
        this.linhaSelecionada = -1;
        this.daoCategoria = new DAOCategoria();
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

        jLabel2 = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        tableCategorias = new javax.swing.JTable();
        txtTituloCategoria = new javax.swing.JTextField();
        btnInserir = new javax.swing.JButton();
        btnRemover = new javax.swing.JButton();
        btnEditar = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Categoria");

        jLabel2.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        jLabel2.setText("Título da Categoria:");

        tableCategorias.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        tableCategorias.setModel(new javax.swing.table.DefaultTableModel(
            new Object [][] {

            },
            new String [] {
                "Título", "ID"
            }
        ) {
            Class[] types = new Class [] {
                java.lang.String.class, java.lang.Integer.class
            };
            boolean[] canEdit = new boolean [] {
                false, false
            };

            public Class getColumnClass(int columnIndex) {
                return types [columnIndex];
            }

            public boolean isCellEditable(int rowIndex, int columnIndex) {
                return canEdit [columnIndex];
            }
        });
        tableCategorias.getTableHeader().setReorderingAllowed(false);
        tableCategorias.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                tableCategoriasMouseClicked(evt);
            }
        });
        jScrollPane2.setViewportView(tableCategorias);
        if (tableCategorias.getColumnModel().getColumnCount() > 0) {
            tableCategorias.getColumnModel().getColumn(1).setResizable(false);
        }

        txtTituloCategoria.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N

        btnInserir.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        btnInserir.setText("Inserir");
        btnInserir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnInserirActionPerformed(evt);
            }
        });

        btnRemover.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        btnRemover.setText("Deletar");
        btnRemover.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRemoverActionPerformed(evt);
            }
        });

        btnEditar.setFont(new java.awt.Font("Segoe UI", 0, 18)); // NOI18N
        btnEditar.setText("Editar");
        btnEditar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnEditarActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(22, 22, 22)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jLabel2)
                    .addComponent(txtTituloCategoria)
                    .addComponent(btnInserir, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(btnRemover, javax.swing.GroupLayout.DEFAULT_SIZE, 250, Short.MAX_VALUE)
                    .addComponent(btnEditar, javax.swing.GroupLayout.DEFAULT_SIZE, 250, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 70, Short.MAX_VALUE)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 452, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE)
            .addGroup(layout.createSequentialGroup()
                .addGap(118, 118, 118)
                .addComponent(jLabel2)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(txtTituloCategoria, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addComponent(btnInserir)
                .addGap(18, 18, 18)
                .addComponent(btnEditar)
                .addGap(18, 18, 18)
                .addComponent(btnRemover)
                .addContainerGap(70, Short.MAX_VALUE))
        );

        pack();
        setLocationRelativeTo(null);
    }// </editor-fold>//GEN-END:initComponents

    Categoria inputNovaCategoria(){
        String tituloCategoria = txtTituloCategoria.getText();
        if(tituloCategoria.isBlank()){
            JOptionPane.showMessageDialog(this, "O campo do título não pode ser nulo.", "Erro", JOptionPane.ERROR_MESSAGE);
            return null;
        }
                
        return new Categoria(tituloCategoria);
    }
   
    
    private void btnInserirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnInserirActionPerformed
        
        Categoria novaCategoria = inputNovaCategoria();
        if(novaCategoria == null) return;
        this.modelo.addCategoria(novaCategoria);
        reiniciaForm();
        
    }//GEN-LAST:event_btnInserirActionPerformed

    private void tableCategoriasMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_tableCategoriasMouseClicked
        //Lendo a linha e coluna selecionada
        linhaSelecionada = tableCategorias.getSelectedRow();

        //Alterando o texto do textField
        String texto = (String) tableCategorias.getModel().getValueAt(linhaSelecionada, 0);
        txtTituloCategoria.setText(texto);
        
        habilitaDesabilitaEditarDeletar();
    }//GEN-LAST:event_tableCategoriasMouseClicked

    private void btnRemoverActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRemoverActionPerformed
        int idCategoria = (int) tableCategorias.getModel().getValueAt(linhaSelecionada, 1);        
        Categoria selecionada = daoCategoria.localizar(idCategoria);
        this.modelo.deletarCategoria(selecionada);
        
        reiniciaForm();
    }//GEN-LAST:event_btnRemoverActionPerformed

    private void btnEditarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnEditarActionPerformed
        
        int idCategoria = (int) tableCategorias.getModel().getValueAt(linhaSelecionada, 1);
        
        //Gerando a categoria antiga
        Categoria antiga = daoCategoria.localizar(idCategoria);
        
        //Criando o novo objeto de categoria
        //A função inputNovaCategoria nao e utilizada pois e necessario nao atualizar o valor do id
        String tituloCategoria = txtTituloCategoria.getText();
        if(tituloCategoria.isBlank()){
            JOptionPane.showMessageDialog(this, "O campo do título não pode ser nulo.", "Erro", JOptionPane.ERROR_MESSAGE);
            return;
        }
        Categoria novo = new Categoria(tituloCategoria, idCategoria);
        
        //Atualizando o item na tabela e no banco de dados
        this.modelo.updateCategoria(novo, antiga);
        
        reiniciaForm();
    }//GEN-LAST:event_btnEditarActionPerformed

    private void reiniciaForm(){
        txtTituloCategoria.setText("");
        habilitaDesabilitaEditarDeletar();
        txtTituloCategoria.requestFocus();
        tableCategorias.getSelectionModel().clearSelection();
    }
    
    private void habilitaDesabilitaEditarDeletar(){
       if(tableCategorias.getSelectedRowCount() == 0) editarDeletar = false;
       else editarDeletar = true;
       
       btnEditar.setEnabled(editarDeletar);
       btnRemover.setEnabled(editarDeletar);
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(TelaCategorias.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(TelaCategorias.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(TelaCategorias.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(TelaCategorias.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new TelaCategorias().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnEditar;
    private javax.swing.JButton btnInserir;
    private javax.swing.JButton btnRemover;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JTable tableCategorias;
    private javax.swing.JTextField txtTituloCategoria;
    // End of variables declaration//GEN-END:variables
}
