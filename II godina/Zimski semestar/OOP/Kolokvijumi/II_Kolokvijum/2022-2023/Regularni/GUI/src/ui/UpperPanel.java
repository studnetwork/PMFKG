package ui;

import javax.swing.*;
import java.awt.*;

public class UpperPanel extends JPanel {

    private int brPotezaCrvenog;
    private int brPotezaZutog;

    private JLabel brojPotezaZutog;
    private JLabel brojPotezaCrvenog;
    private JLabel slikaNaPotezu;

    private ImageIcon crvenaSlika = new ImageIcon("slike/red_small.png");
    private ImageIcon zutaSlika = new ImageIcon("slike/yellow_small.png");

    public UpperPanel() {
        init();
        addChildren();
    }

    private void init() {
        setLayout(new BorderLayout());
    }

    private void addChildren() {
        brojPotezaZutog = new JLabel("Broj poteza zutog: " + brPotezaZutog);
        brojPotezaCrvenog = new JLabel("Broj poteza crvenog: " + brPotezaCrvenog);

        JPanel container = new JPanel();

        JLabel naPotezu = new JLabel("Na potezu:");

        slikaNaPotezu = new JLabel();
        slikaNaPotezu.setIcon(crvenaSlika);

        container.add(naPotezu);
        container.add(slikaNaPotezu);

        add(brojPotezaCrvenog, BorderLayout.WEST);
        add(container, BorderLayout.CENTER);
        add(brojPotezaZutog, BorderLayout.EAST);

        revalidate();
    }

    public void dodajPotezCrvenog() {
        brPotezaCrvenog += 1;
        brojPotezaCrvenog.setText("Broj poteza crvenog: " + brPotezaCrvenog);
        slikaNaPotezu.setIcon(zutaSlika);
    }

    public void dodajPotezZutog() {
        brPotezaZutog += 1;
        brojPotezaZutog.setText("Broj poteza crvenog: " + brPotezaZutog);
        slikaNaPotezu.setIcon(crvenaSlika);
    }

}
