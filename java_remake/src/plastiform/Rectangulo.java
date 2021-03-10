package plastiform;

public class Rectangulo extends Forma{
	
	public Rectangulo(double base, double altura, String color) {
		super(base, altura, color, 1);
	}
	
	public Rectangulo(double base, String color) {
		super(base, color, 1);
	}

	public double calcularArea(double base, double altura) {
		return base*altura;
	}
	
	public double calcularArea(double base) {
		return Math.pow(base, 2);
	}

	
}
