var oglasi=[];
var autori=[];
document.body.onload=function(){
    document.getElementById("logout").style.display="none";
    document.getElementById("prikaz").style.display="none";
    let xmlhttp=new XMLHttpRequest();
    xmlhttp.open("GET","imi.xml");
    xmlhttp.onreadystatechange=function(){
        if(xmlhttp.readyState==4 && xmlhttp.status==200){
            let xml=xmlhttp.responseXML;
            let sviAutori=xml.getElementsByTagName("author");
            autori.push(sviAutori[0].textContent);
            for(let i=1;i<sviAutori.length;i++){
                if(autori.indexOf(sviAutori[i].textContent)==-1){
                    autori.push(sviAutori[i].textContent);
                }
            }
            let selectAutori=document.getElementById("selectAuthor");
            selectAutori.innerHTML="";
            let sadrzaj="";//`<option value="Svi">Svi</option>`;
            for(let autor of autori){
                sadrzaj+=`<option value="${autor}">${autor}</option>`;
            }
            selectAutori.innerHTML=sadrzaj;
            let sviOglasi=xml.getElementsByTagName("item");
            for(let i=0;i<sviOglasi.length;i++){
                let oglas=sviOglasi[i];
                let o={};
                o.title=oglas.getElementsByTagName("title")[0].textContent;
                o.link=oglas.getElementsByTagName("link")[0].textContent;
                o.autori=[];
                let mojiAutori=oglas.getElementsByTagName("author");
                for(let i=0;i<mojiAutori.length;i++){
                    let autor=mojiAutori[i];
                    o.autori.push(autor.textContent);
                }
                o.datum=oglas.getElementsByTagName("pubDate")[0].textContent;
                o.index=i;
                oglasi.push(o);
            }
            popuniTabelu();
        }
    };
    xmlhttp.send();
};
function filterTabele(value,index){
    let selectAuthor=document.getElementById("selectAuthor");
    let search=document.getElementById("txtSearch");
    let re=new RegExp(search.value,"ig");
    if(!value.autori.includes(selectAuthor.value))
        return false;
    if(!re.test(value.title) && search.value!="" && search.value!=undefined)
        return false;
    return true;
}
function prikaziOglas(index){
    let oglas=oglasi[index];
    let target=document.getElementById("oglasi");
    let sadrzaj=`<p><b>Title:</b> ${oglas.title}</p>
    <b>Link do oglasa: </b><a href="${oglas.link}" target="_blank">Link</a><br>
    <b>Datum objavljivanja: </b>${oglas.datum}<br>
    <b>Autori:</b><br>
    <ol>
    `;
    for(let autor of oglas.autori){
        sadrzaj+=`<li>${autor}</li>`;
    }
    sadrzaj+="</ol>";
    target.innerHTML=sadrzaj;

}
function popuniTabelu(){
    let tabela=document.getElementById("tabela");
    tabela.innerHTML="";
    let s=`<table><tr> <th>Title</th> <th>Date</th> <th>Authors</th></tr>`;
    let oglasiKopija=oglasi.filter(filterTabele);
    document.getElementById("broj").innerHTML="Broj oglasa: "+oglasiKopija.length;
    for(let oglas of oglasiKopija){
        s+=`<tr onclick="prikaziOglas(${oglas.index})">
            <td>${oglas.title}</td>
            <td>${oglas.datum}</td>
            <td>${(oglas.autori!=undefined && oglas.autori!=null)? oglas.autori.join(", "):""}</td>
            </tr>`;
    }
    s+="</table>";
    tabela.innerHTML=s;
}
document.getElementById("logujSe").onclick=function(){
    let inputUser=document.getElementById("inpUser");
    let inputPassword=document.getElementById("inpPass");
    let greska=document.getElementById("porukaGreske");
    if(/[a-z]{3,15}\.[a-z]{3,15}[0-9]*/.test(inputUser.value) && /[a-z0-9\-_\.]{6,}/.test(inputPassword.value)){
        document.getElementById("logout").style.display="block";
        document.getElementById("prikaz").style.display="block";
        document.getElementById("login").style.display="none";
        greska.innerHTML="";
        //inputUser.value="";
        //inputPassword.value="";
    }else{
        greska.innerHTML="GRESKA!";
        greska.style.color="red";
    }
};
document.getElementById("logout").onclick=function(){
    document.getElementById("logout").style.display="none";
    document.getElementById("prikaz").style.display="none";
    document.getElementById("login").style.display="block";
};