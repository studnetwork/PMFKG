<?php
include_once 'RenderHTML.php';
include_once 'Auth.php';
?>

<html>
    <head>
        <title>PAGE 4</title>
    </head>
    <body>
        <?php
        # Ukoliko je zahtevan logout
        if (isset($_GET['logout'])) {
            Auth::logout();
        }
        
        # Zahtevan je login
        if (isset($_POST['login_submit']) && isset($_POST['login_username']) && isset($_POST['login_password'])) 
        {
            $username = $_POST['login_username'];
            $password = $_POST['login_password'];
            
            # Poruka za uspesan login
            if (Auth::login($username, $password)) {
                RenderHTML::card('Uspesno ste ulogovani!');
                RenderHTML::linkButton('Nastavi', './');
            }
            # Poruka za neuspesan login
            else {
                RenderHTML::card('Neispravni kredencijali...');
                RenderHTML::linkButton('Pokusaj ponovo', './');
            }
        }
        # Nije zahtevan login
        else {
            # Pocetna strana, ako je korisnik ulogovan
            if (Auth::checkLoggedIn()) {
                RenderHTML::card('# POCETNA STRANA #');
                RenderHTML::linkButton('LOGOUT', './?logout=true');
                RenderHTML::linkButton('REFRESH', './');
            }
            # Strana za logovanje, ako korisnik nije ulogovan
            else {
                RenderHTML::loginForm();
                RenderHTML::linkButton('REFRESH', './');
            }
        }
        
        
        
        ?>
    </body>
</html>
