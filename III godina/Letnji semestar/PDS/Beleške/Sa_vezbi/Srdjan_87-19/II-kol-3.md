U radu direktno sa servlet-ima je dosta toga potrebno uraditi manuelno.


# Java Server Pages (JSP)

Mesavina HTML i Jave. Lici na PHP.


Dobra praksa je da se odvojeno pise Java kod i logika servera od
prezentacije, tj. tog HTML dela.

JSP je baziran na servletima. Oni se koriste u pozadini, a 
strane se generisu automatski.


Generisane `web.xml` je bitno zbog redirekcija.
- Eclipse: treba da se check-ira `Generate web.xml deployment descriptor`


`WebContent` paket predstavlja folder u kome ce biti smesteni fajlovi koji
se serviraju korisniku. To je nesto slicno `public` folderu kod javascript 
aplikacija.

(u Intellj je to izgleda `webapp`)

    
U njemu se nalazi `WEB-INF` koji sadrzi folder `lib` i `web.xml`.

Folder `lib` sadrzi `.jar` fajlove. Mi cemo u njega smestiti JDBC konektor.

---

Za stvari koje su potrebne oko konektovanja na bazu kreiramo interfjes `IProvider`.
U njemu definisemo promenljivu za driver (konektor), npr.
`String DRIVER = "com.mysql.jdbc.Driver";`.

Ove podatke nije bas zgodno cuvati u klasama vec je bolje da se nalaze u nekom
delu koji se ne build-uje, kao sto je neki `.xml` fajli. Time ne bi morali ponovo
da kompajliramo celu aplikaciju samo zbog prmene drajvera ili tako nekog podatka
koji bi se nalazio u podesavanjima.


Bolja verzija za kreiranje singltona preko kojeg se vrsi komunikacija ka bazi:
```Java
publci class ConnectionProvider {
    private static Connection connection = null;
    
    // kreira se pri prvom instanciranju ili referenciranju klase, kada se klasa ucitava
    // i nakon toga se vise nikada ne izvrsava
    static { 
        // kreira se klasa sa prosledjenim imenom, tj. koja se nalazi na prosledjenoj putanji
        try {
            Class.forName(IProvider.DRIVER); 
            connection = DriverManager.getConnection(IProvider.CONNECTION_URL);
        } catch(ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }
    
    public static Connection getConnection() {
        return connection;
    }
}
```

DAO - Data Access Object

Preko tog objekta se pristupa podacima

Java Bean standard:
* sva polja trebaju da budu `private`
* default-ni konstruktor mora da postoji
* postoje `public` getter-i i setter-i za definisana polja


Ako u SQL zelimo da unesemo zapis sa svim podacima onda mozemo za id da
postavimo `null` i da ne navodimo nazive kolona:
```SQL
INSERT INTO student (null, "ime1", "prezime1", "00/0000")
```

Obicno se za fajlove koji predstavljaju stranice (`.jsp`) pravi paket
u kome ce se nalaziti, `pages`, i on se nalazi u `WebContent` paketu.


U `.jsp` fajlovima java kod mozemo da pisemo unutar `<%` i `%>` tagova, tj.
```Java
<%
    String s = "Java kod";
    // ...
%>
```


Forma:
```HTML
<form method="post" action="pages/process.jsp">
    username: <input type="text" name="username"> <!-- ovo treba da bude ime tog polja u klasi -->
    <br>
    password: <input type="password" name="password"> <!-- ovo treba da bude ime tog polja u klasi -->
</form>
```


`index.jsp` treba da se nalazi u `WebContent` paketu (`webapp` u Intellj)


Da bi nam klase iz `src` foldera bile dostupne potrebno je da ih importujemo:
```
<%@ page import="putanja.do.naseg.koda.*" %>

// npr. ako je naziv projekta: com.example.demo
// import izgleda ovako:
// <%@ page import="com.example.demo.*" %>
```


U `.jsp` fajlu imamo auto-complete za jsp stvari ukoliko napisemo `<j`.
To je u formatu: `<jsp:nesto`

```
<jsp:useBean id="nazivPromenljive" class="com.example.demo.models.Student"></jsp:useBean>
<jsp:setProperty property="*" name="nazivPromenljive"/>

<%
    iskoristi_mapiran_objekat(nazivPromenljive);
%>
```

U ovom primeru mozemo da vidimo da se preko `useBean` kreira instanca Java Bean-a, tj.
klase cije je ime navedeno u `class`.

Referenca te instance ce se naci u promenljivoj koja je navedena u `id`.

`setProperty` definise koji property-i ce da se mapiraju.

Nakon ovoga mozemo da koristimo taj objekat kao da je neki objekat koji smo kreirali
na standardan nacin.

Primer:
```
<jsp:useBean id="newUser" class="com.example.demo.models.Student"></jsp:useBean>
<jsp:setProperty property="*" name="newUser"/>

<%
    int status = RegisterDAO.register(newUser);
    
    if(status > 0) {
        %>
            <jsp:include page="uspesna_registracija.html"></jsp:include>
        <%
    } else {
        out.print("Error");
    }
%>
```
 
`<jsp:include page="uspesna_registracija.html"></jsp:include>` predstavlja redirekciju na
datu stranicu.

`out.print("Error")` stampa na datoj stranici poruku `Error`



Dodavanje biblioteke (Eclipse):
1. desni klik na naziv projekta
2. `Properties`
3. *Resource* kartica
4. Kliknemo na ikonicu koja predstavlja *browse* u redu za `Location`
5. Paste-ujemo dati lib


## Sesija

```
<h2>Startovanje sesije</h2>
<%
    session.setAttribute("role", "admin");
%>
```

Na drugoj strani:
```

```
<%
    String role = (String) session.getAttribute("role");
    
    if(role != null && role.equals("admin")) {
        %>
            Sadrzaj za administratora
        <%
    } else {
        %>
            Sadrzaj za korisnika
        <%
    }
%>
```
```
