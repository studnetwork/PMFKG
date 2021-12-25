<?php
include_once 'Db.php';
$db = Db::connect();

if (($data = P("login")) != null)
{
    $result = $db->checkUsernameAndPassword($data->username, $data->password);
    
    $response = ['success' => false];
    if ($result != null) {
        $response = ['success' => true];
        setcookie('username', $result['ime'].' '.$result['ime'], time()+86400);
        setcookie('role', $result['uloga'], time()+86400);
        setcookie('id', $result['id'], time()+86400);
    }
    
    echo json_encode($response);
}

if (($data = P("search")) != null)
{
    $response = [];
    $response['books'] = $db->searchBooks($data->book);
    $response['writers'] = $db->searchWriters($data->writer);
    
    echo json_encode($response);
}

if (($data = P("delete")) != null)
{
    $response = [];
    $db->deleteCascade($data->writer_id);
}

if (($data = P("logout")) != null) 
{
    setcookie('username', '', 0);
    setcookie('role', '', 0);
    setcookie('id', '', 0);
    
    // Iako se setuje ovaj header klijent ne radi redirect ako je zahtev poslat preko AJAX-a
    //header('Location: login.php'); 
}

//if (($data = P("checkAdmin")) != null) {
//    $role = $db->getRole($data->writer_id);
//    if ()
//}

//$response = ['success' => true];
//return json_encode($response);

    
function P($name) {
    if (isset($_POST[$name])) {
        return json_decode($_POST[$name]);
    }
    return null;
}