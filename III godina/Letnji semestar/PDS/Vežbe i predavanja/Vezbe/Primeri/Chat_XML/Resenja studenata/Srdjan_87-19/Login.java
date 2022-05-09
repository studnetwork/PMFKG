import java.beans.XMLEncoder;
import java.io.ByteArrayOutputStream;
import java.io.Serializable;

public class Login extends Request implements Serializable {
	private static final long serialVersionUID = -5297960677845729680L;
	
	private String name;
	private String code;
	
	public Login(){
		// Napravljeno kako bi klasa bila JavaBean
	}
	
	public Login(String name, String code) {
		this.name = name;
		this.code = code;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getCode() {
		return code;
	}

	public void setCode(String code) {
		this.code = code;
	}

	@Override
	public String toString() {
		return super.toString();
	}
}
