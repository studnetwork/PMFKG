<?php
    class DB {
        const user = 'root';
        const pw = '';
        const host = 'localhost';
        const dbname = 'vaterpolo';
        
        private $dbh;
        
        function __construct() {
            $connStr = "mysql:host=".self::host.";dbname=".self::dbname;
            try {
                $this->dbh = new PDO($connStr, self::user, self::pw);
            } catch (Exception $ex) {
                die("Neuspesno uspostavljanje konekcije sa bazom");
            }
        }
        
        function __destruct() {
            $this->dbh = null;
        }
        
        function get_groups() {
            $sql = "SELECT * FROM grupa";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die("Neuspesno dohvatanje liste grupa");
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
        }
        
        function get_teams_by_gid($gid) {
            $sql = "SELECT * FROM timovi WHERE grupa_id=$gid";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die("Neuspesno dohvatanje liste timova #$gid grupe");
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
        }
        
        function get_players_by_tid($tid) {
            $sql = "SELECT * FROM igraci WHERE tim_id=$tid";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die("Neuspesno dohvatanje liste igraca #$tid tima");
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
        }
        
        function deleteTeam($tid) {
            $sql = "DELETE FROM timovi WHERE id=$tid";
            
            try {
                $affected = $this->dbh->exec($sql);
                
                if($affected)
                    return true;
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            
            return false;
        }
        
        function add_player($tid, $playerName, $bio) {
            $sql = "INSERT INTO igraci (ime, tim_id, biografija)";
            $sql .= " VALUES ('$playerName', $tid, '$bio')";
            
            try {
                $affected = $this->dbh->exec($sql);
                
                if($affected)
                    return true;
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            
            return false;
        }
        
        function deleteTeamPlayers($tid) {
            $sql = "DELETE FROM igraci WHERE tim_id=$tid";
            
            try {
                $affected = $this->dbh->exec($sql);
                
                if($affected)
                    return true;
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            
            return false;
        }
    }

