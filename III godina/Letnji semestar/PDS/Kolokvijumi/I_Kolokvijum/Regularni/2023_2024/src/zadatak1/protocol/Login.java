package zadatak1.protocol;

import java.beans.XMLEncoder;
import java.io.ByteArrayOutputStream;
import java.io.Serializable;

public class Login implements Serializable {
    public String name;

    public Login() {

    }
    public Login(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        XMLEncoder xmlEncoder = new XMLEncoder(baos);
        xmlEncoder.writeObject(this);
        xmlEncoder.close();

        return baos.toString().replace("\n", " ");
    }
}
