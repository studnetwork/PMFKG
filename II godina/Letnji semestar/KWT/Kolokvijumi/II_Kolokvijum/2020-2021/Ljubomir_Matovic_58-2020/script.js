document.body.onload=function(){
    let xmlhttp;
    if(window.XMLHttpRequest)
        xmlhttp=new XMLHttpRequest();
    else xmlhttp=ActiveXObject("MICROSOFT.XMLHTTP");
    xmlhttp.open("GET","Cereals.xml");
    xmlhttp.onreadystatechange=function(){
        if(xmlhttp.readyState==4 && xmlhttp.status==200){
            let xml=xmlhttp.responseXML.getElementsByTagName("Cereal");
            //mapira xml u niz objekata
            for(let i=0;i<xml.length;i++){
                let value=xml[i];
                let o={};
                o.name=value.getElementsByTagName("Name")[0].textContent;
                o.manufacturer=value.getElementsByTagName("Manufacturer")[0].textContent;
                o.calories=parseInt(value.getElementsByTagName("Calories")[0].textContent);
                o.price=parseFloat(value.getElementsByTagName("Price")[0].textContent);
                o.index=i;
                o.checked=false;
                cereals.push(o);
            }
            let man=document.getElementById("proizvodjaci");
            man.innerHTML="";
            let sadrzaj=`<option value="svi">Svi</option>`;
            let nov=[];
            for(let i=0;i<cereals.length;i++){
                let b=true;
                for(let j=i+1;j<cereals.length;j++){
                    if(cereals[i].manufacturer==cereals[j].manufacturer)
                    {
                        b=false;
                        break;
                    }
                }
                if(b)
                nov.push(cereals[i].manufacturer);
            }
            nov.sort();
            nov.forEach(v=>sadrzaj+=`<option value=${v}>${v}</option>`);
            man.innerHTML=sadrzaj;

            cereals=cereals.filter((value)=>{
                if(/^[0-9].*/.test(value.name))
                    return false;
                return true;
            });
            for(let i=0;i<cereals.length;i++){
                cereals[i].index=i;
            }
            popuniTabelu(()=>true);
        }
    }
    xmlhttp.send();
};
var cereals=[];
var proizvodjaci=[];
var kupljeno=[];
function filterTabele(value,index){
    let ime=document.getElementById("search").value;
    //filter ime
    let re=new RegExp(ime,"g");
    if(!re.test(value.name) && ime!="")
        return false;

    //filter proizvodjac
    let proizvodjac=document.getElementById("proizvodjaci").value;
    //console.log(proizvodjac);
    if(value.manufacturer!=proizvodjac && proizvodjac!="svi")
        return false;
    let chkMore=document.getElementById("vece_kalorije");
    let chkLess=document.getElementById("manje_kalorije");
    if((chkMore.checked && !chkLess.checked && value.calories<=100) || (!chkMore.checked && chkLess.checked && value.calories>100))
        return false;
    return true;
}
function popuniTabelu(filter){
    let tabela=document.getElementById("proizvodi");
    tabela.innerHTML="";
    let sadrzaj="";
    let content=cereals.filter(filter);
    for(let c of content){
        sadrzaj+=`<tr>
            <td>${c.name}</td>
            <td>${c.manufacturer}</td>
            <td>${c.calories}</td>
            <td>${c.price}</td>
            <td><input type="checkbox" data-index="${c.index}" onchange="obaviKupovinu(event)" ${(c.checked)? "checked":""}></td>
        </tr>`;
    }
    tabela.innerHTML=sadrzaj;
}
function obaviKupovinu(event){
    let index=event.target.dataset.index;
    if(event.target.checked){
        kupljeno.push(cereals[index]);
        cereals[index].checked=true;
    }else {
        kupljeno=kupljeno.filter(v=>v.index!=index);
        console.log(kupljeno);
        cereals[index].checked=false;
    }
    let cena=document.getElementById("cena");
    let porudzbine=document.getElementById("porudzbine");
    porudzbine.innerHTML="";
    if(kupljeno.length==0){
        document.getElementById("prazno_text").style.display="inline";
        cena.innerHTML="";
        return;
    }else{
        document.getElementById("prazno_text").style.display="none";
    }
    let sadrzaj="";
    
    let suma=0;
    for(let k of kupljeno){
        sadrzaj+=`<tr>
        <td>${k.name}</td>
        </tr>
        `;
        suma+=k.price;
    }
    porudzbine.innerHTML=sadrzaj;
    cena.innerHTML=suma;
}
