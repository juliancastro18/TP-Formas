package plastiform;

public class Cilindro extends Forma {
	
	private static final double pi = 3.1415;
	
	public Cilindro(double radio, double altura, String color) {
		super(radio, altura, color, 4);
	}

	public double calcularArea(double radio) {
		return -1;
	}

	public double calcularArea(double radio, double altura) {
		return 2 * pi * radio * (radio + altura);
	}
	
}
