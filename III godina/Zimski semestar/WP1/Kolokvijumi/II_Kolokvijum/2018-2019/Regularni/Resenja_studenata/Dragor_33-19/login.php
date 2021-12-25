<?php
include_once 'Db.php';
include_once 'Render.php';
?>

<html>
    <head>
        <title>LOGIN</title>
        <link rel="stylesheet" href="css.css"/>
    </head>
    <body>
        <?php
        $db = Db::connect();
        $writers = $db->readAllWriters();
        Render::writersRadioButtons($writers);
        Render::loginForm();
        ?>
    </body>
</html>

<script src="helper.js"></script>

<script>
function insertUsernameAndPassword(element) 
{
    let ime = element.getAttribute("ime");
    let prezime = element.getAttribute("prezime");
    document.getElementById("loginUsername").value = ime;
    document.getElementById("loginPassword").value = prezime;
}

function login()
{
    let data = {
        username: document.getElementById("loginUsername").value,
        password: document.getElementById("loginPassword").value
    }
    
    let callback = function (xhr) {
        data = JSON.parse(xhr.responseText);
        if (data['success']) {
            document.getElementById("loginFailedMessage").setAttribute("hidden", "");
            window.location = 'index.php';
        }
        else {
            document.getElementById("loginFailedMessage").removeAttribute("hidden");
        }
    }
    
    sendRequest("login", data, callback);
}
</script>