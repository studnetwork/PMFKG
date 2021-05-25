/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
var x1, x2, korpa=[];

function loadXML() {
    if (window.XMLHttpRequest)
    {// code for IE7+, Firefox, Chrome, Opera, Safari
        xmlhttp1=new XMLHttpRequest();
        xmlhttp2=new XMLHttpRequest();
    }
    else
    {// code for IE6, IE5
        xmlhttp1=new ActiveXObject("Microsoft.XMLHTTP");
        xmlhttp2=new ActiveXObject("Microsoft.XMLHTTP");
    }
    xmlhttp1.open("GET","books.xml",false);
    xmlhttp1.send();
    xmlDoc1=xmlhttp1.responseXML; 
    x1=xmlDoc1.getElementsByTagName("book");
    
    xmlhttp2.open("GET","books_1.xml",false);
    xmlhttp2.send();
    xmlDoc2=xmlhttp2.responseXML; 
    x2=xmlDoc2.getElementsByTagName("book");
    
    for (i=0; i<x1.length; i++)
        korpa[i] = false;
    
    document.getElementById("cena").innerHTML = "0.00$";
    document.getElementById("opis").innerHTML = "VAŠA KORPA ZA KUPOVINU JE PRAZNA.";
    
}

function showBooks() {
    results = document.getElementById("tabela");
    divDesc = document.getElementById("desc");
    pretraga = document.getElementById("pretraga").value;
    pretragaPatt=/^[^0-9]*$/;

    if (pretragaPatt.test(pretraga)) {
        table = "<table>";
        for (i=0;i<x1.length;i++)
        { 
            author = x1[i].getElementsByTagName("author")[0].childNodes[0].nodeValue;
            title = x1[i].getElementsByTagName("title")[0].childNodes[0].nodeValue;
            price = x1[i].getElementsByTagName("price")[0].childNodes[0].nodeValue;
            publishDate = x1[i].getElementsByTagName("publish_date")[0].childNodes[0].nodeValue;
            desc = x1[i].getElementsByTagName("description")[0].childNodes[0].nodeValue;
            price = 1.0*price;
            date = new Date(publishDate);
            year = date.getFullYear();
            if (title.indexOf(pretraga)!=-1) {
                table += "<tr class='"+ i +"' ><td>";
                table += author;
                table += "</td><td>";
                table += title;
                table+="</td><td><input type='checkbox' onchange='Calculate(this)' name='suma' value='" + i + "' ";
                if (korpa[i])
                    table+="checked ";
                table += "/></td></tr>";
            }
        }
        table += "</table>";
        results.innerHTML = table;
    }
    else
    {
        results.innerHTML = "";
    }
}

function Calculate(check)
{
    checkValue = Number(check.value);
    if (check.checked)
    {
        korpa[checkValue]=true;
    }
    else
    {
        korpa[checkValue]=false;
    }
    var suma = 0;
    table = "<table>";
    for (i = 0; i < korpa.length; i++) {
        //alert(select[i].value);
        if (korpa[i])
        {
            suma = suma + parseFloat(x1[i].getElementsByTagName("price")[0].childNodes[0].nodeValue);
            table += "<tr><td>" + x1[i].getElementsByTagName("title")[0].childNodes[0].nodeValue + "</td></tr>";
        }
    }
    table += "</table>";
    
    document.getElementById("opis").innerHTML = table;
    if (suma==0)
        document.getElementById("opis").innerHTML = "VAŠA KORPA ZA KUPOVINU JE PRAZNA.";
    
    document.getElementById("cena").innerHTML = suma.toFixed(2) + "$";
    
    ShowRecommendation();
}

function ShowRecommendation()
{       
    table = "<table id='books'>";
    for (i = 0; i < korpa.length; i++) {
        for (j = 0; j < x2.length; j++) {
            if(korpa[i] && x1[i].getAttribute("id") === x2[j].getElementsByTagName("related")[0].childNodes[0].nodeValue)
            {
                table += "<tr><td>" + x2[j].getElementsByTagName("title")[0].childNodes[0].nodeValue + "</td></tr>";
            }
        }
    }
    table += "</table>";
    document.getElementById("recomm").innerHTML = table;
    
    // Malo DOM-a
    var spannode = document.createElement("span");
    var textnode = document.createTextNode("Recommended products:");
    spannode.appendChild(textnode);
    var newItem = document.createElement("p");
    document.getElementById("recomm").insertBefore(spannode, document.getElementById("books"));
    document.getElementById("recomm").insertBefore(newItem, document.getElementById("books"));
    
    document.getElementById("recomm").style.display = "block";
}





