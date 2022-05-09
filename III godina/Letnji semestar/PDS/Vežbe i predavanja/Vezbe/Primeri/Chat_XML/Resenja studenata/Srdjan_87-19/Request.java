import java.beans.XMLEncoder;
import java.io.ByteArrayOutputStream;

public class Request {

	@Override
	public String toString() {
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		XMLEncoder encoder = new XMLEncoder(baos);
		encoder.writeObject(this);
		encoder.close();
		
		return new String(baos.toByteArray()).replace('\n', ' ');
	}
}
