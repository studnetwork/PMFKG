package zadatak1.battleshipgame;

import java.util.HashMap;
import java.util.List;

public abstract class Ship {

    private HashMap<Coordinate2D, HealthStatus> shipHealthMap;

    public abstract ShipType getShipType();

    public abstract int getShipLength();

    public Ship(List<Coordinate2D> coordinate2DList){
        if (coordinate2DList.size() == getShipLength()){
            shipHealthMap = new HashMap<>();
            for (Coordinate2D coordinate2D: coordinate2DList){
                shipHealthMap.put(coordinate2D, HealthStatus.HEALTH);
            }
        }
        else {
            throw new IllegalArgumentException("The length of ship must be " + getShipLength());
        }
    }

    public boolean isShipwreck(){
        for (HealthStatus status: shipHealthMap.values()){
            if (status == HealthStatus.HEALTH){
                return false;
            }
        }
        return true;
    }
    public AttackResult attackOnShip(Coordinate2D attackAt){
        if (shipHealthMap.containsKey(attackAt) && shipHealthMap.get(attackAt) == HealthStatus.HEALTH){
            shipHealthMap.put(attackAt, HealthStatus.NOT_HEALTH);
            if (isShipwreck()){
                return AttackResult.SHIPWRECK;
            }
            return AttackResult.HIT;
        }
        return AttackResult.MISS;
    }
}
