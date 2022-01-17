<?php
    include_once './Database.php';
    
    $db = new DB();
?>

<!DOCTYPE html>

<html>
    <head>
        <meta charset="UTF-8">
        <title></title>
    </head>
    <body>
        <h2>Unesite novog igraca</h2>
        <br>
        <form>
            Ime i prezime:
            <br>
            <input type="text" name="playerName"
                    value="<?php if(isset($_GET['playerName'])) echo $_GET['playerName']; ?>">
            <br><br>
            Biografija: <br>
            <textarea name='bio' cols='20' rows='5'>
                <?php 
                    if(isset($_GET['bio']))
                        echo trim($_GET['bio']); 
                ?>
            </textarea>
            <br><br>
            
            <?php
                $groups = $db->get_groups();
                
                $id = null;
                $name = null;
                echo "<div id='grupe' style='display: block; padding: 10px'>";
                
                $groupIDs = [];
                foreach ($groups as $group) {
                    $id = $group['id'];
                    $name = $group['name'];
                    echo "<input type='radio' value='$id' name='gid'";
                    if(isset($_GET['gid']) && $_GET['gid'] === $id) {
                        echo " checked";
                    }
                    echo " onclick='showTeams(this,$id)'>&nbsp;$name<br>";
                    $groupIDs[] = $id;
                }
                echo "</div>";
                
                foreach ($groupIDs as $groupID) {
                    echo "<div id='t$groupID' style='display: none; padding: 10px'>";

                    $teams = $db->get_teams_by_gid($groupID);
                    foreach($teams as $team) {
                        $id = $team['id'];
                        $name = $team['tim'];
                        echo "<input type='radio' value='$id' name='tid'";
                        if(isset($_GET['tid']) && $_GET['tid'] === $id) {
                            echo " checked";
                        }
                        echo ">&nbsp;$name<br>";
                    }
                    echo "</div>";
                }
            ?>
            <br>
            <input type="submit"  value='Submit' name="Dodaj">
        </form>
        
        <?php
            if(isset($_GET['tid'])) {
                if(!$db->add_player($_GET['tid'], $_GET['playerName'], $_GET['bio'])) {
                    echo "<span styple='color: red'>Greska pri dodavanju igraca</span>";
                }
            }
        ?>
    </body>
    <script>
        function showTeams(gdiv,gid) {
            let grupeDiv = document.getElementById('grupe');
            let timoviDiv = document.getElementById('t'+gid);
            
            grupeDiv.style.display = "none";
            timoviDiv.style.display = "block";
        }
    </script>
</html>
