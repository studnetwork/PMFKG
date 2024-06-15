package ui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Dugme extends JButton {

    private boolean praznoPolje = true;
    private int boja = 0;
    private int x = -1;
    private int y = -1;

    private ImageIcon slikaPraznogPolja = new ImageIcon("slike/prazno_polje.PNG");
    private ImageIcon crvenoPolje = new ImageIcon("slike/crvena_boja.PNG");
    private ImageIcon zutoPolje = new ImageIcon("slike/zuto_polje.PNG");

    public Dugme(int x, int y) {
        this.x = x;
        this.y = y;
        setIcon(slikaPraznogPolja);
    }

    public int dajBoju() {
        return boja;
    }

    public boolean jePrazno() {
        return praznoPolje;
    }

    public int dajX() {
        return x;
    }

    public int dajY() {
        return y;
    }

    public void postaniCrveno() {
        setIcon(crvenoPolje);
        boja = 1;
        praznoPolje = false;
    }

    public void postaniZuto() {
        setIcon(zutoPolje);
        boja = 2;
        praznoPolje = false;
    }

}
