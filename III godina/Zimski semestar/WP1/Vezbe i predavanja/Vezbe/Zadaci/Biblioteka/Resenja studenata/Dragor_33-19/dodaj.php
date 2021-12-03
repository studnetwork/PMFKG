<html>
    <head>
        <title>Dodavanje knjige</title>
        <link rel="stylesheet" href="style.css"/>
    </head>
    
    <body>
        <h1>Dodavanje knjige</h1>

        <div class="card">
            <form action="index.php">
                <span>Naslov</span>
                <input type="text" name="new_title"><br>
                <span>Autor</span>
                <input type="text" name="new_author"><br>
                <span>Godina</span>
                <input type="text" name="new_year"><br>
                <input type="submit" name="create_submit" value="Dodaj">
            </form>
        </div>
        
        <a class="card" href="index.php">Index</a>

    </body>
</html>
