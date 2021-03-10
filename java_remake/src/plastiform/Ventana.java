package plastiform;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

import javax.imageio.ImageIO;
import javax.print.DocFlavor.URL;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.DefaultListModel;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.event.ListDataEvent;
import javax.swing.event.ListDataListener;

public class Ventana extends JFrame{

	private DefaultListModel<Forma> lf;
	private PanelPrincipal pp;
	private static boolean cambios;
	private JMenuItem guardarItem;
	private LectorTxt lTxt;
	private parteSuperior ps;
	
	public Ventana(int ancho, int alto, String titulo, DefaultListModel<Forma> lf) {
		
		this.lf = lf;
		boolean cambios = false;
		Pantalla p = new Pantalla();
		
		//seteo ventana
		this.setTitle(titulo);
		this.setBounds(p.posXBound(ancho), p.posYBound(alto), ancho, alto);
		this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		//this.setResizable(false);
		
		//le agrego el icono
		Toolkit t = Toolkit.getDefaultToolkit();
		Image miIcono = t.getImage(getClass().getResource("icon.png"));
		this.setIconImage(miIcono);
		
		//le agrego el panel
		JMenu menu1 = new JMenu("Archivo");
		JMenu menu2 = new JMenu("Ordenar");
		JMenu menu3 = new JMenu("Ayuda");
		
		JMenuItem cargarItem = new JMenuItem("Cargar lote", getIconoToolbar("cargar"));
		guardarItem = new JMenuItem("Guardar lote", getIconoToolbar("guardar"));
		JMenuItem vaciarItem = new JMenuItem("Vaciar lote", getIconoToolbar("nuevo"));
		JMenuItem imprimirItem = new JMenuItem("Imprimir", getIconoToolbar("imprimir"));
		JMenuItem salirItem = new JMenuItem("Salir", getIconoToolbar("salir"));
		JRadioButtonMenuItem ingresoItem = new JRadioButtonMenuItem("Por ingreso", true);
		JRadioButtonMenuItem colorItem = new JRadioButtonMenuItem("Por color", false);
		JRadioButtonMenuItem tipoItem = new JRadioButtonMenuItem("Por tipo forma", false);
		JRadioButtonMenuItem areaItem = new JRadioButtonMenuItem("Por tamaño área", false);
		JMenuItem formatoItem = new JMenuItem("Formato de lotes", getIconoToolbar("formato"));
		JMenuItem acercaItem = new JMenuItem("Acerca de...", getIconoToolbar("acerca"));
		ButtonGroup grupoOrden = new ButtonGroup();
		
		menu1.add(cargarItem);
		menu1.add(guardarItem);
		menu1.add(vaciarItem);
		menu1.add(imprimirItem);
		menu1.add(salirItem);
		menu2.add(ingresoItem);
		grupoOrden.add(ingresoItem);
		menu2.add(colorItem);
		grupoOrden.add(colorItem);
		menu2.add(tipoItem);
		grupoOrden.add(tipoItem);
		menu2.add(areaItem);
		grupoOrden.add(areaItem);
		menu3.add(formatoItem);
		menu3.add(acercaItem);
		
		JMenuBar barra = new JMenuBar();
		barra.add(menu1);
		barra.add(menu2);
		barra.add(menu3);
		this.setJMenuBar(barra);
		
		JPanel panelVentana = new JPanel();
		panelVentana.setLayout(new BoxLayout(panelVentana, BoxLayout.Y_AXIS));
		
		ps = new parteSuperior();
		parteInferior pi = new parteInferior();
		pp = new PanelPrincipal(lf, pi);
		
		pi.actualizar();
		
		panelVentana.add(ps);
		panelVentana.add(pp);
		panelVentana.add(pi);	
		
		this.add(panelVentana);
		
		lTxt = new LectorTxt(lf, pp.getTabla());
		cargarItem.addActionListener(lTxt);
		guardarItem.addActionListener(new EscritorTxt(lf));

		ingresoItem.addActionListener(new ListenerOrden(-1));	
		colorItem.addActionListener(new ListenerOrden(2));		
		tipoItem.addActionListener(new ListenerOrden(1));
		areaItem.addActionListener(new ListenerOrden(5));
		
		imprimirItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				pp.imprimirTabla();
			}
		});
		
		vaciarItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(Ventana.cambios==true && (!lf.isEmpty())) {
					Object[] options = {"Guardar","No guardar","Cancelar"};
					int tipoPanel = JOptionPane.YES_NO_CANCEL_OPTION;
				    int opcion = JOptionPane.showOptionDialog (null,"¿Querés guardar los cambios antes de vaciar el lote?","Confirmación para vaciar", tipoPanel, JOptionPane.QUESTION_MESSAGE, null, options, options[0]);
				    if(opcion==JOptionPane.YES_OPTION) {
				    	guardarItem.doClick();
				    }
				    if(opcion==JOptionPane.CANCEL_OPTION) {
						return;
				    }
				}
				
				lTxt.setLeyendo(true);
				lf.clear();
				pp.actualizarTabla();
				lTxt.setLeyendo(false);
				pp.actualizarTabla();
				Ventana.cambios=false;
			}
		});
		
		formatoItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(null, "El programa acepta archivos .txt con elementos en el siguiente formato:\n<tipoforma> <color> <parametro1> ; <parametro2>\n\nSin distinción de mayúsculas ni tildes.\nPor ejemplo: triangulo rojo 5,25 ; 3");
			}
		});
		
		acercaItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ImageIcon ii = new ImageIcon(miIcono.getScaledInstance(64, 64, Image.SCALE_DEFAULT));
				JOptionPane.showMessageDialog(null, "Hecho por Julián Castro para\npracticar Java en cuarentena\n28.7.20", "Acerca de PlastiForm", JOptionPane.INFORMATION_MESSAGE, ii);
			}
		});
		
		//listeners para salir
		this.addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent we) {
				salir();
			}
		});
		salirItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				salir();
			}
		});
		
		  new  FileDrop(this, new FileDrop.Listener(){
			  
			  public void  filesDropped( java.io.File[] files ){   
				  boolean decision = lTxt.comprobar();
				  if(decision) {
					  for(File f : files) {
						  if(f.getName().endsWith(".txt")) {
							  lTxt.leerArchivo(f);
						  }else {
							  JOptionPane.showMessageDialog(null, "Solo se aceptan archivos formato .txt", "Formato inválido", JOptionPane.INFORMATION_MESSAGE);
						  }
			          }
				  }
			  }
		  });
		
	}

	
	private void salir() {
		if(cambios==true && (!lf.isEmpty())) {
			Object[] options = {"Guardar","No guardar","Cancelar"};
			int tipoPanel = JOptionPane.YES_NO_CANCEL_OPTION;
		    int opcion = JOptionPane.showOptionDialog (null,"¿Querés guardar los cambios antes de salir?","Confirmación para salir", tipoPanel, JOptionPane.QUESTION_MESSAGE, null, options, options[0]);
		    if(opcion==JOptionPane.YES_OPTION) {
		    	guardarItem.doClick();
		    	System.exit(0);
		    }
		    if(opcion==JOptionPane.NO_OPTION) {
				System.exit(0);
		    }
		}else {
			System.exit(0);
		}
	}
	
	
	class parteSuperior extends JPanel implements ActionListener {
		
		private ArrayList<JCheckBox> jcb;
		private JButton todosBoton;
		
		public parteSuperior() {
			
			this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
			this.setMaximumSize(new Dimension(600,80));
			
			//PANEL SUPERIOR
			JPanel jps = new JPanel();
			jcb = new ArrayList<JCheckBox>();
			
			todosBoton = new JButton("Todos");
			jcb.add(new JCheckBox("Triangulo", true));
			jcb.add(new JCheckBox("Rectangulo", true));
			jcb.add(new JCheckBox("Circulo", true));
			jcb.add(new JCheckBox("Cubo", true));
			jcb.add(new JCheckBox("Cilindro", true));
			
			jps.add(new JLabel("Filtrar: "));
			jps.add(todosBoton);
			for(JCheckBox j : jcb) {
				jps.add(j);
				j.addActionListener(this);
			}
			
			//PANEL INFERIOR
			JPanel jpi = new JPanel();
			
			JButton agregarForma = new JButton("Agregar forma");
			JButton eliminarForma = new JButton("Eliminar seleccion");
			
			jpi.add(agregarForma);
			jpi.add(eliminarForma);
			
			add(jps);
			add(jpi);
			
			todosBoton.addActionListener(this);
			todosBoton.addActionListener(new ActionListener() {

				public void actionPerformed(ActionEvent e) {

					for(JCheckBox j: jcb) {
						j.setSelected(true);
					}
					
				}
				
			});
			
			agregarForma.addActionListener(new ActionListener() {

				public void actionPerformed(ActionEvent arg0) {
					AgregarForma af = new AgregarForma(lf, pp);
				}
			});
			
			eliminarForma.addActionListener(new ActionListener() {

				public void actionPerformed(ActionEvent arg0) {
					int [] indicesTabla = pp.getFilasSeleccionadas();
					int largo = indicesTabla.length;
					int [] indicesLista = new int[largo];
					
					for(int i = 0; i<largo; i++) {
						indicesLista[i] = pp.getIndiceLista(indicesTabla[i]);
					}
					Arrays.sort(indicesLista);
					
					for(int i = largo; i>0 ; i--) {
						pp.actualizarFilaEliminada(indicesLista[i-1]);
						lf.remove(indicesLista[i-1]);
						pp.actualizarTabla();
						
					}
				}
			});
		}
		

		public void actionPerformed(ActionEvent e) {

			pp.setFiltro(jcb);
			
		}
		
		public void clickearTodos() {
			todosBoton.doClick();
		}
		
		
		
	}
	
	class parteInferior extends JPanel {
		
		private JLabel labelElementos;
		private JLabel labelAreas;
		private final DecimalFormat formatter;
		
		public parteInferior() {
			
			JPanel jpi = new JPanel();
			BoxLayout bl = new BoxLayout(jpi, BoxLayout.Y_AXIS);
			jpi.setLayout(bl);
			this.setMaximumSize(new Dimension(600,100));
			
			formatter = new DecimalFormat( "0.00" );
			
			labelElementos = new JLabel();
			labelAreas = new JLabel();
			jpi.add(labelElementos);
			jpi.add(labelAreas);
			labelElementos.setAlignmentX(JLabel.CENTER_ALIGNMENT);
			labelAreas.setAlignmentX(JLabel.CENTER_ALIGNMENT);
			
			this.add(jpi);
			
		}
		
		public void actualizar() {
			labelElementos.setText("Mostrando: " + pp.getTablaColumnas() + " elementos de " + lf.getSize());
			labelAreas.setText("Área total de los elementos mostrados: " + formatter.format(getAreas()));
		}
		
		private double getAreas() {
			double areas = 0;
			
			for(int i=0; i<pp.getTablaColumnas();i++) {
				areas += (Double)pp.getAreaElemento(i);
			}
			return areas;
		}
	}
	
	class ListenerOrden implements ActionListener {
		
		private int numCol;
		
		public ListenerOrden(int numCol) {
			this.numCol = numCol;
		}
		
		public void actionPerformed(ActionEvent e) {
			pp.ordenarLista(numCol);
		}
		
	}

	
	public static void setCambios(boolean b) {
		cambios = b;
	}
	
	public static boolean getCambios() {
		return cambios;
	}
	
	public ImageIcon getIconoToolbar(String nombre) {
		return new ImageIcon(getClass().getResource("toolbar_icons/" + nombre + ".png"));
	}
	
}