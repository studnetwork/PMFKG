<html>
    <head>
        <title>Izmena knjige</title>
        <link rel="stylesheet" href="style.css"/>
    </head>
    
    <body>
        <h1>Izmena knjige</h1>

        <div class="card">
            <form action="index.php">
                <span>Naslov</span>
                <input type="text" name="updated_title"><br>
                <span>Autor</span>
                <input type="text" name="updated_author"><br>
                <span>Godina</span>
                <input type="text" name="updated_year"><br>
                <input hidden type="number" name="book_id" value=<?php echo $_GET["book_id"]; ?>>
                <input type="submit" name="update_submit" value="Izmeni">
            </form>
        </div>
        
        <a class="card" href="index.php">Index</a>

    </body>
</html>
