<?php
    include_once '../Database.php';   
    
    $db = new Database();
?>

<!DOCTYPE html>

<html>
    <head>
        <meta charset="UTF-8">
        <title></title>
    </head>
    <body>
        <?php

            if(isset($_GET['commID'])) {
                $comment = $db->fetchCommentById($_GET['commID']);
                $db->deleteComment($comment['comm_id']);
                $db->addComment($comment['vest_id'], $comment['tekst']);
            }
            
            if(isset($_POST['commtext'])) {
                $db->addUnvalidatedComment($_POST['newsID'], $_POST['commtext']);
                header("Location: ".$_SERVER['HTTP_REFERER']."&issnt=1");
            }
            
            $comments = $db->fetchCommentsOnHold();

            echo "<table border='1' cellspacing='5'>";
            echo "<tr><th>Tekst komentar</th><th></th></tr>";
            foreach ($comments as $comment) {
                echo "<tr>";
                echo "<td>".$comment['tekst']."</td>";
                echo "<td><a href='?commID=".$comment['comm_id']."'>"
                . "ODOBRI</a></td>";
                echo "</tr>";
            }
            echo "</table>";
        ?>
    </body>
</html>
