<?php

class Knjiga_db
{
    const host = "localhost";
    const port = 3306;
    const user = "root";
    const pass = "";
    const base = "biblioteka";
    
    private $conn = null;
    private $books = [];
    private $last_search_text = "";

    public function __construct() {
        $this->connectToDB();
    }
    
    public function __destruct() {
        $this->disconnectFromDB();
    }
    
    public function main() {
        $to_search = isset($_GET["search_submit"]);
        $to_delete = isset($_GET["delete_submit"]);
        $to_update = isset($_GET["update_submit"]);
        $to_create = isset($_GET["create_submit"]);
        
        #echo "za malo: " . $_GET["delete_submit"];
        
        if ($to_search) {
            $this->last_search_text = $_GET["search_text"];
            $this->readSearchedBooks($this->last_search_text);
            $this->render();
        }
        else if ($to_delete) {
            $this->deleteBook($_GET["book_id"]);
            $this->readAllBooks();
            $this->render();
        }
        else if ($to_update) {
            $this->updateBook($_GET["book_id"], $_GET["updated_title"], $_GET["updated_author"], $_GET["updated_year"]);
            $this->readAllBooks();
            $this->render();
        }
        else if ($to_create) {
            
            $this->createBook($_GET["new_title"], $_GET["new_author"], $_GET["new_year"]);
            $this->readAllBooks();
            $this->render();
        }
        else {
            $this->readAllBooks();
            $this->render();
        }
    }

    # Connect / Disconnect
    public function connectToDB() {
        try {
            $conn_str = "mysql:host=".self::host.";dbname=".self::base;
            $this->conn = new PDO($conn_str, self::user, self::pass);
        } catch (Exception $ex) {
            echo $ex->getMessage();
        }
    }
    public function disconnectFromDB() {
        $this->conn = null;
    }

    # CRUD
    public function readAllBooks()
    {
        $query = "select * from knjige";
        $result = $this->conn->query($query);
        $this->books = $result->fetchAll(PDO::FETCH_ASSOC);
    }
    
    public function readSearchedBooks($text)
    {
        $query = "select * from knjige where naslov like '%".$text."%'";
        $result = $this->conn->query($query);
        $this->books = $result->fetchAll(PDO::FETCH_ASSOC);
    }
    
    public function deleteBook($id) {
        try {
            $query = "delete from knjige where id=".$id."";
            $statement = $this->conn->prepare($query);
            $statement->execute();
        } catch (Exception $ex) {
            echo $ex->getMessage();
        }
        #(new PDO())->prepare($query)->bindValue(":", $statement); # TESTING
    }
    
    public function updateBook($id, $title, $author, $year) {
        try {
            $query = "update knjige set "
                    . "naslov=:title, "
                    . "autor=:author, "
                    . "godina_izdanja=:year "
                    . "where id=:id";
            $statement = $this->conn->prepare($query);
            $statement->bindValue(":id", $id);
            $statement->bindValue(":title", $title);
            $statement->bindValue(":author", $author);
            $statement->bindValue(":year", $year);
            $statement->execute();
        } catch (Exception $ex) {
            echo $ex->getMessage();
        }
    }
    
    public function createBook($title, $author, $year) {
        try {
            $query = "insert into knjige (naslov, autor, godina_izdanja) "
                    . "values (:title, :author, :year)";
            $statement = $this->conn->prepare($query);
            $statement->bindValue(":title", $title);
            $statement->bindValue(":author", $author);
            $statement->bindValue(":year", $year);
            $statement->execute();
        } catch (Exception $ex) {
            echo $ex->getMessage();
        }
    }


    # Rendering
    public function render() {
        echo '<div class="card">';
        echo '<form action="" method="get">';
        echo '<input type="text" name="search_text" placeholder="Pretraga..." value="'. $this->last_search_text.'">';
        echo '<input type="submit" name="search_submit" value="Trazi">';
        
        
        echo "<table>";
        echo "<tr><th>ID</th><th>Naslov</th><th>Autor</th><th>Godina izdanja</th><th></th></tr>";
        foreach ($this->books as $b) {
            echo '<tr><td>'
            .$b["id"].'</td><td>'
            .$b["naslov"].'</td><td>'
            .$b["autor"].'</td><td>'
            .$b["godina_izdanja"].'</td>'
            .'<td><input type="button" value="brisi" '
            .'onclick="confirm(\'Da li sigurno zelite da obrisete knjigu?\')?'
                    . 'window.location = \'?book_id='.$b["id"].'&delete_submit=Da\':'
                    . '\'\''
            .'"></td>'
            .'<td><a href="izmeni.php?book_id='.$b["id"].'"><input type="button" value="izmeni"></a></td>'
            .'<td hidden><input type="number" name="book_id" value='.$b["id"].'></td>'
            .'</tr>';
        }
        echo "</table>";
        echo '</form>';
        echo '<form action="dodaj.php" method="get">';
        echo '<input type="submit" value="Dodaj">';
        echo '</form>';
        echo '</div>';
    }
    
}

?>

<!--<input type="button" value="Trazi" src="./?search=kekeke">-->