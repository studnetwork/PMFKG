package ui;

import javax.swing.*;
import java.awt.*;

import static ui.GameWindow.Potez.CRVENI;
import static ui.GameWindow.Potez.ZUTI;

public class GameWindow extends JFrame {

    public enum Potez {
        CRVENI,
        ZUTI
    }

    private UpperPanel upperPanel;
    private CenterPanel centerPanel;
    private LowerPanel lowerPanel;

    private Potez naPotezu = CRVENI;

    public GameWindow() {
        init();
        addPanels();
    }

    public void promeniPotez() {
        if (koJeNaPotezu() == CRVENI) {
            upperPanel.dodajPotezCrvenog();
            naPotezu = ZUTI;
        } else if (koJeNaPotezu() == ZUTI) {
            upperPanel.dodajPotezZutog();
            naPotezu = CRVENI;
        }
    }

    public Potez koJeNaPotezu() {
        return naPotezu;
    }

    private void init() {
        setTitle("Connect 4");
        setSize(700, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setLocationRelativeTo(null);
        setResizable(false);
        setVisible(true);
    }

    private void addPanels() {
        upperPanel = new UpperPanel();
        centerPanel = new CenterPanel(this);
        lowerPanel = new LowerPanel(this);

        getContentPane().add(upperPanel, BorderLayout.NORTH);
        getContentPane().add(centerPanel, BorderLayout.CENTER);
        getContentPane().add(lowerPanel, BorderLayout.SOUTH);

        revalidate();
    }

    public void krajIgre() {
        dispose();
        new GameWindow();
    }

}
