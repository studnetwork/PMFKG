var totalAmount = 0;
var xml_arr,link_arr;
var korpa = [];

// Ajax
function loadXML()
{
    var xhttp = new XMLHttpRequest();
    var xlink = new XMLHttpRequest();
    
    xlink.onreadystatechange = function()
    {
        if (this.readyState == 4 && this.status == 200) 
        {
            link_arr = this.responseXML.getElementsByTagName("book");  
        }
    };
    
    xlink.open("GET", "books_1.xml", true);
    xlink.send();
    
    xhttp.onreadystatechange = function()
    {
        if (this.readyState == 4 && this.status == 200) 
        {
            xml_arr = this.responseXML.getElementsByTagName("book");
            for(var i = 0; i < xml_arr.length; i++) korpa[i] = false;
            
             showBooks(xml_arr, new RegExp(""));
        }
    };
    
    xhttp.open("GET", "books.xml", true);
    xhttp.send();
}

// Show books on page
function showBooks(xml_arr, regex)
{
    var tmp;
    var tabela = "<table>";
    var tabela_korpa = "<table>";
    var tabela_recomm = "<table>";
    
    for(var i = 0; i < xml_arr.length; i++)
    {
        if(regex.test(xml_arr[i].getElementsByTagName("author")[0].childNodes[0].nodeValue, "ig") || regex.test(xml_arr[i].getElementsByTagName("title")[0].childNodes[0].nodeValue))
        {
            tabela += "<tr><td>";
            tabela += xml_arr[i].getElementsByTagName("author")[0].childNodes[0].nodeValue;
            tabela += "</td><td>";
            tabela += xml_arr[i].getElementsByTagName("title")[0].childNodes[0].nodeValue;
            tabela += "</td>";
            
            if(korpa[i]) tabela += "<td><input id='"+ i +"' type='checkBox' onclick='addToCart("+i+")' value='" + i + "' checked/></td></tr>";
            
            else tabela += "<td><input id='"+ i +"' type='checkBox' onclick='addToCart("+i+")' value='" + i + "'/></td></tr>";
        }
        
        if(korpa[i])
        {
            // Korpa
            tabela_korpa += "<tr><td>";
            tabela_korpa += xml_arr[i].getElementsByTagName("title")[0].childNodes[0].nodeValue;
            tabela_korpa += "</td></tr>";
            
            // Preporuceno
            for(var j = 0; j < link_arr.length; j++)
            {
                book_id = xml_arr[i].attributes["id"].value;
                link_id = link_arr[j].getElementsByTagName("related")[0].childNodes[0].nodeValue;
                
                if(book_id == link_id)
                {
                    tabela_recomm += "<tr><td>";
                    tabela_recomm += link_arr[j].getElementsByTagName("title")[0].childNodes[0].nodeValue;
                    tabela_recomm += "</td></tr>";
                }
            }
        }

    }
    
    tabela += "</table>";
    tabela_korpa += "</table>";
    tabela_recomm += "</table>";
    
    document.getElementById("tabela").innerHTML = tabela;
    document.getElementById("tabela_korpa").innerHTML = tabela_korpa;
    document.getElementById("cena").innerHTML = totalAmount + "$";
    document.getElementById("recomm").innerHTML = tabela_recomm;
}

// Search
function search()
{
    var str = document.getElementById("pretraga").value;
    var regex = /[^0-9]/;
    
    if(regex.test(str) || str == "")
    {
        if(str != "") regex = "(\\" + str +")+";
        else regex = str;
        
        showBooks(xml_arr, new RegExp(regex,"ig"));
    }
    
    else alert("Ne smes unositi brojeve u pretragu!");
}

function addToCart(i)
{
    if(document.getElementById(i).checked)
    {
        korpa[i] = true;
        totalAmount += parseInt(xml_arr[i].getElementsByTagName("price")[0].childNodes[0].nodeValue);
    }
    
    else
    {
        korpa[i] = false;
        totalAmount -= parseInt(xml_arr[i].getElementsByTagName("price")[0].childNodes[0].nodeValue);
    }
    
    regex = document.getElementById("pretraga").value;
    
    if(regex != "") regex = "\\" + regex;
    showBooks(xml_arr, new RegExp(regex));
}