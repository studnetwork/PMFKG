import java.beans.XMLEncoder;
import java.io.ByteArrayOutputStream;
import java.io.Serializable;

public class Message extends Request implements Serializable {

	private static final long serialVersionUID = -2723363051271966964L;

	private String content;
	private String sender;
	
	public Message() {
		// Napravljeno kako bi klasa bila JavaBean
	}

	public Message(String content, String sender) {
		this.content = content;
		this.sender = sender;
	}
	
	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public String getSender() {
		return sender;
	}

	public void setSender(String sender) {
		this.sender = sender;
	}

	@Override
	public String toString() {
		return super.toString();
	}
}
