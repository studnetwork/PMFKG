<?php
    class DB{
        const user = "root";
        const pw = "";
        const dbn = "csgo";
        const host = "localhost";
        
        private $dbh;
        
        function __construct() {
            $connStr = "mysql:host=".self::host.";dbname=".self::dbn;
            try {
                $this->dbh = new PDO($connStr, self::user, self::pw);
            } catch (Exception $ex) {
                die("Neuspesno uspostavljanje koncekcije");
            }
        }
        
        function __destruct() {
            $this->dbh = null;
        }
        
        function get_weapons() {
            $sql = "SELECT * FROM weapon";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die("Greska pri dobavljanju liste oruzja");
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (PDOException $ex) {
                echo $ex->getMessage();
            }
        }
        
        function get_weapon_by_id($id) {
            $sql = "SELECT * FROM weapon WHERE id=$id";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die("Greska pri dobavljanju oruzja po id-u");
                
                return $pdo_stat->fetch(PDO::FETCH_ASSOC);
            } catch (PDOException $ex) {
                echo $ex->getMessage();
            }
        }
        
        function get_users() {
            $sql = "SELECT * FROM user";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die("Greska pri dobavljanju liste korisnika");
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (PDOException $ex) {
                echo $ex->getMessage();
            }
        }
        
        function update_money($uid, $money) {
            $sql = "UPDATE user SET money=:money WHERE id=:id";
            
            try {
                $pdo_stat = $this->dbh->prepare($sql);
                $pdo_stat->bindParam(":id", $uid);
                $pdo_stat->bindParam(":money", $money);
                $pdo_stat->execute();
                
                return true;
            } catch (PDOException $ex) {
                echo $ex->getMessage();
            }
            
            return false;
        }
        
        function has_loadout($uid,$team) {
            $sql = "SELECT * FROM loadout WHERE userID=$uid AND t_ct=$team";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die("Greska proveri da li korisnik ima loadout");
                
                if( count($pdo_stat->fetchAll(PDO::FETCH_ASSOC)) > 0 ) // TODO: lose
                    return true;
            } catch (PDOException $ex) {
                echo $ex->getMessage();
            }
            
            return false;
        }


        function add_loadout(/*$id = null,*/ $uid, $wid, $team) {
            $sql = "INSERT INTO loadout (userID, weaponID, t_ct) ";
            $sql .= "VALUES ($uid, $wid, $team)";
            
            /*$sql = "INSERT INTO loadout (";
            if($id!=null) 
                $sql .="id,";
            $sql .= "userID, weaponID, t_ct) ";
            
            $sql .= "VALUES (";
            if($id!=null) 
                $sql .="$id,";
            $sql .= "$uid, $wid, $team)";*/
            
            try {
                $affected = $this->dbh->exec($sql);
                
                if($affected)
                    return true;
            } catch (PDOException $ex) {
                echo $ex->getMessage();
            }
            
            return false;
        }
        
        function drop_loadout($uid,$team) {
            $sql = "DELETE FROM loadout WHERE userID=$uid, t_ct=$team";
            
            try {
                $affected = $this->dbh->exec($sql);
                
                if($affected)
                    return true;
            } catch (PDOException $ex) {
                echo $ex->getMessage();
            }
            
            return false;
        }
    }