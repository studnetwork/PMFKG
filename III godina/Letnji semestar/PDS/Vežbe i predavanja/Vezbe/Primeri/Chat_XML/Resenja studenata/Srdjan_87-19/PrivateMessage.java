import java.beans.XMLEncoder;
import java.io.ByteArrayOutputStream;
import java.io.Serializable;

public class PrivateMessage extends Message {
	private String recipient;

	// Napravljeno kako bi klasa bila JavaBean
	public PrivateMessage() {
		super();
	}

	public PrivateMessage(String content, String sender, String recipient) {
		super(content, sender);
		this.recipient = recipient;
	}

	public String getRecipient() {
		return recipient;
	}

	public void setRecipient(String recipient) {
		this.recipient = recipient;
	}

	@Override
	public String toString() {
		return super.toString();
	}
}
