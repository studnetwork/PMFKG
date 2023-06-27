# Eclipse

Pomocu Eclipse Wizard-a se u sekciji `Web` moze izabrati `Dynamic Web Project`

U sledecem prozoru u `Dynamic web module version` proveravamo da li je izabrana
verzija `3.0` posto je ona kompatabilna sa Tomcat servertom koji cemo koristiti.

Ono sto je bitno jeste checkbox na stranici `Web Module` u wizard-u,
`Generate web.xml deployment descriptor`. To ce biti bitno i za ispit i za
naredne termine. U ovom fajlu se nalazi dosta servisnih i drugih informacija
koje mogu da se konfigurisu. Dodje kao konfiguracioni fajl za ceo app.

Tag `<welcome-file>` u `web.xml` definise moguce opcije za ime fajla
koji se servira kada se ode na adresu servera, tj. root `/`. Vrsice se
pretraga po tim nazivima dok se ne nadje neki fajl sa takvim imenom.

Ista ta podesavanja mogu da se vide u lepsem grafickom prikazu u kartici
`Design` koja se nalazi u donjem levom uglu.


U Project Exploreru u folderu `Java Resources/src` dodajemo nase Java klase.


Jedna od praksi pri kreiranju projekata sa servletima je da se za svaki model
pravi poseban servlet.


Servlet moze da se kreira desnim klikom `New > Servlet` preko wizard-a.

Ne biramo odmah `Finish`, vec `Next` jer zelimo neke stvari da izmenimo.

U delu `Create Servlet` check-iramo `doPut` i `doDelete` dodatno.

Projekat nakon kreiranje servleta moza prikazuje da postoji greska, ali
se ipak moze pokrenuti desnim klikom na projekat i biranjem 
`Run As > Run on Server`. Otvara se prozor u kome se bira Tomcat server. 
Moze da se desi da imamo vise servera ili da nemamo Tomcat v9.0 server. 

Ako ga nema mozemo da ga kreiramo.

Na jednom serveru moze biti pokrenuto vise projekata istovremeno pa nas zbog
toga Eclipse wizard pita koje projekte zelimo da pokrenemo.

Moze da se dogodi da imamo vise instanci servera i da koriste isti port pa da je
jedna od njih vec koristi port tako da druga ne moze da se pokrene posto hoce
da koristi isti port.

Ako imamo taj problem ili ukoliko zelimo da promenimo port ili nesto drugo 
to mozemo da uradimo tako sto cemo otici u donji potprozor Eclipse-a u kome
postoji tab `Servers`. U njemu nadjemo odgovarajuci server i duplim klikom
dolazimo do stranice za podesavanje servera. Port menjamo promenom broja 
za `HTTP/1.1` koji po podrazumevano ima vrednost `8080`



Tomcat server moze da se preuzme sa [official stranice](https://tomcat.apache.org/download-90.cgi).


Da bismo to konfigurisali pri pokretanju projekta (u prozoru `Run On Server`)
idemo na `Configure runtime environments` i onda klikom na `Add` biramo
lokaciju na kojoj se nalazi preuzeti server.


Nakon sto smo ovo uradili potrebno je da dodamo ovaj server u build path.
To radimo tako sto desnim klikom na projekat izaberemo 
`Build Path > Configure Build Path`.

U otvorenom prozoru biramo `Modulepath` i dodajemo library preko `Add Library`.
Za tip biramo `Server Runtime` i iz te liste server koji smo upravo dodali.

---

Ako ne koristimo bazu to mozemo da simuliramo `HashMap`-om, npr:
```Java
private HashMap<Integer, Student> studenti = new HashMap<Integer, Student>();
```

---

`Integer.parseInt`

Sve sto je vezano za zahtev korisnika se nalazi u objektu klase `HttpServletRequest`,
a sve za odgovor u objektu klase `HttpServletResponse`

Definisanje tipa dokumenta koji ce biti vracen:
```Java
response.setContentType("text/html;charset=UTF-8");
```

Za dolazak do query parametara koristimo:
```Java
request.getParameter("imeParametra");

// ovo se u stvari koristi jer `getParameter` vraca uvek String
// Integer.parse(request.getParameter("imeParametra")); 
```


Response kreiramo tako sto koristimo `PrintWriter` response-a, tj.
preko `response.getWriter()`.

Sam upis mozemo da vrsimo preko `writer.println("tekst")`

Zbog default-nih podesavanja, na vezbama je putanja bila:
```
localhost:port/ImeProjekta/ImeServleta

// tj. konkretno:

localhost:8082/ServletVezbe/StudentServlet?id=1
```


Da bi servlet prihvatao podatke u body-u (preko POST-a) potrebno je
dodati anotaciju iznad servlet klase: `@MultipartConfig`


Ukoliko je potrebno i definisati neki statusni kod odgovora to mozemo
uciniti sa `response.setStatus(statusniKod)`

---

Korisni metodi `HashMap`-a:
```Java
hashmap.containsKey(id);
hashmap.remove(id);
hashmap.put(id, nesto); // dodaje novu vrednost ili azurira postojecu za dati id
```

Za kreiranje zahteva moze se koristiti [Postman](https://www.postman.com/downloads/).

---

# Intellj

Da bi se ovaj tip projekta kreirao potreban je IDEA Ultimate. Studenti koji su prethodno
aktivirali licencu koja ga ukljucuje mogu da reaktiviraju licencu i preko studentskog
email-a i da tako dobiju ponovo pristup.


Kada se otvori IDEA Intellj biramo JakartaEE ili Maven Archetype.
Za archetype se bira
`org.apache.maven.archetypes:maven-archetype-webapp`

Zavisnosti treba dodati u `pom.xml`. Svi se nalaze u fajlu [`dependencies.txt`](./dependencies.txt)

Za Tomcat:
`Run > Edit Configurations > + > Tomcat Server > local`
