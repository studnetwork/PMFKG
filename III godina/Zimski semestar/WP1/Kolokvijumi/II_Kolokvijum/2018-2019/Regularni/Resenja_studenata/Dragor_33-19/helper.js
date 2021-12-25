function sendRequest(action, payload, callback)
{
    xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function () {
        if (xhr.readyState == 4 && xhr.status == 200) {
            callback(xhr);
        }
    }
    
    xhr.open('post', 'api.php', true);
    xhr.setRequestHeader('content-type', 'application/x-www-form-urlencoded');
    xhr.send(action + '=' + JSON.stringify(payload));
}


