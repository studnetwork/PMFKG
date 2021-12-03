<?php
include_once "Knjiga_db.php";
?>

<html>
    <head>
        <title>Index</title>
        <link rel="stylesheet" href="style.css"/>
    </head>
    <body>
        <?php
        $b = new Knjiga_db();
        $b->main();
        ?>
    </body>
</html>



