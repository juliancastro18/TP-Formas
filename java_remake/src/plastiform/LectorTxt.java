package plastiform;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.text.Normalizer;
import java.util.ArrayList;

import javax.swing.DefaultListModel;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.event.ListDataEvent;
import javax.swing.event.ListDataListener;
import javax.swing.filechooser.FileNameExtensionFilter;

import plastiform.PanelPrincipal.TablaPersonalizada;

public class LectorTxt implements ActionListener{
	
	private static boolean leyendo;
	private JFileChooser fileChooser;
	private BufferedReader br;
	private File file;
	private TablaPersonalizada tp;
	int returnVal;
	String currentLine;
	
	private DefaultListModel <Forma> listaFormas;
	
	public LectorTxt(DefaultListModel<Forma> lf, TablaPersonalizada tp) {
		this.tp = tp;
		fileChooser = new JFileChooser();
		fileChooser.setFileFilter(new FileNameExtensionFilter("Archivos de texto", "txt"));
		fileChooser.setDialogTitle("Indicá la ubicación del lote");  
		listaFormas = lf;
		leyendo = false;
	}

	public void actionPerformed(ActionEvent e) {
		leyendo = true;
		//me fijo si la lista tiene cosas cargadas y pregunto si quiere sobreescribir
		if(listaFormas.isEmpty() == false) {
			Object[] options = {"Adicionar","Reemplazar","Cancelar"};
		    int resultadoDialogo = JOptionPane.showOptionDialog(null, "Ya hay elementos en la lista.\nQue desea hacer?","Atención",JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[0]);
			if (resultadoDialogo == JOptionPane.NO_OPTION){
				
				//tp.fireTableRowsDeleted(0, tp.getRowCount()-1);
				listaFormas.clear();
				tp.fireTableDataChanged();
				
			}else if(resultadoDialogo == JOptionPane.CANCEL_OPTION){
				leyendo = false;
				return;
			}
		}
		
		returnVal = fileChooser.showOpenDialog(null);
		if(returnVal == JFileChooser.APPROVE_OPTION) {
			file = fileChooser.getSelectedFile();
			leerArchivo(file);
			
		}
		
		leyendo= false;
	}
	
	public static boolean getLeyendo() {
		return leyendo;
	}
	
	public static void setLeyendo(boolean valor) {
		leyendo = valor;
	}
	
	private static boolean isLetterOrDigit(char c) {
	    return (c >= 'a' && c <= 'z') ||
	           (c >= 'A' && c <= 'Z') ||
	           (c >= '0' && c <= '9');
	}

	public boolean comprobar() {
		leyendo=true;
		if(listaFormas.isEmpty() == false) {
			Object[] options = {"Adicionar","Reemplazar","Cancelar"};
		    int resultadoDialogo = JOptionPane.showOptionDialog(null, "Ya hay elementos en la lista.\nQue desea hacer?","Atención",JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE, null, options, options[0]);
			if (resultadoDialogo == JOptionPane.NO_OPTION){
				
				//tp.fireTableRowsDeleted(0, tp.getRowCount()-1);
				listaFormas.clear();
				tp.fireTableDataChanged();
				
				
			}else if(resultadoDialogo == JOptionPane.CANCEL_OPTION){
				return false;
			}
		}
		leyendo = false;
		return true;
	}
	
	public void leerArchivo(File file) {
		leyendo = true;
		boolean listaEstabaVacia = listaFormas.isEmpty();
		int linea = 0;
		
		//Read the file
		try {
			br = new BufferedReader(new FileReader(file));
			br.mark(1);
			
			char simbolo = (char)br.read();
			while(!isLetterOrDigit(simbolo)) {
				br.mark(1);
				simbolo = (char)br.read();
			}
			
			br.reset();
			
			while((currentLine = br.readLine()) != null) {
				linea++;
				boolean todoOk = true;
				String forma = new String();
				String color = new String();
				double p1 = 0;
				double p2 = 0;
				
				try {
					currentLine = currentLine.replace(',', '.');
					currentLine = Normalizer.normalize(currentLine, Normalizer.Form.NFD).replaceAll("\\p{InCombiningDiacriticalMarks}+", "");
					
					
					int indice1 = 0;
					int indice2 = currentLine.indexOf(" ");
					forma = currentLine.substring(indice1, indice2);
					
					indice1 = indice2+1;
					indice2 = currentLine.indexOf(" ", indice1);
					color = currentLine.substring(indice1, indice2);
					
					indice1 = indice2+1;
					indice2 = currentLine.indexOf(";", indice1);
					
					p1 = 0;
					p2 = 0;
					
					if(indice2 != -1) { //si hay 2 parametros
						p1 = Double.parseDouble(currentLine.substring(indice1, indice2));
						p2 = Double.parseDouble(currentLine.substring(indice2+1));
					}else {
						p1 = Double.parseDouble(currentLine.substring(indice1));
					}
					
				
				}catch(Exception error) {
					JOptionPane.showMessageDialog(null, "Error en la línea " + linea + ": formato inválido\nSe ignorará esta línea");
					todoOk = false;
				}
				
				if(todoOk == true) {
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
					}else {
						JOptionPane.showMessageDialog(null, "Error en la línea " + linea + ": nombre de figura no válida\nSe ignorará esta línea");
					}
					
				}

				
			}
		}catch(Exception error) {
			JOptionPane.showMessageDialog(null, "Error al leer el archivo seleccionado");
			error.printStackTrace();
		}
		
		listaFormas.addElement(new Triangulo(0,0,"dummy"));
		listaFormas.remove(listaFormas.size() - 1);
		
		if(listaEstabaVacia) {
			Ventana.setCambios(false);
		}
		leyendo= false;
		tp.fireTableDataChanged();
	}
}
