/* -------- Login -------- */
let login = document.getElementById('login');
let logout = document.getElementById('logout');
let inpUser = document.getElementById('inpUser');
let inpPass = document.getElementById('inpPass');

document.getElementById('logujSe').onclick = logovanje;
document.getElementById('izlogujSe').onclick = izlogovanje;
document.getElementById('selCena').onchange = updatePrikaz;
       
function logovanje() {
    let regUser = /^[a-z][a-z0-9]{4,14}$/;
    let regPass = /^[a-z0-9]{8,}$/;
    
    if(inpUser.value.match(regUser) && inpPass.value.match(regPass)) {
        document.getElementById('greska').hidden = true;
        login.hidden = true;
        logout.hidden = false;
        
        document.getElementById('welcomeUser').innerHTML = inpUser.value;
    }
    else {
        document.getElementById('greska').hidden = false;
    }
}

function izlogovanje() {
    login.hidden = false;
    logout.hidden = true;
}

/* -------- XML -------- */
let tab = document.getElementById('tabela');
let det = document.getElementById('detalji');
let xml;
let cbs = {};
let books = [];
let allBooks = [];

/* Main */
document.body.onload = loadXML;

function createZanr() {
    // Imena zanrova
    let genreNames = xml.getElementsByTagName('genre_name');
    let t = '';
    for(let i = 0; i < genreNames.length; i++) {
        let name = genreNames[i].textContent;
        t += '<input type="checkbox" onchange="updatePrikaz()" id="cbZanr'+name+'" checked>' + name + '<br>';
        cbs[name] = true;
    }
    document.getElementById('checkboxes').innerHTML = t;
    
    updatePrikaz();
}

function updateZanr() {
    let f = false;
    for (let key in cbs) {
        //console.log(key);
        cbs[key] = document.getElementById('cbZanr'+key).checked;
        f = f || cbs[key];
    }
    
    if(!f) {
        for (let key in cbs) {
            cbs[key] = true;
        }
    }
}

function updatePrikaz() {
    updateZanr();
    
    // Knjige
    books = [];
    allBooks = [];
    let genres = xml.getElementsByTagName('genre');
    let t = '<table><tr><th>Author</th><th>Title</th></tr>'
    let bn = 0;
    for(let i = 0; i < genres.length; i++) {
        let gName = genres[i].getElementsByTagName('genre_name')[0].textContent; 
        let bks = genres[i].getElementsByTagName('book');
        for(let j = 0; j < bks.length; j++) {
            let cen = parseInt(document.getElementById('selCena').value);
            let bkCen = parseInt(bks[j].getElementsByTagName('price')[0].textContent);
            
            allBooks.push({
                id: bks[j].attributes.id,
                author: bks[j].getElementsByTagName('author')[0].textContent,
                title: bks[j].getElementsByTagName('title')[0].textContent,
                genre: gName,
                price: bks[j].getElementsByTagName('price')[0].textContent,
                publishDate: bks[j].getElementsByTagName('publish_date')[0].textContent,
                cover: bks[j].getElementsByTagName('cover')[0].textContent,
                description: bks[j].getElementsByTagName('description')[0].textContent
            });
            
            if(!cbs[gName] || cen < bkCen)
                continue;
            
            books[bn] = allBooks[allBooks.length-1];
            
            t += '<tr>'+
                    '<td>'+ books[bn].author +'</td>' +
                    '<td>'+ books[bn].title +'</td>' +
                    '<td><button onclick="detaljnije(this)" bookId="'+bn+'">Detaljnije</button></td>' +
                '</tr>';
        
            bn++;
            //console.log(books);
        }
    }
    
    t += '</table>';
    tab.innerHTML = t;
    //console.log(t);
}

function detaljnije(btn)
{
    let book = books[btn.getAttribute('bookId')];
    let t = '';
    
    let auth = book.author.split(', ');
    auth = auth[1]+' '+auth[0];
    
    let dat = book.publishDate.split('-');
    dat = dat[2]+'.'+dat[1]+'.'+dat[0]+'.';
    
    t += '<img id="detailsImage" src="images/'+book.cover+'">'; // Cover
    t += '<div id="detailsTitle">'+book.title+'</div>'; // Title
    t += '<div id="detailsAuthor"><span>by </span>'+auth+'</div>'; // Author
    t += '<div class="detTag" id="detailsGenre"><span>Zanr: </span>'+book.genre+'</div>'; // Genre
    t += '<div class="detTag" id="detailsPrice"><span>Cena: </span>'+book.price+'</div>'; // Price
    t += '<div class="detTag" id="detailsDate"><span>Datum: </span>'+dat+'</div>'; // Date
    t += '<div class="detTag" id="detailsDescription"><span>Opis: </span>'+book.description+'</div>'; // Description
    
    let b = false;
    for (let i = 0; i < allBooks.length; i++) {
        if(allBooks[i].genre == book.genre && allBooks[i].title != book.title) {
            b = true;
            break;
        }
    }
    if(b) {
        t += '<div id="prep">Preporuceno:</div>';
        t += '<ul>';
        for (let i = 0; i < allBooks.length; i++) {
            if(allBooks[i].genre != book.genre || allBooks[i].title == book.title)
                continue;
            t += '<li>'+allBooks[i].title+'</li>';
        }
        t += '</ul>';
    }
    document.getElementById('detalji').innerHTML = t;
    
}

function tagINPUT(type){
    return '<input type="'+type+'">'
}

function loadXML(){
    let xh = new XMLHttpRequest();
    xh.onreadystatechange = function () {
        if(xh.readyState === 4 && xh.status === 200) {
            xml = xh.responseXML;
            createZanr();
            console.log(xml.getElementById('bk101').attributes);
        }
        
    }
    
    xh.open('GET', 'books.xml', true);
    xh.send();
}