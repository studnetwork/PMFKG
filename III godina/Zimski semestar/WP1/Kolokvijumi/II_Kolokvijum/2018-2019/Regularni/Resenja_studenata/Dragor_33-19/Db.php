<?php

class Db
{
    private const conn_str = "sqlite:db.db";
    private $conn = null;
    
    private  static $instance = null;
    
    public static function connect()
    {
        if (self::$instance == null) {
            self::$instance = new Db();
        }
        
        if (self::$instance->conn == null) {
            try {
                self::$instance->conn = new PDO(self::conn_str);
            } 
            catch (Exception $ex) {
                self::$instance->conn = null;
                echo $ex;
            }
        }
        
        return self::$instance;
    }
    
    // CRUD
    
    public function readAllWriters()
    {
        try {
            $res = $this->conn->query("select * from pisac");
            return $res->fetchAll(PDO::FETCH_ASSOC);
        }
        catch (Exception $ex) {
            echo $ex;
        }
    }
    public function checkUsernameAndPassword($user, $pass)
    {
        try {
            $query = 'select * from pisac where ime="'.$user.'"  and prezime="'.$pass.'"';
            $res = $this->conn->query($query);
            $arr = $res->fetchAll(PDO::FETCH_ASSOC);
            return (count($arr) == 1)? $arr[0] : null;
        }
        catch (Exception $ex) {
            echo $ex;
        }
    }
    
    public function searchWriters($str)
    {
        try {
            $query = 'select * from pisac where ime like "%'.$str.'%" or prezime like "%'.$str.'%"';
            $res = $this->conn->query($query);
            return $res->fetchAll(PDO::FETCH_ASSOC);
        }
        catch (Exception $ex) {
            echo $ex;
        }
    }
    
    public function searchBooks($str)
    {
        try {
            $query = 'select * from knjiga where naslov like "%'.$str.'%"';
            $res = $this->conn->query($query);
            return $res->fetchAll(PDO::FETCH_ASSOC);
        }
        catch (Exception $ex) {
            echo $ex;
        }
    }
    
    public function deleteCascade($writer_id)
    {
        try {
            $this->conn->beginTransaction();
            $this->conn->exec('delete from pisac where id='.$writer_id);
            $this->conn->exec('delete from knjiga where pisac_id='.$writer_id);
            $this->conn->commit();
        }
        catch (Exception $ex) {
            $this->conn->rollBack();
            echo $ex;
        }
    }
    
//    public function getRole($id)
//    {
//        try {
//            $query = 'select uloga from knjiga where id='.$id;
//            $res = $this->conn->query($query);
//            return $res->fetchAll(PDO::FETCH_ASSOC);
//        }
//        catch (Exception $ex) {
//            echo $ex;
//        }
//    }
    
    
}