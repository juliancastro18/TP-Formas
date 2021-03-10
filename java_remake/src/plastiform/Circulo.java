package plastiform;

public class Circulo extends Forma {
	
	private static final double pi = 3.1415;

	public Circulo(double radio, String color) {
		super(radio, color, 2);
	}

	public double calcularArea(double radio) {
		return pi * Math.pow(radio, 2);
	}

	public double calcularArea(double radio, double p2) {
		return calcularArea(radio);
	}
	
}
