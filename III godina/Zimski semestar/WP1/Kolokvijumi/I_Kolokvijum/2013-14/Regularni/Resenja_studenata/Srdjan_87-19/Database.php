<?php

    class Database {
        const user = 'root';
        const pw = '';
        const host = 'localhost';
        const dbname = 'press';
        
        private $dbh;
        
        function __construct() {
            $connStr = "mysql:host=".self::host.";dbname=".self::dbname;
            try {
                $this->dbh = new PDO($connStr, self::user, self::pw);
            } catch (Exception $ex) {
                die('Greska pri uspostavljanju konekcije sa bazom'
                . $ex->getMessage());
            }
        }
        
        function __destruct() {
            $this->dbh = null;
        }
        
        function fetchNews($id=-1) {
            $sql = "SELECT * FROM vesti";
            if($id !== -1)
                $sql .= " WHERE vest_id='$id'";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die('Greska pri dohvatanju svih vesti');
                
                if($id === -1)
                    return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
                else
                    return $pdo_stat->fetch(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
        }
        
        function fetchComments($newsId=-1) {
            $sql = "SELECT * FROM komentari";
            if($newsId !== -1)
                $sql .= " WHERE vest_id='$newsId'";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die('Greska pri dohvatanju svih vesti');
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
        }
        
        function fetchCommentById($cid) {
            $sql = "SELECT * FROM ckomentari WHERE comm_id=$cid";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die('Greska pri dohvatanju komentara');
                
                return $pdo_stat->fetch(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
        }
        
        function fetchCommentsOnHold($newsId=-1) {
            $sql = "SELECT * FROM ckomentari WHERE";
            if($newsId !== -1)
                $sql .= " vest_id='$newsId' AND";
            
            $sql .= " comm_id not in (SELECT komentar_id FROM komentari)";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die('Greska pri dohvatanju svih vesti');
                
                return $pdo_stat->fetchAll(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
        }
        
        function fetchUnvalidatedCommentText($cid) {
            $sql = "SELECT tekst FROM ckomentari WHERE vest_id='$cid'";
            
            try {
                $pdo_stat = $this->dbh->query($sql);
                
                if(!$pdo_stat)
                    die('Greska pri dohvatanju teksta komentara');
                
                return $pdo_stat->fetch(PDO::FETCH_ASSOC);
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
        }
        
        function addUnvalidatedComment($newsId, $text) {
            $sql = "INSERT INTO ckomentari (vest_id,tekst) "
            . "VALUES ($newsId, '$text')";
            
            try {
                $affected = $this->dbh->exec($sql);
                
                if($affected)
                    return true;
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            
            return false;
        }
        
        function addComment($newsId, $text, $pos = 0, $neg = 0) {
            $sql = "INSERT INTO komentari (vest_id,tekst,pozitivno,negativno) "
            . "VALUES ($newsId, '$text', $pos, $neg)";
            
            try {
                $affected = $this->dbh->exec($sql);
                
                if($affected)
                    return true;
            } catch (Exception $ex) {
                echo $ex->getMessage();
            }
            
            return false;
        }
        
        function deleteComment($commId) {
            $sql = "DELETE FROM ckomentari WHERE comm_id=$commId";
            
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
