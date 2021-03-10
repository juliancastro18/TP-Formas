package plastiform;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.*;

import javax.swing.DefaultListModel;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

public class EscritorTxt implements ActionListener {
	
	private JFileChooser fileChooser;
	private File file;
	int returnVal;
	private Formatter x;
	private DefaultListModel<Forma> listaFormas;
	
	public EscritorTxt(DefaultListModel<Forma> lf) {
		fileChooser = new JFileChooser();
		fileChooser.setSelectedFile(new File("nuevo lote.txt"));
		fileChooser.setFileFilter(new FileNameExtensionFilter("Archivos de texto", "txt"));
		fileChooser.setDialogTitle("Indicá donde guardar el lote");  
		
		this.listaFormas = lf;
	}
	
	public void openFile() {
		
		returnVal = fileChooser.showSaveDialog(null);
		if(returnVal == JFileChooser.APPROVE_OPTION) {
			file = fileChooser.getSelectedFile();

			String fname = file.getAbsolutePath();
			
			
			if(!fname.endsWith(".txt") ) {
                file = new File(fname + ".txt");
			}
			
			try {
				x = new Formatter(file);
				addRecords();
				closeFile();
				Ventana.setCambios(false);
			}
			catch(IOException e) {
				JOptionPane.showMessageDialog(null, e.toString());
				x.close();
			}
			
		}
		
		
	}
	
	public void addRecords() {
		for(int i=0; i< listaFormas.size(); i++) {
			x.format("%s%n", listaFormas.get(i));
		}
	}
	
	public void closeFile() {
		x.close();
	}
	
	public void actionPerformed(ActionEvent e) {
		openFile();
	}

}
