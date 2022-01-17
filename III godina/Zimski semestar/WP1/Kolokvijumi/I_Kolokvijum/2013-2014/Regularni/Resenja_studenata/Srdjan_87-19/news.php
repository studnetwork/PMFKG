<?php
    include_once './Database.php';   
    
    $db = new Database();
?>

<!DOCTYPE html>

<html>
    <head>
        <meta charset="UTF-8">
        <title></title>
        <style>
            body {
                background-color: darkgrey;
            }
            .comment {
                background-color: gainsboro;
                margin: 15px;
                padding: 20px;
                width: 20%;
                border-radius: 5px;
                font-weight: bold;
                color: slategrey;
            }
        </style>
    </head>
    <body>
        <?php
            if(isset($_GET['id'])) {
                $news = $db->fetchNews($_GET['id']);
                
                echo "<h1>".$news['naslov']."</h1>";
                echo "<p>".$news['opis']."</p>";
                
                $comments = $db->fetchComments($_GET['id']);
                
                foreach($comments as $comment) {
                    echo "<div class='comment'>".$comment['tekst']."</div>";
                }
                
                echo "<form method='post' action='Komentari/validacija.php'>";
                echo "<input type='hidden' name='newsID' value='".$_GET['id']."'>";
                echo "<textarea cols='60' rows='10' name='commtext'>"
                . "</textarea><br>";
                echo "<input type='submit' value='Dodaj komentar'>";
                echo "</form>";
                
                if(isset($_GET['issnt'])) {
                    echo "<br><br><span style='font-weight: bold'>"
                    . "Komentar je poslat na pregled administratoru</span>";
                }
            }
        ?>
    </body>
</html>
