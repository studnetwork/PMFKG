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
    Školska godina: 2020-2021
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
    </head>
    <body>
        <form>
            <h3>Izaberite temu:</h3>
            <select name="topic">
                <?php
                    $topics = $db->get_all_topic();
                    
                    $selected = 0;
                    
                    if(isset($_GET['topic'])) {
                        $selected = $_GET['topic'];
                    }
                    
                    foreach ($topics as $topic) {
                        echo "<option value='".$topic['id']."' ";
                        if($topic['id'] == $selected)
                            echo "selected";
                        echo ">".$topic['topic']."</option>";
                    }
                ?>
            </select>
            <br>
            <br>
            <input type='submit' value='prikazi'>
        </form>
        <br>
        <?php
            if(isset($_GET['topic'])) {
                $cstatements = $db->get_all_cstatements_by_topic($_GET['topic']);
                    
                echo "<table border='1' cellspacing='5'>";
                echo "<tr><th>Ime drzave</th><th>Izjava predsednika</th>"
                . "<th>Klasifikacija</th></tr>";
                
                $keywords = ['dobar', 'odlican', 'razvoj', 'napredak', 'buducnost'];
                $needle = "Srbija";
                
                // pretraga, bojenje i klasifikacija
                foreach ($cstatements as $cstatement) {
                    $cid = $cstatement['countryID'];
                    $cname = $db->get_cname_by_id($cid);
                    $statement = $cstatement['statement'];
                    
                    $is_positive_class = 0; // pretpostavka da se ne klas. pozitivno
                    
                    if(strpos($statement, $needle)!== false) {
                        $words = explode(' ', $statement);
                        
                        $offsets = [-3, -2, -1, 1, 2, 3];//,4];
                        
                        for ($i = 0; $i < count($words); $i++) {
                            if($words[$i] === $needle) {
                                foreach ($offsets as $offset) {
                                    // proveri okolinu trazene reci
                                    if($i+$offset>=0 && $i+$offset < count($words) 
                                    && in_array(strtolower($words[$i+$offset]), $keywords)) {
                                        $is_positive_class = 1;
                                        $words[$i+$offset] = 
                                                "<span style='color: red'>" .
                                                $words[$i+$offset] .
                                                "</span>";
                                    }
                                }
                            }
                        }
                        
                        $statement = implode(' ', $words);
                    }
                    
                    echo "<tr><td><a href='?cid=$cid'>$cname</a></td>";
                    echo "<td>".$statement."</td>";
                    echo "<td>".( ($is_positive_class)? 'Pozitivno':'Negativno')."</td>";
                    echo "</tr>";
                }
                echo "</table>";
            }
            // Drugi prikaz
            else if(isset($_GET['cid'])) {
                echo "<span style='font-weight: bold'>Izjava zemlje:</span>";
                echo $db->get_cname_by_id($_GET['cid']);
                
                $cstatements = $db->get_all_cstatements_by_country($_GET['cid']);
                
                echo "<br><br><table border='1' cellspacing='5'>";
                echo "<tr><th>Teme</th><th>Izjava predsednika</th></tr>";
                
                foreach ($cstatements as $cstatement) {
                    $tid = $cstatement['topicID'];
                    $statement = $cstatement['statement'];
                    $topic = $db->get_topic_by_id($tid)['topic'];
                    
                    echo "<tr><td>$topic</td>";
                    echo "<td>".$statement."</td>";
                    echo "</tr>";
                }
                
                echo "</table>";
            }
        ?>
    </body>
</html>
