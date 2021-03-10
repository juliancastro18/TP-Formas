package plastiform;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.Rectangle;
import java.awt.event.ContainerEvent;
import java.awt.event.ContainerListener;
import java.awt.print.PrinterException;
import java.io.File;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BoxLayout;
import javax.swing.DefaultListModel;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.OverlayLayout;
import javax.swing.RowFilter;
import javax.swing.RowSorter;
import javax.swing.RowSorter.SortKey;
import javax.swing.SortOrder;
import javax.swing.SwingConstants;
import javax.swing.event.ListDataEvent;
import javax.swing.event.ListDataListener;
import javax.swing.event.RowSorterEvent;
import javax.swing.event.RowSorterListener;
import javax.swing.event.TableModelEvent;
import javax.swing.event.TableModelListener;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableModel;
import javax.swing.table.TableRowSorter;

import plastiform.Ventana.parteInferior;

public class PanelPrincipal extends JPanel {

	private DefaultListModel <Forma> listaFormas;
	private TablaPersonalizada miModelo;
	private TableRowSorter<TableModel> sorter;
	private List<RowSorter.SortKey> sortKeys;
	private List<RowFilter<Object,Object>> filters;
	private JTable tabla;
	private JLabel vacioCentro;
	
	public PanelPrincipal(DefaultListModel <Forma> lf, parteInferior pi) {
		
		this.setLayout(new BorderLayout());
		
		JPanel panel = new JPanel();
		panel.setLayout(new OverlayLayout(panel));
		
		listaFormas = lf;
	
		miModelo = new TablaPersonalizada();
		tabla = new JTable(miModelo);
		
		tabla.getTableHeader().setEnabled(false);
		JScrollPane sp = new JScrollPane(tabla);
		this.setMinimumSize(new Dimension(500,300));
		this.setMaximumSize(new Dimension(500,1000));
		sp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		
		vacioCentro = new JLabel("Agregá formas, cargá un lote o arrastralo hasta la tabla", SwingConstants.CENTER);
		vacioCentro.setAlignmentX(CENTER_ALIGNMENT);
		vacioCentro.setFont(new Font(null, Font.ITALIC, 12));
		vacioCentro.setForeground(new Color(120,120,120));
		vacioCentro.setOpaque(false);
		sp.add(vacioCentro);
		
		panel.add(vacioCentro);
		panel.add(sp);
		
		add(panel, BorderLayout.CENTER);

		
		
		DecimalFormatRenderer renderer = new DecimalFormatRenderer();
		tabla.getColumnModel().getColumn(3).setCellRenderer(renderer);
		tabla.getColumnModel().getColumn(4).setCellRenderer(renderer);
		tabla.getColumnModel().getColumn(5).setCellRenderer(renderer);
		
		tabla.getColumnModel().getColumn(0).setMinWidth(40);
		tabla.getColumnModel().getColumn(0).setPreferredWidth(40);
		tabla.getColumnModel().getColumn(1).setMinWidth(80);
		tabla.getColumnModel().getColumn(2).setMinWidth(80);
		tabla.getColumnModel().getColumn(3).setMinWidth(80);
		tabla.getColumnModel().getColumn(4).setMinWidth(80);
		tabla.getColumnModel().getColumn(5).setMinWidth(80);
		
		sorter = new TableRowSorter<TableModel>(tabla.getModel());
		tabla.setRowSorter(sorter);
		
		sortKeys = new ArrayList<>(25);
		sortKeys.add(new RowSorter.SortKey(0, SortOrder.UNSORTED));

		filters = new ArrayList<RowFilter<Object,Object>>(2);

		
		sorter.addRowSorterListener(new RowSorterListener() {

			@Override
			public void sorterChanged(RowSorterEvent arg0) {
				if(!LectorTxt.getLeyendo()) {
					pi.actualizar();
				}
				
			}
			
		});
		
		
		listaFormas.addListDataListener(new ListDataListener() {

			@Override
			public void contentsChanged(ListDataEvent arg0) {

				Ventana.setCambios(true);
			}

			@Override
			public void intervalAdded(ListDataEvent arg0) {

				Ventana.setCambios(true);
			}

			@Override
			public void intervalRemoved(ListDataEvent arg0) {

				Ventana.setCambios(true);
			}
			
		});
		
		miModelo.addTableModelListener(new TableModelListener() {

			@Override
			public void tableChanged(TableModelEvent arg0) {
				boolean tablaVacia;
				if(!LectorTxt.getLeyendo()) {
					pi.actualizar();
				}
				if(miModelo.getRowCount() == 0) {
					tablaVacia = true;
				}else {
					tablaVacia = false;
				}
				vacioCentro.setVisible(tablaVacia);
			}
			
		});
		
	}
	
	public int getTablaColumnas() {
		return tabla.getRowCount();
	}
	
	public Object getAreaElemento(int index) {
		return tabla.getValueAt(index, 5);
	}

	
	public void ordenarLista(int columna) {
		int ultimo = sortKeys.size() - 1;
		SortKey sk = sortKeys.get(ultimo);
		sortKeys.remove(ultimo);
		
		if(columna>=0) {
			if(sk.equals(new RowSorter.SortKey(columna, SortOrder.ASCENDING))) {
				sortKeys.add(new RowSorter.SortKey(columna, SortOrder.DESCENDING));
			}else {
				sortKeys.add(new RowSorter.SortKey(columna, SortOrder.ASCENDING));
			}
		}else {
			sortKeys.add(new RowSorter.SortKey(0, SortOrder.UNSORTED));
		}
		
		sorter.setSortKeys(sortKeys);
		
	}
	
	public void setFiltro(ArrayList<JCheckBox> jcb) {

		boolean todo = true;
		filters.clear();
		
		for(JCheckBox j : jcb) {
			if(!j.isSelected()) {
				todo = false;
			}
		}
		if(todo) {
			sorter.setRowFilter(null);
		}else {
			for(JCheckBox j : jcb) {
				if(j.isSelected()) {
					filters.add(RowFilter.regexFilter(j.getText(), 1));
				}
			}
			
			sorter.setRowFilter(RowFilter.orFilter(filters));
		}

	}
	
	public TablaPersonalizada getTabla() {
		return miModelo;
	}
	
	public int[] getFilasSeleccionadas() {
		return tabla.getSelectedRows();
	}
	
	public void actualizarTabla() {
		miModelo.fireTableDataChanged();
	}
	
	public int getIndiceLista(int i) {
		return tabla.convertRowIndexToModel(i);
	}
	
	public void actualizarFilaEliminada(int r1) {
		miModelo.fireTableRowsDeleted(r1, r1);
	}
	
	public void actualizarFilaAgregada() {
		int lastRowIndex = miModelo.getRowCount() -1;
		miModelo.fireTableRowsInserted(lastRowIndex, lastRowIndex);
	}
	
	public void actualizarTablaEliminada() {
		miModelo.fireTableRowsDeleted(0, miModelo.getRowCount()-1);
	}
	
	public void imprimirTabla() {
		try {
			tabla.print();
		} catch (PrinterException e) {
			JOptionPane.showMessageDialog(null, "Error al imprimir la tabla\n" + e.toString(), "Error de impresión", JOptionPane.INFORMATION_MESSAGE);
		}
	}
	
	
	class TablaPersonalizada extends DefaultTableModel {

		private String[] colNames = new String[] {"Icono", "Forma", "Color", "Parámetro 1", "Parámetro 2", "Área"};
		
		private CreadorIconos ci;
		
		public TablaPersonalizada() {
			ci = new CreadorIconos();
		}

		@Override
		public String getColumnName(int col) {
		    return colNames[col];
		}
		
		@Override
		public int getColumnCount() {
			return 6;
		}

		@Override
		public int getRowCount() {
			return listaFormas.size();
		}
		
		public boolean isCellEditable(int rowIndex, int columnIndex) {
			return false;
		}
		

		@Override
		public Object getValueAt(int rowIndex, int columnIndex) {
			
			
			switch (columnIndex) {
				case 0 : return ci.getIcono(listaFormas.get(rowIndex));
				case 1 : return listaFormas.get(rowIndex).getForma();
				case 2 : return listaFormas.get(rowIndex).getColor();
				case 3 : return listaFormas.get(rowIndex).getParam1();
				case 4 : return listaFormas.get(rowIndex).getParam2();
				case 5 : return listaFormas.get(rowIndex).getArea();
			}
			
			
			return 0;
			
		}
		
		@Override
		public Class<?> getColumnClass(int columnIndex) {
		    if (listaFormas.isEmpty()) {
		        return Object.class;
		    }
		    
		    return getValueAt(0, columnIndex).getClass();
		}
		
	}
	
   static class DecimalFormatRenderer extends DefaultTableCellRenderer {
	      private static final DecimalFormat formatter = new DecimalFormat( "0.00" );
	      
	      public DecimalFormatRenderer() {
	    	  setHorizontalAlignment(JLabel.RIGHT);
	      }
	 
	      public Component getTableCellRendererComponent(JTable table, Object value, boolean isSelected, boolean hasFocus, int row, int column) {

	    	  
	         // First format the cell value as required
	 
	         value = formatter.format((Number)value);
	 
	            // And pass it on to parent class
	 
	         return super.getTableCellRendererComponent(table, value, isSelected, hasFocus, row, column );
	      }
	 }
   /*
	class parteInferior extends JPanel {
		
		private JLabel labelElementos;
		private JLabel labelAreas;
		private final DecimalFormat formatter;
		
		public parteInferior() {
			BoxLayout bl = new BoxLayout(this, BoxLayout.Y_AXIS);
			this.setLayout(bl);
			this.setPreferredSize(new Dimension(470,100));
			
			formatter = new DecimalFormat( "0.00" );
			labelElementos = new JLabel();
			labelAreas = new JLabel();
			actualizar();
			add(labelElementos);
			add(labelAreas);
			labelElementos.setAlignmentX(JLabel.LEFT_ALIGNMENT);
			labelAreas.setAlignmentX(JLabel.LEFT_ALIGNMENT);
			
		}
		
		public void actualizar() {
			labelElementos.setText("Mostrando: " + tabla.getRowCount() + " elementos de " + listaFormas.getSize());
			labelAreas.setText("Área total de los elementos mostrados: " + formatter.format(getAreas()));
		}
		
		private double getAreas() {
			double areas = 0;
			
			for(int i=0; i<tabla.getRowCount();i++) {
				areas += (Double)tabla.getValueAt(i, 5);
			}
			return areas;
		}
	}*/

}