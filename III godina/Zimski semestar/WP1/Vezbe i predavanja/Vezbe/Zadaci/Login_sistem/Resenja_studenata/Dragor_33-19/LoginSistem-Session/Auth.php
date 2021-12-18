<?php
include_once 'DB.php';

# Klasa preko koje se realizuju sve akcije vezane za autentifikaciju
# session_start() - zapocinje rad sa sesijom, kreira jednu ukoliko mu korisnicki browser
#   u headeru http zahteva nije poslao PHPSESSID Cookie
#   (koji sadrzi id fajla na serveru koji predstavlja sesiju i cuva podatke ubacene u $_SESSION),
#   u suprotnom nastavlja rad sa vec postojecom, kopira podatke iz fajla u $_SESSION
# session_commit() - cuva podatke iz $_SESSION u odgovarajuci session fajl i prekida rad sa sesijom
#   (ukoliko se dva puta za redom pozove session_start(), bez prethodno zatvorene sesije, dolazi do greske)
# session_write_close() radi isto sto i session_commit()
class Auth
{
    # Setovan $_SESSION['loggedin'] je indikator da je korisnik sa odgovarajucom sesijom ulogovan
    #   a setuje se samo ako su ispravno uneti sifra i username
    # Povratna vrednost oznacava da li je login bio uspesan ili ne
    public static function login($user, $pass) 
    {
        $pass = sha1($pass);
        
        $db = DB::connect();
        $loggedin = $db->checkUserCredentials($user, $pass);
        
        if ($loggedin) 
        {
            session_start();
            $_SESSION['loggedin'] = $user;
            session_commit();
        }
        
        return $loggedin;
    }
    
    public static function logout()
    {
        session_start();
        session_destroy();
    }
    
    # Ukoliko je indikator $_SESSION['loggedin'] setovan u datoj sesiji 
    #   (u fajlu na serveru sa id-jem koji je klijentski browser automatski poslao u headeru http request-a)
    #   znaci da je korisnik sa tom sesijom ulogovan (ne trazi mu se ponovo sifra i username)
    public static function checkLoggedIn() 
    {
        session_start();
        if (isset($_SESSION['loggedin']))
        {
            session_commit();
            return true;
        }
        
        return false;
    }
}