package plastiform;

import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.text.ParseException;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFormattedTextField;
import javax.swing.JFormattedTextField.AbstractFormatter;
import javax.swing.JFormattedTextField.AbstractFormatterFactory;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.Border;
import javax.swing.text.InternationalFormatter;
import javax.swing.text.MaskFormatter;

public class AgregarForma extends JFrame {
	
	private static final String [] colores = new String [] {"Amarillo", "Azul", "Blanco", "Naranja", "Negro", "Rojo", "Verde", "Violeta", "Otro..."};
	private JButton aceptarBoton;


	public AgregarForma(DefaultListModel<Forma> lf, PanelPrincipal pp) {
		
		
		CreadorIconos ci = new CreadorIconos();
		
		Pantalla p = new Pantalla();
		this.setTitle("Agregar forma");
		this.setBounds(p.posXBound(400), p.posYBound(150), 400, 150);
		this.setVisible(true);
		this.setResizable(false);
		
		JPanel jpentero = new JPanel();
		jpentero.setLayout(new BoxLayout(jpentero, BoxLayout.Y_AXIS));
		
		JPanel jp = new JPanel();
		
		Border padding = BorderFactory.createEmptyBorder(20, 20, 20, 20);
		jp.setBorder(padding);
		GridLayout gl = new GridLayout(2,4);
		jp.setSize(new Dimension(60,150));
		gl.preferredLayoutSize(jp);
		jp.setLayout(gl);
		
		
		
		jp.add(new JLabel("Forma:"));
		JComboBox formasJcb = new JComboBox(Forma.formas);
		formasJcb.setSelectedIndex(0);
		
		jp.add(new JLabel("Color:"));
		JComboBox coloresJcb = new JComboBox(colores);
		coloresJcb.setSelectedIndex(0);
		
		JLabel param1Label = new JLabel("Base:");
		JLabel param2Label = new JLabel("Altura:");
		JTextField param1Field = new JTextField(10);
		JTextField param2Field = new JTextField(10);
		
		formasJcb.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				int index = formasJcb.getSelectedIndex();
				switch(index) {
				case 0: param1Label.setText("Base:");
						param2Label.setText("Altura:");
						break;
						
				case 1: param1Label.setText("Base:");
						param2Label.setText("Altura:");
						break;
						
				case 2: param1Label.setText("Radio:");
						param2Label.setText("N/A");
						break;
				case 3: param1Label.setText("Lado:");
						param2Label.setText("N/A");
						break;
				case 4:	param1Label.setText("Radio:");
						param2Label.setText("Altura:");
						break;
				default: break;
				}
				
				if(index == 2 || index == 3) {
					param2Field.setEditable(false);
				}else {
					if(!param2Field.isEditable()) {
						param2Field.setEditable(true);
					}
				}
				
				param1Field.setText("");
				param2Field.setText("");
				setIconImage(ci.getIcono(coloresJcb.getSelectedItem().toString(), formasJcb.getSelectedItem().toString()));
			}
			
		});
		
		coloresJcb.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent arg0) {
				int index = coloresJcb.getSelectedIndex();
				if(index == 8) {
					coloresJcb.setEditable(true);
					coloresJcb.setSelectedItem("");
				}else if(index>=0 && index<=7){
					coloresJcb.setEditable(false);
				}
				
				param1Field.setText("");
				param2Field.setText("");
				setIconImage(ci.getIcono(coloresJcb.getSelectedItem().toString(), formasJcb.getSelectedItem().toString()));
			}
			
		});
		
	
		
		aceptarBoton = new JButton("Agregar");
		JButton cancelarBoton = new JButton("Listo");
		
		aceptarBoton.setFocusable(false);
		cancelarBoton.setFocusable(false);
		
		aceptarBoton.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				boolean todoOk = true;
				String color = new String();
				String forma = new String();
				double p1 = 0;
				double p2 = 0;
				try {
					color = coloresJcb.getSelectedItem().toString();
					forma = formasJcb.getSelectedItem().toString();
					String auxP1 = param1Field.getText().replace(',', '.');
					p1 = Double.parseDouble(auxP1);
					if(p1<=0) {
						throw new IndexOutOfBoundsException("p1 no puede ser menor o igual a 0");
					}
					if(param2Field.isEditable()) {
						String auxP2 = param2Field.getText().replace(',', '.');
						p2 = Double.parseDouble(auxP2);
						if(p2<=0) {
							throw new IndexOutOfBoundsException("p2 no puede ser menor o igual a 0");
						}
					}
				}catch(Exception e) {
					JOptionPane.showMessageDialog(null, "Error en los parámetros ingresados\nNo se pudo ingresar al lote");
					todoOk = false;
				}
				
				param1Field.setText("");
				param2Field.setText("");
				
				if(color.isEmpty()) {
					JOptionPane.showMessageDialog(null, "El campo de color no puede quedar vacío");
					todoOk =  false;
				}
				
				if(todoOk) {
					agregarForma(lf, forma, color, p1, p2);
					pp.actualizarFilaAgregada();
					Ventana.setCambios(true);
				}
				
				formasJcb.requestFocus();
			}
			
		});
		
		cancelarBoton.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				dispose();				
			}
			
		});
		
		jp.add(param1Label);
		jp.add(param2Label);
		
		jp.add(formasJcb);
		jp.add(coloresJcb);
		jp.add(param1Field);
		jp.add(param2Field);
		
		
		JPanel jp2 = new JPanel();
		
		jp2.add(aceptarBoton);
		jp2.add(cancelarBoton);
		
		jpentero.add(jp);
		jpentero.add(jp2);
		
		this.add(jpentero);
		
		setIconImage(ci.getIcono(coloresJcb.getSelectedItem().toString(), formasJcb.getSelectedItem().toString()));
		
		this.getRootPane().setDefaultButton(aceptarBoton);

	}
	
	private void agregarForma(DefaultListModel<Forma> listaFormas, String forma, String color, double p1, double p2) {
		
		if(forma.equalsIgnoreCase("triangulo")) {
			listaFormas.addElement(new Triangulo(p1, p2, color));
		}else if (forma.equalsIgnoreCase("rectangulo")) {
			listaFormas.addElement(new Rectangulo(p1, p2, color));
		}else if(forma.equalsIgnoreCase("circulo")) {
			listaFormas.addElement(new Circulo(p1, color));
		}else if(forma.equalsIgnoreCase("cubo")) {
			listaFormas.addElement(new Cubo(p1, color));
		}else if(forma.equalsIgnoreCase("cilindro")) {
			listaFormas.addElement(new Cilindro(p1, p2, color));
		}
		
	}
	
}
