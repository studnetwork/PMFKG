package zadatak1.battleshipgame;

import java.util.ArrayList;
import java.util.List;

public class BattleshipMap {

    List<Ship> ships;

    public boolean hasHealthyShip(){
        return ships.isEmpty() == false;
    }

    public List<ShipType> getAvailableShips(){
        return ships.stream().map(x -> x.getShipType()).toList();
    }

    public BattleshipMap(Battleship battleship, Cruiser cruiser1, Cruiser cruiser2,
                         Destroyer destroyer1, Destroyer destroyer2, Destroyer destroyer3,
                         Submarine submarine1, Submarine submarine2, Submarine submarine3, Submarine submarine4){
        ships = new ArrayList<>();

        ships.add(battleship);

        ships.add(cruiser1);
        ships.add(cruiser2);

        ships.add(destroyer1);
        ships.add(destroyer2);
        ships.add(destroyer3);

        ships.add(submarine1);
        ships.add(submarine2);
        ships.add(submarine3);
        ships.add(submarine4);
    }

    public AttackResult underAttack(Coordinate2D attackAt) {

        for (Ship ship : ships) {
            AttackResult attackResult = ship.attackOnShip(attackAt);
            if (attackResult == AttackResult.SHIPWRECK) {
                ships.remove(ship);
                return attackResult;
            }
            if (attackResult == AttackResult.HIT) {
                return attackResult;
            }
        }
        return AttackResult.MISS;
    }
}