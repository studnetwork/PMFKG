<?php
    class Baza 
    {
        const ime_hosta = 'localhost';
        const korisnik = 'root';
        const sifra = '';
        const ime_baze = 'csgo';
        
        private $db;
        
        function __construct() 
        {
            try 
            {
                $konekcioni_string="mysql:host=".self::ime_hosta.";dbname=".self::ime_baze;
                $this->dbh = new PDO($konekcioni_string, self::korisnik, self::sifra);
            } catch(PDOException $e) {
                echo "GRESKA: ";
                echo $e->getMessage();
            }
        }
        
        function __destruct() 
        {
            $this->dbh = null;
        }
        
        function procitajTabelu($tabela)
        {
            try 
            {
                $sql = "SELECT * FROM " . $tabela;
                $pdo_izraz = $this->dbh->query($sql);
                
                $niz = $pdo_izraz->fetchALL(PDO::FETCH_ASSOC);
                
                return $niz;
            }
            catch(PDOException $e) 
            {
                die('Greska pri read-u!');
            }
        }
        
        function checkRadio($strana)
        {
            if(isset($_GET['strana']))
            {
                if($_GET['strana'] == $strana) return true;
            }
                
            return false;
        }
        
        function checkBox($i)
        {
            if(isset($_GET['checkBox'.$i])) return true;
            return false;
        }
        
        function checkDropDown($username)
        {
            if(isset($_GET['korisnik']))
            {
                if($_GET['korisnik'] == $username) return true;
            }
            
            return false;
        }
        
        function prikaz()
        {
            $niz = $this->procitajTabelu('user');
            
            echo "<form  action='".$_SERVER["PHP_SELF"]."' method='get'>";
            echo "<select name= 'korisnik'>";
            foreach ($niz as $korisnik)
            {
                if($this->checkDropDown($korisnik['username']))
                {
                    echo "<option value ='".$korisnik['username']."' selected>".$korisnik['username'];
                }
                
                else echo "<option value ='".$korisnik['username']."'>".$korisnik['username'];
            }
            echo "</select><br>";
            if($this->checkRadio('ct')) echo "<input type='radio' value='ct' name='strana' checked> CT<br>";
            else echo "<input type='radio' value='ct' name='strana'> CT<br>";
            if($this->checkRadio('t')) echo "<input type='radio' value='t' name='strana' checked> T<br><br>";
            else echo "<input type='radio' value='t' name='strana'> T<br><br>";
            echo "<input type='submit' value='Choose side' name='submit'><br>";
            
            $this->prikazTabele($niz);
            echo "</form>";
        }
        
        function prikazTabele($nizKorisnika)
        {
            if(isset($_GET['korisnik']) && ($this->checkRadio('ct') || $this->checkRadio('t')))
            {
                $korisnik = null;
                $nizPusaka = null;
                
                foreach ($nizKorisnika as $k)
                {
                    if($k['username'] == $_GET['korisnik']) $korisnik = $k;
                }
                
                echo "<br><span style='color:red'>Stanje na racunu: ".$korisnik['money']."$</span>";
                
                if(isset($_GET['strana']) || isset($_POST['submitBuy']))
                {
                    $nizPusaka = $this->procitajTabelu('weapon');
                    
                    echo "<br><br><table cellpadding='5' border='1'>";
                    echo "<tr><th>Name</th><th>Price</th><th>Buy</th>";
                    
                    $i = 1;
                    foreach ($nizPusaka as $puska)
                    {
                        if(($_GET['strana'] == 'ct' &&  $puska['ct'] == true) || ($_GET['strana'] == 't' &&  $puska['t'] == true))
                        {
                            echo "<tr><td>".$puska['name']."</td>"; 
                            echo "<td>".$puska['price']."</td>";
                            
                            if($this->proveriLoadout($puska)) echo "<td><input type='checkBox' name='checkBox".$i."' disabled></td></tr>";
                            else if($this->checkBox($i)) echo "<td><input type='checkBox' name='checkBox".$i."' checked></td></tr>";
                            else echo "<td><input type='checkBox' name='checkBox".$i."'></td></tr>";
                        }
                        
                        $i++;
                    }
                    echo "</table>";
                    echo "<input type='submit' value='Buy' name='submitBuy'>"; 
                }
                
                $this->kupovina($korisnik,$nizPusaka);
                $this->prikaziLoadout($korisnik);
                $this->igraj($korisnik);
                $this->dropLoadout($korisnik);
            }
            
            else if(isset($_GET['submit']))
            {
                echo '<script type ="text/JavaScript">';  
                echo 'alert("Morate odabrati stranu!")';  
                echo '</script>';  
            }
        }
        
        function kupovina($korisnik,$nizPusaka)
        {
            if(isset($_GET['submitBuy']))
            {
                $kupljenoOruzje = [];
                $ukupnaCena = 0;
                
                $i = 1;
                foreach ($nizPusaka as $puska)
                {
                    if(isset($_GET['checkBox'.$i]))
                    {
                        $ukupnaCena += $puska['price'];
                        $kupljenoOruzje[] = $puska;
                    }
                    
                    $i++;
                }
                
                if($ukupnaCena != 0)
                {
                    if($korisnik['money'] >= $ukupnaCena)
                    {
                        $this->azurirajNovac($korisnik,$korisnik['money'] - $ukupnaCena);
                        
                        if($this->checkRadio('ct')) $t_ct = 1;
                        else $t_ct = 0;
                        
                        $this->kupi($korisnik, $kupljenoOruzje, $t_ct);
                    }

                    else
                    {
                        echo "<br><br><span style='color:red'>Nemas dovoljno novca!</span>";
                    }
                }
            }
        }
        
        function azurirajNovac($korisnik,$novac)
        {
            try 
            {
                $sql = "UPDATE user SET money=:novac WHERE id=:id";
                $pdo_izraz = $this->dbh->prepare($sql);
                
                $pdo_izraz->bindParam(':id', $korisnik['id']);
                $pdo_izraz->bindParam(':novac', $novac);
                
                $pdo_izraz->execute();
                
            } catch(PDOException $e) { die("Greska pri update-u!"); }
        }
        
        function kupi($korisnik,$kupljenoOruzje,$t_ct)
        {
            try 
            {
                foreach ($kupljenoOruzje as $oruzje)
                {
                    $userID = $korisnik['id'];
                    $weaponID = $oruzje['id'];
                    
                    $sql = "INSERT INTO loadout(userID,weaponID,t_ct)";
                    $sql.= "VALUES ('$userID', '$weaponID', '$t_ct')";
                    $pdo_izraz = $this->dbh->exec($sql);
                }
                
            } catch(PDOException $e) { die("Greska pri insert-u!"); }
        }
        
        function prikaziLoadout($korisnik)
        {
            $loadout = $this->procitajTabelu('loadout');
            $oruzje = $this->procitajTabelu('weapon');
            
            echo "<br><br><table cellpadding='5' border='1'>";
            echo "<tr><th>Loadout</th>";
            foreach($loadout as $item)
            {
                if($item['userID'] == $korisnik['id'])
                {
                    foreach ($oruzje as $puska)
                    {
                        if($item['weaponID'] == $puska['id']) echo "<tr><td>".$puska['name']."</td>"; 
                    }
                }
            }
            
            echo "<input type='submit' value='PLAY' name='submitPlay'>"; 
            echo "<input type='submit' value='DROP' name='submitDrop'>"; 
        }
        
        function proveriLoadout($p)
        {
            $loadout = $this->procitajTabelu('loadout');
            $oruzje = $this->procitajTabelu('weapon');
            
            foreach($loadout as $item)
            {
                foreach($oruzje as $puska)
                {
                    if($item['weaponID'] == $puska['id'] && $puska['name'] == $p['name']) return true;
                }
            }
            
            return false;
        }
        
        function igraj($korisnik)
        {
            if(isset($_GET['submitPlay']))
            {
                $pobeda = rand(0,1);
            
                if($pobeda)
                {
                    $novac = $korisnik['money'] + 3400;
                    $this->azurirajNovac($korisnik, $novac);
                            
                    echo "<span style='color:blue'>Korisnik ".$korisnik['username']." je pobedio!</span>";
                }
                
                else
                {
                    $novac = $korisnik['money'] + 1900;
                    $this->azurirajNovac($korisnik, $novac);
                    
                    $this->obrisiLoadout($korisnik['id']);
                    
                    echo "<br><span style='color:blue'>Korisnik ".$korisnik['username']." je izgubio!</span>";
                }
            }
        }
        
        function obrisiLoadout($id)
        {
            try 
            {
                $sql = "DELETE FROM loadout WHERE userID=$id";
                $this->dbh->exec($sql);
            } catch(PDOException $e) { die("Greska pri delete-u!"); }
        }
        
        function dropLoadout($korisnik)
        {
            if(isset($_GET['submitDrop'])) $this->obrisiLoadout($korisnik['id']);
        }
    }
?>