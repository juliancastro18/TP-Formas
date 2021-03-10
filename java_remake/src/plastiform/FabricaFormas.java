package plastiform;

import java.util.ArrayList;

import javax.swing.DefaultListModel;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.event.ListDataEvent;
import javax.swing.event.ListDataListener;

public class FabricaFormas {
	
	public static void main(String[] args) {
		
		DefaultListModel <Forma> listaFormas = new DefaultListModel<Forma>();
		
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}
				
		Ventana v = new Ventana(550, 700, "PlastiForm", listaFormas);
		v.setVisible(true);
		
	}

}
