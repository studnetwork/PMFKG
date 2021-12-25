<?php
if (!isset($_COOKIE["username"])) {
    header('Location: login.php');
}
?>

<html>
    <head>
        <title>INDEX</title>
        <link rel="stylesheet" href="css.css"/>
    </head>
    <body>
        Pisac:
        <input id="search_writer" type="text" oninput="search(this);">
        Knjiga:
        <input id="search_book" type="text" oninput="search(this);">
        <br><br>
        
        <div id="table"></div>
        
        <button onclick="logout()">LOGOUT</button>
        
    </body>
</html>

<script src="helper.js"></script>

<script>
renderTableForEmptyInput();

function search(element)
{
    // Reference na elemente
    let sw = document.getElementById('search_writer');
    let sb = document.getElementById('search_book');
    
    // Brisanje jednog inputa ako se unosi drugi
    if (element == sw)
        sb.value = '';
    else
        sw.value = '';
    
    // Priprema podataka
    let data = {
        book: sb.value,
        writer: sw.value
    }
    
    // Callback
    let callback = function (xhr) 
    {
        let resp = JSON.parse(xhr.responseText);
        let books = resp['books'];
        let writers = resp['writers'];
        
        renderTable(books, writers);
    }
    
    // Zahtev
    sendRequest('search', data, callback);
}

function renderTable(b, w)
{
    let html = '<table>';
    for (let i = 0; i < w.length; i++) {
        w[i]['books'] = [];
        for (let j = 0; j < b.length; j++) {
            if (w[i]['id'] == b[j]['pisac_id']) {
                w[i]['books'].push(b[j]);
            }
        }
    }
    
    for (let i = 0; i < w.length; i++) 
    {
        let n = w[i]['books'].length;
        for (let j = 0; j < w[i]['books'].length; j++) 
        {
            html += '<tr>';
            html += '<td>'+w[i]['books'][j]['naslov']+'</td>';
            if (j == 0) {
                html += '<td rowspan='+n+'>'+w[i]['ime']+' '+w[i]['prezime']+'</td>';
                
                let r = getCookie('role');
                if (r != null && r == 'admin')
                    html += '<td rowspan='+n+'><button onclick="deleteCascade('+w[i]['id']+')">X</button></td>';
            }

            html += '</tr>';
        }
    }
    
    html += '</table>';
    document.getElementById('table').innerHTML = html;
}

function deleteCascade(writerId)
{
    let callback = function (bzvz) { renderTableForEmptyInput(); }
    sendRequest('delete', {writer_id: writerId}, callback);
}

function renderTableForEmptyInput()
{
    search(document.getElementById('search_writer'));
}

function logout()
{
    sendRequest('logout', {}, function () { window.location = ''; });
}

function getCookie(name)
{
    let arr = document.cookie.split(';');
    for (let i = 0; i < arr.length; i++) {
        let t = arr[i].split('=');
        if (t[0].trim() == name) {
            return t[1].trim();
        }
    }
    
    return null;
}
</script>