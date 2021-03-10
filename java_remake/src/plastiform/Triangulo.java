package plastiform;

public class Triangulo extends Forma {


	public Triangulo(double base, double altura, String color) {
		super(base, altura, color, 0);
	}

	public double calcularArea(double base, double altura) {
		return (base*altura) / 2;
	}

	public double calcularArea(double base) {
		return Math.pow(base, 2) / 2;
	}

}
