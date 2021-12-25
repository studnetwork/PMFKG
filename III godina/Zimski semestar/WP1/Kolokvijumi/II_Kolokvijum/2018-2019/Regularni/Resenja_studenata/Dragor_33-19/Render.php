<?php

class Render
{
    public static function loginForm()
    {
        echo '
        <div class="card">
            Username:<br>
            <input type="text" id="loginUsername"><br>
            Password:<br>
            <input type="text" id="loginPassword"><br>
            Zapamti lozinku 
            <input type="checkbox">
            <button onclick="login();">Posalji</button><br>
            <b id="loginFailedMessage" style="color: red;" hidden>
                Lozinka ili korisnicko ime nisu ispravni</b>
        </div>
        ';
    }
    
    public static function writersRadioButtons($writers) 
    {
        echo '<div class="card">';
        foreach ($writers as $w) {
            echo '
                <input type="radio" name="writerRadioInput" value="'.$w["id"].'"
                onclick="insertUsernameAndPassword(this)" 
                ime="'.$w["ime"].'" prezime="'.$w["prezime"].'">
                '.$w["ime"].' '.$w["prezime"].'
                <br>
            ';
        }
        echo '</div>';
    }
}