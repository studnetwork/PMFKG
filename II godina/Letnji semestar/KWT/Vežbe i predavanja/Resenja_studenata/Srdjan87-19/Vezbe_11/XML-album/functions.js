var xmlDoc;
var cds;

function ucitajXML() {
    var httpXml = new XMLHttpRequest();
    
    httpXml.onreadystatechange = function () {
        if( this.readyState == 4 && httpXml.status == 200 ) {
            xmlDoc = this.responseXML;
            cds = xmlDoc.getElementsByTagName("CD");
        }
    }
    
    httpXml.open("GET", "cd_catalog.xml", true);
    httpXml.send();
}            

function prikaziKatalog() {
    var tableContent = "<tr><th>Artist</th><th>Title</th></tr>";
    
    var artist;
    var title;
    for (var i = 0; i < cds.length; i++) {
        tableContent += '<tr onclick="prikaziInfo('+i+')">';
        //artist = cds[i].getElementsByTagName("ARTIST")[0].childNodes[0].nodeValue;
        artist = cds[i].getElementsByTagName("ARTIST")[0].textContent;
        title = cds[i].getElementsByTagName("TITLE")[0].textContent;
        
        tableContent += "<td>" + artist + "</td>";
        tableContent += "<td>" + title + "</td>";
        tableContent += "</tr>";
    }
    
    document.getElementById("tabela").innerHTML = tableContent;
}

function prikaziInfo(i) { 
    
    var info = document.getElementById("info");

    var artist = cds[i].getElementsByTagName("ARTIST")[0].textContent;
    var title = cds[i].getElementsByTagName("TITLE")[0].textContent;
    var year = cds[i].getElementsByTagName("YEAR")[0].textContent;
    var country = cds[i].getElementsByTagName("COUNTRY")[0].textContent;
    var company = cds[i].getElementsByTagName("COMPANY")[0].textContent;
    var price = cds[i].getElementsByTagName("PRICE")[0].textContent;
    
    var text = "Artist: " + artist + "</br>";
    text += "Title: " + title + "</br>";
    text += "Year: " + year + "</br>";
    text += "Country: " + country + "</br>";
    text += "Company: " + company + "</br>";
    text += "Price: " + price + "</br></br>";
    
    info.innerHTML = text;
    
    if( info.innerHTML != "" ) {
        var button = document.createElement("button");
        
        button.innerHTML = "&lt;&lt";
        button.onclick = function() {
            prikaziInfo( cds.length * (i==0) + i - 1 );
        };
        
        info.appendChild(button);
        
        button = document.createElement("button");
        
        button.innerHTML = "&gt;&gt";
        button.onclick = function() {
            prikaziInfo( (i+1) % cds.length );
        };
        
        info.appendChild(button);
    }
}
             
