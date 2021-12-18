<?php

# connect() staticka metoda uspostavlja konekciju sa bazom i cuva je u privatnom atributu $conn
# Metode za komunikaciju sa bazom se koriste preko instance klase koja se dobija pomocu connect() metode,
#   a nova instanca se kreira samo u slucaju da je $instance == null, tj. nije ranije pozvana metoda connect()
#   i samo tada se uspostavlja konekcija sa bazom
class DB
{
    const con_str = 'sqlite:db.db';
    public static $instance = null;
    private $conn = null;
    
    # Konekcija sa bazom, i kreiranje singleton-a
    public static function connect()
    {
        if (self::$instance == null) 
        {
            self::$instance = new DB();
            try {
                self::$instance->conn = new PDO(self::con_str);
            } 
            catch (Exception $ex) {
                echo '<h1>GRESKA PRILIKOM KONEKCIJE SA BAZOM!!!</h1>';
            }
        }
        return self::$instance;
    }
    
    ### Metode za rad sa bazom
    
    # Da li u tabeli postoji data kombinacija korisnickih podataka?
    public function checkUserCredentials($user, $pass)
    {
        try {
            $query = 'select * from user where username="'.$user.'" and password="'.$pass.'"';
            $res = $this->conn->query($query);
            $arr = $res->fetchAll(PDO::FETCH_ASSOC);
            if ($arr == false) return false;
            return count($arr) == 1;
        } 
        catch (Exception $ex) {
            echo '<h1>GRESKA PRILIKOM PROVERE KORISNICKIH PARAMETARA!!!</h1>';
        }
    }
    
    # Kreira dati token u tabeli active_session
    public function createActiveSession($token)
    {
        try {
            $res = $this->conn->prepare('insert into active_session (id) values (:id)');
            $res->bindValue(':id', $token);
            return $res->execute();
        } 
        catch (Exception $ex) {
            echo '<h1>GRESKA PRILIKOM KREIRANJA AKTIVNE SESIJE!!!</h1>';
        }
    }
    
    # Brise dati token iz tabele active_session
    public function deleteActiveSession($token)
    {
        try {
            $res = $this->conn->prepare('delete from active_session where id=:id');
            $res->bindValue(':id', $token);
            return $res->execute();
        } 
        catch (Exception $ex) {
            echo '<h1>GRESKA PRILIKOM BRISANJA AKTIVNE SESIJE!!!</h1>';
        }
    }
    
    # Da li u tebeli postoji dati token?
    public function checkActiveSession($token)
    {
        try {
            $query = 'select * from active_session where id="'.$token.'"';
            $res = $this->conn->query($query);
            $arr = $res->fetchAll(PDO::FETCH_ASSOC);
            if ($arr == false) return false;
            return count($arr) == 1;
        } 
        catch (Exception $ex) {
            echo '<h1>GRESKA PRILIKOM PROVERE AKTIVNE SESIJE!!!</h1>';
        }
    }
}