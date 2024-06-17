package zadatak1.battleshipgame;

import java.util.List;

public class Cruiser extends Ship {
    public Cruiser(List<Coordinate2D> coordinate2DList) {
        super(coordinate2DList);
    }

    @Override
    public ShipType getShipType() {
        return ShipType.CRUISER;
    }

    @Override
    public int getShipLength() {
        return 3;
    }
}
