import JMyron.*;

public class JMyronTest {
    public static void main(String [] argv){
	JMyron m = new JMyron();
	m.start(320,240);
	m.findGlobs(0);
	System.out.println("Myron " + m.version());

	while(true){
	    m.update();
	    int[] img = m.image();
	    System.out.println(img[0]);
	    
	    //Thread.sleep(100);
	    
	}

    }
    
}
