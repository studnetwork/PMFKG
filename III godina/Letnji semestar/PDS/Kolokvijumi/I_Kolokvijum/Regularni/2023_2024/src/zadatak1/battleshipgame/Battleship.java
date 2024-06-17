package zadatak1.battleshipgame;

import java.util.List;

public class Battleship extends Ship {
    public Battleship(List<Coordinate2D> coordinate2DList) {
        super(coordinate2DList);
    }

    @Override
    public ShipType getShipType() {
        return ShipType.BATTLESHIP;
    }

    @Override
    public int getShipLength() {
        return 4;
    }
}
