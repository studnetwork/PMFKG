package zadatak1.protocol;

import java.beans.XMLEncoder;
import java.io.ByteArrayOutputStream;

public class Result {
    public String result;

    public Result() {

    }
    public Result(String result) {
        this.result = result;
    }

    public String getResult() {
        return result;
    }

    public void setResult(String result) {
        this.result = result;
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
