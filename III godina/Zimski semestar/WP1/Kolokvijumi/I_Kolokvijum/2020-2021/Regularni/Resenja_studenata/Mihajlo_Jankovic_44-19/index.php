<?php
    include_once 'csgo.php';
    $baza = new Baza();
?>

<html>
    <head>
        <meta charset="UTF-8">
        <title>Index</title>
    </head>
    <body>
        <?php
            $baza->prikaz();
        ?>
    </body>
</html>
