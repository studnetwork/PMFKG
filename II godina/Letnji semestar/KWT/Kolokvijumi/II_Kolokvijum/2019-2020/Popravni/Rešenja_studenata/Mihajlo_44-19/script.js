var xml_arr = new Array();
var major_arr = new Array();
var currentMajor = null;

function loadXML() 
{
    var xhttp = new XMLHttpRequest();
    
    xhttp.onreadystatechange = function() 
    {
          if (this.readyState == 4 && this.status == 200) 
          {
              xml_arr = this.responseXML.getElementsByTagName("student");
              setMajors();
          }
    };
    
    xhttp.open("GET", "students.xml", false);
    xhttp.send();
}

function setMajors()
{
    for (var i = 0; i < xml_arr.length; i++) 
    {
        var flag = 1;
        major = xml_arr[i].getElementsByTagName("major")[0].childNodes[0].nodeValue;
        
        for(var j = 0; j < major_arr.length; j++) if(major_arr[j] == major) flag = 0;
        
        if(flag) major_arr[major_arr.length] = major;
    }
    
    
    var options = "";
    for (var i = 0; i < major_arr.length; i++) 
    {   
        options += "<option onclick='showTable(\"" + major_arr[i] + "\"), setCurrentMajor(\"" + major_arr[i] + "\")'>" + major_arr[i] + "</option>";
    }
    
    document.getElementById("selectMajor").innerHTML = options;
    setCurrentMajor(major_arr[0]);
    showTable(major_arr[0]);
}

function setCurrentMajor(major)
{
    currentMajor = major;
}

function showTable(major)
{
    
    var table = "<table>";
    
    table += "<th><tr><td>Ime</td><td>Prezime</td><td>Zemlja</td><td>Godine</td></tr></th>";
    for (var i = 0; i < xml_arr.length; i++)
    {
       
        if(xml_arr[i].getElementsByTagName("major")[0].childNodes[0].nodeValue == major)
        {          
            name = xml_arr[i].getElementsByTagName("name")[0].childNodes[0].nodeValue;
            name_arr = name.split(" ");
            
            country = xml_arr[i].getElementsByTagName("country")[0].childNodes[0].nodeValue;
            id = xml_arr[i].attributes["id"].value;
            
            table += "<tr onclick='studentInfo(\"" + id + "\")'>";
            table += "<td>" + name_arr[0] + "</td>";
            table += "<td>" + name_arr[1] + "</td>";
            table += "<td>" + country + "</td>";
            table += "<td id='godine"+ i +"'><img src=\"images/x_mark.png\" alt=\"alt\"/></td>"; 
            table += "</tr>";
        }
    }
    
    table += "</table>";
    
    document.getElementById("tabela").innerHTML = table;
}

function search()
{
    var searchBar = document.getElementById("txtAge");
    
    switch(searchBar.value)
    {
        case "":
            searchBar.style.backgroundColor = "salmon";
            if(currentMajor != null) showTable(currentMajor);
            break;
            
        default:
            var value = parseInt(searchBar.value);
            regex = /^[0-9]+$/;
            
            if(regex.test(searchBar.value) && value >= 18 && value <= 30)
            {
                searchBar.style.backgroundColor = "lightgreen";
                
                for(var i = 0; i < xml_arr.length; i++)
                {
                    if(currentMajor == xml_arr[i].getElementsByTagName("major")[0].childNodes[0].nodeValue)
                    {
                        birthDate = new Date(xml_arr[i].getElementsByTagName("age")[0].childNodes[0].nodeValue);
                        ageDifMs = Date.now() - birthDate;
                        ageDate = new Date(ageDifMs);
                        age = Math.abs(ageDate.getUTCFullYear() - 1970);

                        if(value < age)
                        {
                            str = "Stariji";
                        }

                        else if(value == age)
                        {
                            str = "Jedanko";
                        }

                        else str = "Mladji";

                        
                        document.getElementById("godine"+i).innerHTML = str;
                    }
                }
            }
            
            else
            {
                searchBar.style.backgroundColor = "salmon";
                showTable(currentMajor);
            }
            break;
    }
}

function studentInfo(id)
{
    var string = "";
    
    for (var i = 0; i < xml_arr.length; i++)
    {
        if(xml_arr[i].attributes["id"].value == id)
        {
            string += "<span>";
            string += "<b>Student: </b>";
            string += xml_arr[i].getElementsByTagName("name")[0].childNodes[0].nodeValue;
            string += "</span><br><br>";
            string += "<span>";
            string += "<b>Datum rodjenja: </b>";
            string += xml_arr[i].getElementsByTagName("age")[0].childNodes[0].nodeValue;
            string += "</span><br><br>";
            string += "<b>Kursevi koje pohadja:</b>";
            string += "<br>";
            
            courses_arr = xml_arr[i].getElementsByTagName("courses")[0].getElementsByTagName("course");
            
            string += "<ol>";
            for (var j = 0; j < courses_arr.length; j++)
            {
                string += "<li>";
                string += courses_arr[j].childNodes[0].nodeValue;
                string += "</li>";
            }
            
            string += "</ol>";
            break;
        }
    }
    
    document.getElementById("right").innerHTML = string;
}