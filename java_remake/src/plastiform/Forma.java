package plastiform;

import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.Locale;

public abstract class Forma {
	
	public static final String formas[] = {"Triangulo", "Rectangulo", "Circulo", "Cubo", "Cilindro"};
	
	private static final DecimalFormat df = new DecimalFormat();
	
	private int tipoForma;	
	
	private String color = "sin color";
	
	private double param1 = 0;
	
	private double param2 = 0;
	
	private double area = 0;

	public Forma(double p1, String color, int f) {
		this.param1 = p1;
		this.color = color.substring(0, 1).toUpperCase() + color.substring(1).toLowerCase();
		this.area = calcularArea(p1);
		this.tipoForma = f;
	}
	
	public Forma(double p1, double p2, String color, int f) {
		this.param1 = p1;
		this.param2 = p2;
		this.color = color.substring(0, 1).toUpperCase() + color.substring(1).toLowerCase();
		this.area = calcularArea(p1, p2);
		this.tipoForma = f;
	}
	
	public double getArea() {
		return area;
	}
	
	public String getColor() {
		return color;
	}
	
	public double getParam1() {
		return param1;
	}
	
	public double getParam2() {
		return param2;
	}
	
	public String getForma() {
		return formas[tipoForma];
	}
	
	
	public abstract double calcularArea(double p1);
	public abstract double calcularArea(double p1, double p2);
	
	public String toString() {

		String str = this.formas[tipoForma].toLowerCase() + " " + this.color.toLowerCase() + " " + df.format(param1);
		if(param2!=0) {
			str+= "; " + df.format(param2);
		}
		return str;
	}
	
}