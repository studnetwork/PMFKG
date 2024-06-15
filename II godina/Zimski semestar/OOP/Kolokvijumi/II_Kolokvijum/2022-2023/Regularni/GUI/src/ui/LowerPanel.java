package ui;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LowerPanel extends JPanel {

    private GameWindow gameWindow;

    public LowerPanel(GameWindow gameWindow) {
        this.gameWindow = gameWindow;
        init();
        addChildren();
    }

    private void init() {
        setLayout(new BorderLayout());
    }

    private void addChildren() {
        JButton novaIgra = new JButton("Nova igra");
        novaIgra.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                gameWindow.krajIgre();
            }

        });

        add(novaIgra, BorderLayout.CENTER);

        revalidate();
    }

}
