<?php

    class DB 
    {
        const user = 'root';
        const pw = '';
        const host = 'localhost';
        const dbname = 'oebs';
        
        private $dhb;
        
        function __construct() {
            $connStr = "mysql:host=".self::host.";dbname=".self::dbname;
            try {
                $this->dhb = new PDO($connStr, self::user, self::pw);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
        }
        
        function __destruct() {
            $this->dhb = null;
        }
        
        function get_topic_by_id($topicID) {
            $sql = "SELECT * FROM topics WHERE id=$topicID";
            
            try {
                $pdo_stat = $this->dhb->query($sql);
                if(!$pdo_stat)
                    die("Greska pri dohvatanju teme po id-u");
                
                return $pdo_stat->fetch(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            return false;
        }
        
        function get_all_topic() {
            $sql = "SELECT * FROM topics";
            
            try {
                $pdo_stat = $this->dhb->query($sql);
                if(!$pdo_stat)
                    die("Greska pri dohvatanju liste svih tema");
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            return false;
        }
        
        function get_all_cstatements_by_country($countryID) {
            $sql = "SELECT * FROM topiccou WHERE countryID=$countryID";
            
            try {
                $pdo_stat = $this->dhb->query($sql);
                if(!$pdo_stat)
                    die("Greska pri dohvatanju liste izjava i drzava");
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            return false;
        }
        
        function get_all_cstatements_by_topic($topicID) {
            $sql = "SELECT * FROM topiccou WHERE topicID=$topicID";
            
            try {
                $pdo_stat = $this->dhb->query($sql);
                if(!$pdo_stat)
                    die("Greska pri dohvatanju liste izjava i drzava po temi");
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            return false;
        }
        
        function get_cname_by_id($id) {
            $sql = "SELECT name FROM countries WHERE id=$id";
            
            try {
                $pdo_stat = $this->dhb->query($sql);
                if(!$pdo_stat)
                    die("Greska pri dohvatanju naziva drzave");
                
                return $pdo_stat->fetch(PDO::FETCH_ASSOC)['name'];
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            return false;
        }
    }
    
?>
