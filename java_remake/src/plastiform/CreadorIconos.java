package plastiform;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.image.BufferedImage;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;


public class CreadorIconos {
	
	private BufferedImage trianguloImagen;
	private BufferedImage rectanguloImagen;
	private BufferedImage circuloImagen;
	private BufferedImage cuboImagen;
	private BufferedImage cilindroImagen;
	
	private static final Color VIOLETA = new Color(128,0,255);
	private static final Color CUSTOMCOLOR = new Color(100,100,100);
	private static final Color NEGRO = new Color(50,50,50);
	
	public CreadorIconos(){
		try {
	
		trianguloImagen = ImageIO.read(getClass().getResource("tria.png"));
		rectanguloImagen = ImageIO.read(getClass().getResource("rect.png"));
		circuloImagen = ImageIO.read(getClass().getResource("circ.png"));
		cuboImagen = ImageIO.read(getClass().getResource("cubo.png"));
		cilindroImagen = ImageIO.read(getClass().getResource("cili.png"));
		}catch(IOException e) {
			System.out.println("Error al cargar imagenes");
		}

	}
	

	
	public ImageIcon getIcono(Forma f) {
		BufferedImage bi;
		Color c= getColor(f);
		
		if(f instanceof Triangulo) {
			bi = colorearImagen(trianguloImagen, c);
		}else if(f instanceof Rectangulo) {
			bi = colorearImagen(rectanguloImagen, c);
		}else if(f instanceof Circulo) {
			bi = colorearImagen(circuloImagen, c);
		}else if(f instanceof Cubo) {
			bi = colorearImagen(cuboImagen, c);
		}else if(f instanceof Cilindro) {
			bi = colorearImagen(cilindroImagen, c);
		}else {
			return null;
		}
		
		ImageIcon ii = new ImageIcon(bi);
		
		return ii;
		
	}
	
	public Image getIcono(String color, String forma) {
		BufferedImage bi;
		Color c= getColor(color);
		
		if(forma.equals("Triangulo")) {
			bi = colorearImagen(trianguloImagen, c);
		}else if(forma.equals("Rectangulo")) {
			bi = colorearImagen(rectanguloImagen, c);
		}else if(forma.equals("Circulo")) {
			bi = colorearImagen(circuloImagen, c);
		}else if(forma.equals("Cubo")) {
			bi = colorearImagen(cuboImagen, c);
		}else if(forma.equals("Cilindro")) {
			bi = colorearImagen(cilindroImagen, c);
		}else {
			return null;
		}
		
		return bi;
		
	}
	
	private static BufferedImage colorearImagen(BufferedImage bi, Color c) {
        if(c.equals(CUSTOMCOLOR)) {
        	return colorearCustom(bi);
        }
		
		BufferedImage image = copyImage(bi);
		
        int width = image.getWidth();
        int height = image.getHeight();
        
        for (int xx = 0; xx < width; xx++) {
            for (int yy = 0; yy < height; yy++) {
                Color originalColor = new Color(image.getRGB(xx, yy), true);
                if (originalColor.equals(Color.BLACK) && originalColor.getAlpha() == 255) {
                	image.setRGB(xx, yy, c.getRGB());
                }
            }
        }
        return image;
    }
	
	
	private static BufferedImage colorearCustom(BufferedImage bi) {
		BufferedImage image = copyImage(bi);
		
        int width = image.getWidth();
        int height = image.getHeight();
        

        for (int xx = 0; xx < width; xx++) {
            for (int yy = 0; yy < height; yy++) {
                Color originalColor = new Color(image.getRGB(xx, yy), true);
                if (originalColor.equals(Color.BLACK) && originalColor.getAlpha() == 255) {
                	if( (xx+yy)%2 == 0) {
                		image.setRGB(xx, yy, CUSTOMCOLOR.getRGB());
                	}else {
                		image.setRGB(xx, yy, Color.white.getRGB());
                	}
                }
            }
        }
        return image;
    }	
	
		
	public static BufferedImage copyImage(BufferedImage source){
	    BufferedImage b = new BufferedImage(source.getWidth(), source.getHeight(), source.getType());
	    Graphics g = b.getGraphics();
	    g.drawImage(source, 0, 0, null);
	    g.dispose();
	    return b;
	}
	
	Color getColor(Forma f) {
		Color c;
		String s = f.getColor();
		switch(s) {
		case "Rojo": c=Color.red; break;
		case "Azul": c=Color.blue; break;
		case "Amarillo": c=Color.yellow; break;
		case "Negro": c=NEGRO; break;
		case "Blanco": c=Color.white; break;
		case "Naranja": c=Color.orange; break;
		case "Verde": c=Color.green; break;
		case "Violeta": c= VIOLETA; break;
		default: c= CUSTOMCOLOR; break;
		}
		return c;
	}
	
	Color getColor(String s) {
		Color c;
		switch(s) {
		case "Rojo": c=Color.red; break;
		case "Azul": c=Color.blue; break;
		case "Amarillo": c=Color.yellow; break;
		case "Negro": c=NEGRO; break;
		case "Blanco": c=Color.white; break;
		case "Naranja": c=Color.orange; break;
		case "Verde": c=Color.green; break;
		case "Violeta": c= VIOLETA; break;
		default: c= CUSTOMCOLOR; break;
		}
		return c;
	}

	
}
