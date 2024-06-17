package zadatak1.battleshipgame;

import java.util.List;

public class Submarine extends Ship {
    public Submarine(List<Coordinate2D> coordinate2DList) {
        super(coordinate2DList);
    }

    @Override
    public ShipType getShipType() {
        return ShipType.SUBMARINE;
    }

    @Override
    public int getShipLength() {
        return 1;
    }
}
