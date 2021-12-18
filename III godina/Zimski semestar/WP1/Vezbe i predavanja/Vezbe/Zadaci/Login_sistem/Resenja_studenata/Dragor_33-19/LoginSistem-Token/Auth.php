<?php
include_once 'DB.php';

# Klasa preko koje se realizuju sve akcije vezane za autentifikaciju
class Auth
{
    # Naziv Cookie-ja (u daljem opisu "token") koji kao vrednost cuva SHA1 hash stringa sastavljenog od korisnickih podataka
    const token_name = 'session_token';
    
    # Ukoliko su tacni lozinka i username, kreira se token i cuva u bazi (gde predstavlja "aktivnu sesiju")
    public static function login($user, $pass) 
    {
        $pass = sha1($pass);
        
        $db = DB::connect();
        $loggedin = $db->checkUserCredentials($user, $pass);
        
        if ($loggedin) 
        {
            $token = sha1($user.$pass.time());
            $db->createActiveSession($token);
            setcookie(self::token_name, $token, time()+120);
        }
        
        return $loggedin;
    }
    
    # Ukoliko je klijent poslao token (znaci da postoji aktivna sesija), obrisati ga (kod klijenta i u bazi)
    public static function logout() 
    {
        if (isset($_COOKIE[self::token_name])) 
        {
            $db = DB::connect();
            
            # brisanje tokena u bazi
            $db->deleteActiveSession($_COOKIE[self::token_name]);
            
            # brisanje tokena (klijent ce promeniti expiration date tokena (Cookie) tako da se on obrise)
            setcookie(self::token_name, '', 0);
        }
    }


    # Ukoliko je klijent poslao token proveriti da li je sesija aktivna, u suprotnom sigurno nije ulogovan
    public static function checkLoggedIn() 
    {
        if (isset($_COOKIE[self::token_name]))
        {
            $db = DB::connect();
            $token = $_COOKIE[self::token_name];
            
            if ($db->checkActiveSession($token)) {
                return true;
            }
            
            # ukoliko je klijent poslao token a ne postoji odgovarajuca aktivna sesija, 
            #   onda je on istekao/neispravan, pa se trazi od klijenta da ga izbrise
            setcookie(self::token_name, '', 0);
        }
        
        return false;
    }
}