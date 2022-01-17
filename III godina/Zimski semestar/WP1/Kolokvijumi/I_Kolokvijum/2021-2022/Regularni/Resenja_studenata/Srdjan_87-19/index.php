<!--
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
    Školska godina: 2021-2022
    Kolokvijum: I
-->


<?php
    include_once './Database.php';
    
    $db = new DB();
?>

<!DOCTYPE html>

<html>
    <head>
        <meta charset="UTF-8">
        <title></title>
        <style>
            #grupe {
                background-color: beige;
                list-style-type: none;
                margin: 0;
                padding: 0;
                overflow: hidden;
                display: block;
            }
            
            #grupe > li {
                float: left;
                padding: 10px 25px;
            }
            
            #grupe > li > a{
                text-decoration: none;
                display: block;
                text-align: center;
                font-weight: bold;
                color: gray;
            }
            
            .selected {
                background-color: lightgray;
            }
            /*
            table {
                border-spacing: 5
            }
            
            table, th, td {
                border: 1px solid black; 
            }*/
        </style>
    </head>
    <body>
        <ul id='grupe'>
            <?php
                $groups = $db->get_groups();
                
                $id = null;
                $name = null;
                foreach ($groups as $group) {
                    $id = $group['id'];
                    $name = $group['name'];
                    echo "<li";
                    if(isset($_GET['gid']) && $id === $_GET['gid'] ) {
                        echo " class='selected'";
                    }
                    echo "><a href='?gid=$id'>$name</a></li>";
                }
            ?>
        </ul>
        
        <?php 
            // deo za brisanje iz druge tabela
            if(isset($_GET['obrisi'])) {
                $id = $_GET['obrisi'];
                
                if( count($db->get_players_by_tid($id)) !== 0 ) {
                    if(!$db->deleteTeamPlayers($id)) {
                        die("Neuspesno brisanje igraca tima");
                    }
                }
                else if(!$db->deleteTeam($id)) {
                    die("Neuspesno brisanje tima");
                }
            }
            
            // prva tabela
            if(isset($_GET['gid'])) {
                $gid = $_GET['gid'];
                $teams = $db->get_teams_by_gid($gid);

                echo "<br><table border='1' cellspacing='5' style='float: left'>";
                echo "<tr><th>Ime tima</th><th>Tim</th><th>Brisanje</th></tr>"; 
                $id = null;
                $name = null;
                foreach($teams as $team) {
                    $id = $team['id'];
                    $name = $team['tim'];
                    echo "<tr>";
                    echo "<td>$name</td>";
                    echo "<td><a href='?gid=$gid&tid=$id'>Prikazi igrace</a></td>";
                    echo "<td><a href='?gid=$gid&obrisi=$id'>Obrisi tim</a></td>";
                    echo "</tr>";
                }
                echo "</table>";
                
                // druga tabela
                if(isset($_GET['tid'])) {
                    $players = $db->get_players_by_tid($_GET['tid']);
                    
                    echo "<table border='1' cellspacing='5' "
                    . "style='float: left; margin: 0 20px;'>";
                    echo "<tr><th>Ime i prezime</th><th>Biografija</th></tr>"; 
                    $bio = null;
                    $name = null;
                    foreach ($players as $player) {
                        $name = $player['ime'];
                        $bio = $player['biografija'];
                        
                        echo "<tr>";
                        echo "<td>$name</td>";
                        echo "<td>$bio</td>";
                        echo "</tr>";
                    }
                    echo "</table>";
                }
            }
                    
            echo "<br><a href='dodaj.php'>Dodaj igraca</a>";
        ?>
    </body>
</html>
