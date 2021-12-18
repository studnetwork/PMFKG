<style>
    body {
        background-color: #f1f1f1;
    }
    .card, .btn {
        display: inline-block;
        margin: 5px;
        padding: 0.3em;
        background-color: #f9f9f9;
        color: black;
        border: 1px solid #a0a0a0;
        border-radius: 4px;
        box-shadow: 0 0.3em 1em -0.3em #bbb;
    }
    
    .btn:hover {
        background-color: #dddddd;
        border: 1px solid #888888;
    }
    .btn:active {
        background-color: #bbbbbb;
        border: 1px solid #888888;
        box-shadow: 0 0 0 0 black;
    }
</style>

<?php

# Klasa cije staticke metode sluze za kreiranje predefinisanih html elemenata
class RenderHTML
{
    public static function card($text) {
        echo '<b class="card">'.$text.'</b><br>';
    }
    
    public static function loginForm($user_val = '', $get = false) {
        echo '
        <div class="card">
            <b>Login</b><br><br>
            <form action="./" method="'.(($get)?'get':'post').'" style="margin:0;">
                <input type="text" name="login_username" placeholder="Username" value="'.$user_val.'">
                <input type="password" name="login_password" placeholder="Password">
                <input type="submit" name="login_submit" value="LOGIN">
            </form>
        </div>
        <br>
        ';
    }
    
    public static function linkButton($text, $href) {
        echo '<a href="'.$href.'"><div class="btn">'.$text.'</div></a><br>';
    }
}