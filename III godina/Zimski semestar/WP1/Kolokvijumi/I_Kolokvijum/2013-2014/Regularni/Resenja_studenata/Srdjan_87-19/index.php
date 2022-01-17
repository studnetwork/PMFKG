<!--
    Napomene
    --------
    Rešenje ne ispunjava zahtev za korišćenje transakcije.
    Takođe, deo za bonus nije urađen.

    Podaci o rešenju
    ----------------
    Predmet: Web programiranje
    Program: 2019
    Školska godina: 2021-2022
    Kolokvijum: I
    Autor: Srđan Todorović
    
    Podaci o zadatku
    ----------------
    Predmet: Web programiranje
    Školska godina: 2013-2014
    Kolokvijum: I
-->

<?php
    include_once './Database.php';   
    
    $db = new Database();
?>

<!DOCTYPE html>

<html>
    <head>
        <meta charset="UTF-8">
        <title></title>
    </head>
    <body>
        <h1>IMI Press vesti</h1>
        <?php
            $word_count_limit = 10;
            $news = $db->fetchNews();
            
            foreach ($news as $n) {
                echo "<br><a href='news?id="
                .$n['vest_id']."'>"
                .$n['naslov']."</a><br>";
                
                $desc = '';
                $words = explode(' ', $n['opis']);
                
                $desc .= $words[0];
                
                for ($i = 1; $i < count($words); $i++) {
                    if($i >= $word_count_limit) {
                        $desc .= '...';
                        break;
                    }
                    $desc .= " ".$words[$i];
                }
                
                
                echo "<br><span>$desc</span><br>";
            }
        ?>
    </body>
</html>
