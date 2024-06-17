package zadatak1.battleshipgame;

import java.util.List;

public class Destroyer extends Ship {
    public Destroyer(List<Coordinate2D> coordinate2DList) {
        super(coordinate2DList);
    }

    @Override
    public ShipType getShipType() {
        return ShipType.DESTROYER;
    }

    @Override
    public int getShipLength() {
        return 2;
    }
}
