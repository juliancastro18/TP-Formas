package plastiform;

import java.awt.Dimension;
import java.awt.Toolkit;

public class Pantalla {
	
	private int alturaPantalla;
	
	private int anchoPantalla;
	
	public Pantalla() {
		
		Toolkit miPantalla = Toolkit.getDefaultToolkit();
		
		Dimension tamanoPantalla = miPantalla.getScreenSize();
		
		this.alturaPantalla = tamanoPantalla.height;
		
		this.anchoPantalla = tamanoPantalla.width;
		
	}
	
	public int getAltura() {
		return alturaPantalla;
	}
	
	public int getAncho() {
		return anchoPantalla;
	}
	
	public int posYBound(int alto) {
		return (getAltura() / 2) - (alto / 2);
	}
	
	public int posXBound(int ancho) {
		return (getAncho() / 2) - (ancho / 2);
	}
	
}