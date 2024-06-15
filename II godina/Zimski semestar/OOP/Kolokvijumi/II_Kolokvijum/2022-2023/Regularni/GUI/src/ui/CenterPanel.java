package ui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CenterPanel extends JPanel {

    private GameWindow gameWindow;
    private Dugme[][] dugmici = new Dugme[6][7];

    public CenterPanel(GameWindow gameWindow) {
        this.gameWindow = gameWindow;

        init();
        addChildren();
    }

    public Dugme[][] getDugmici() {
        return dugmici;
    }

    private void init() {
        setLayout(new GridLayout(6, 7, 1, 1));
    }

    private void addChildren() {
        for (int i = 0; i < dugmici.length; i++)
            for (int j = 0; j < dugmici[i].length; j++) {
                dugmici[i][j] = new Dugme(i, j);

                dugmici[i][j].addActionListener(new ActionListener() {

                    @Override
                    public void actionPerformed(ActionEvent e) {
                        Dugme izvornoDugme = (Dugme) e.getSource();

                        int izvornoX = izvornoDugme.dajX();
                        int izvornoY = izvornoDugme.dajY();

                        Dugme dodataKugla = dodajKuglu(izvornoY);

                        if (dodataKugla != null) {
                            boolean pobeda = proveriPobedu(dodataKugla);
                            boolean neresno = daLiJeNeresno();

                            if (pobeda) {
                                String text;

                                if (gameWindow.koJeNaPotezu() == GameWindow.Potez.CRVENI)
                                    text = "Pobednik je crveni";
                                else
                                    text = "Pobednik je zuti";

                                int rezultat = JOptionPane.showConfirmDialog(gameWindow, text + "\nDa li zelite novu igru", "Kraj", JOptionPane.YES_NO_OPTION);

                                if (rezultat == JOptionPane.YES_OPTION)
                                    gameWindow.krajIgre();
                                else
                                    System.exit(0);
                            } else if (neresno) {
                                int rezultat = JOptionPane.showConfirmDialog(gameWindow, "Nereseno\nDa li zelite novu igru", "Kraj", JOptionPane.YES_NO_OPTION);

                                if (rezultat == JOptionPane.YES_OPTION)
                                    gameWindow.krajIgre();
                                else
                                    System.exit(0);
                            }
                            else
                                gameWindow.promeniPotez();
                        }
                    }

                });

                add(dugmici[i][j]);
            }

        revalidate();
    }

    private boolean proveriPobedu(Dugme dugme) {
        int x = dugme.dajX();
        int y = dugme.dajY();
        int boja = dugme.dajBoju();

        // Provera za dole

        if (x + 3 < 6) {
            boolean pobeda = true;

            for (int i = x; i <= x + 3; i++) {
                if (dugmici[i][y].dajBoju() != boja) {
                    pobeda = false;
                    break;
                }
            }

            if (pobeda)
                return true;
        }

        if (y - 3 >= 0) { // Levo
            boolean pobeda = true;

            for (int i = y - 3; i <= y; i++) {
                if (dugmici[x][i].dajBoju() != boja) {
                    pobeda = false;
                    break;
                }
            }

            if (pobeda)
                return true;
        }

        if (y + 3 <= 7) { // Desno
            boolean pobeda = true;

            for (int i = y; i <= y + 3; i++) {
                if (dugmici[x][i].dajBoju() != boja) {
                    pobeda = false;
                    break;
                }
            }

            if (pobeda)
                return true;
        }

        return false;
    }

    private boolean daLiJeNeresno() {
        for (int i = 0; i < dugmici.length; i++)
            for (int j = 0; j < dugmici[i].length; j++) {
                if (dugmici[i][j].jePrazno())
                    return false;
            }

        return true;
    }


    private Dugme dodajKuglu(int y) {
        for (int x = dugmici.length - 1; x >= 0; x--) {
            if (dugmici[x][y].jePrazno()) {
                if (gameWindow.koJeNaPotezu() == GameWindow.Potez.CRVENI)
                    dugmici[x][y].postaniCrveno();
                else
                    dugmici[x][y].postaniZuto();

                return dugmici[x][y];
            }
        }

        return null;
    }

}
