package plastiform;

public class Cubo extends Forma {
	
	public Cubo(double base, String color) {
		super(base, color, 3);
	}

	public double calcularArea(double base) {
		return Math.pow(base, 2) * 6;
	}

	public double calcularArea(double base, double p2) {
		return calcularArea(base);
	}

	
}
