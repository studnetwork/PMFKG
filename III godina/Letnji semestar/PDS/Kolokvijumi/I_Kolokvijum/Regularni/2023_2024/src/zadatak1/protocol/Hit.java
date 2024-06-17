package zadatak1.protocol;

import java.beans.XMLEncoder;
import java.io.ByteArrayOutputStream;

public class Hit {
    public int x;
    public int y;

    public Hit() {
    }

    public Hit(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
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
