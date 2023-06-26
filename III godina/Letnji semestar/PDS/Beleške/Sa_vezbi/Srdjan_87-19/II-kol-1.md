Stranica phpmyadmin-a:  
`localhost/phpmyadmin`

Default creds:
```
username: "root"
password: ""
```

Pri kreiranju baze izabrati `utf8_general_ci` jer taj format
podrzava case-insensitive Unicode


Tabela se najcesce naziva tako sto je naziv u nominativu
jednine, npr. `student`.

Pridevinisanju tabele, ako ona ima id mi mozemo da check-iramo
`A_I` i da time nad tom kolonom definisemo auto-increment.

Za tekstualne pdoatke mozemo da definisemo kolone tipa 
`VARCHAR` duzine `255`


Pri kreiranju java projekta nije potrebno kreirati modul.

Da bi smo dodali potrebne biblioteke (jdbc) kreiramo folder
`libs` (ne mora tako da se zove) i desnim klikom na njega
otvaramo meni u kome biramo `Properties`. U `Resource` 
kliknemo na ikonicu u `Location` delu i u tom otvorenom
folderu prekopiramo dati `.jar` fajl.

Nakon sto se osvezi `Project Explorer` Eclipse-a doci ce
do pojavljivanja fajla koji smo dodali.

Ono sto je neophodno pored dodavanja biblioteke jeste to 
da se ona ukljuci u build-ovani fajl. 

To postizemo tako sto desnim klikom na taj `.jar` fajl
izaberemo `Build Path > Add to Build Path`

Ono sto je moguce je da se napravi referenca na neku zavisnost
koja ne postoji (npr. referencu na `libs/x.jar` iako
taj fajl ne postoji. To moze da predstavlja problem jer
iako taj fajl postoji kod nas on mozda ne postoji kod nekoga
drugog na njegovom racunaru.

---

Mi dodavanje biblioteke radimo za mysql konektor u javi.
On predstavlja interfejs prema bazi. 

Ono sto je prednost toga je sto mozemo konektor da promenimo
i time promenimo bazu sa kojom radimo, a da sve ostalo (tj.
kod) ostane isto.

Izbegavati nazivanje paketa u javi sa `Test` jer moze doci
do problema u nazivanju.

---

Za komunikaciju za bazom definisemo paket `DataAccessLayer`


Za pristup bazi kreiramo klasu `Database.java`

Za rad sa jednom tabelom kreiramo interface `INazivAccess.java` i
u njemu deklarisemo CRUD metode.


Klase koje ce biti mapirane u bazu trebaju da budu
Java bean. Da bi to bile one moraju da imaju no-arg
konstruktor i da definisu propertije za svako polje.

Java bean-ovi se koriste kod ORM-a (Object-relational mapping).


Pri generisanju `toString` treba obratiti paznju na to da moze doci do
stack overflow-a zbog toga sto neko od polja mozda sadrzi objekat
druge klase koja u svom polju sadrzi objekat klase za koju pravimo
`toString`. Jednostavnije receno, imaju jedna drugu pa onda pri ispisu
beskonacno se pozivaju naizmenicno dok ne dodje do stack overflow-a.

`List<ImeKlase> lista`

Klasa `Database` implementira sve interfejse tabela sa kojima zelimo
da radimo.



Konekciju sa bazom ostvarujemo u konstruktoru `Database` klase.

```Java
Connection connection; // iz java.sql.Connection;
public Database() {
    String connectionString = "jdbc:mysql://adresa_baze/ime_baze?user=neki_user&password=neki_pw";
    
    try {
        connection = DriverManager.getConnection(connectionString);
    } catch(SQLException e) {
        e.printStackTrace();
    }
}
```

`adresa_baze` je u slucaju lokalne mysql baze kreirane preko 
WAMP-a (ili LAMP-a): `localhost:3306`

To mozemo i da vidimo na vrhu stranice: `localhost/phpmyadmin`


Konekcioni string nije dobro definisati ovako jer je ukljucen u proces kompajliranja. Ako ga 
promenimo morali bismo ponovo da kompajliramo ceo program. Obicno se definise u nekom
eksternom fajlu koji je "human-readable" (npr. `.xml` ili `.json`).


Kada dodje do nekog problema u komunikaciji sa bazom baca se `SQLException`

Kreiranje vise konekcija za istu bazou u jednoj aplikaciji nije pozeljno jer se time usporava
aplikacija. Zbog toga se klasa definise kao singlton.

Tada bi nas kod izgledao ovako:
```Java
public class Database implements IStudentAccess {
    Connection connection;
    
    static Database instance = null;
    
    private Database() {
        String connectionString = "jdbc:mysql://localhost:3306/studije_vezbe?user=root&password=";
        
        try {
            connection = DriverManager.getConnection(connectionString);
        } catch(SQLException e) {
            e.printStackTrace();
        }
    }
    
    public static Database getInstance() {
        if(instance == null)
            instance = new Database();
        
        return instance;
    }
}
```


Nakon ovoga mozemo da implementiramo metode za rad sa nekom tabelom, npr:
```Java
public Boolean addStudent(Student s) {
    String sql = "INSERT INTO student(indeks, upisan, ime, mesto)"
        + " VALUES(" + s.getIndeks() + ", "  // NAPOMENA: ovde se cesto zaboravi razmak izmedju `)` i `VALUES`
        + s.getUpisan() + ", '" // NAPOMENA: primetiti `'`; to radimo zato sto je sledece polje string
        + s.getIme() + "', '" 
        + s.getMesto() + "')";
    
    try {
        Statement statement = connection.createStatement();  // iz java.sql paketa
        statement.executeUpdate(sql);
        
        return true; // ukoliko nije doslo do greske
    } catch(SQLException e) {
        e.printStackTrace();
    }

    return false; // ukoliko je doslo do greske
}
```

`statement.executeUpdate(sql);` se ne koristi samo kada se menja jedan red, vec kada se menja
stanje cele baze. To znaci da se koristi i u `UPDATE` i `DELETE` naredbama.
(?)


Kada prosledjujemo parametre u upitu nije pogodno koristiti ovaj metod jer opisani nacin
moze dovesti do SQL Injection napada.

Zbog toga koristimo `PreparedStatement`. U njemu postoje "joker"-i koji se zamenjuju sa
nekim parametrom i oznacenu su sa `?`.

Primer:
```Java
String sql = "UPDATE student set mesto=? WHERE id=?";

try {
    PreparedStatement prepStat = connection.prepareStatement(sql);

    prepStat.setInt(2, s.getIndeks());
    prepStat.setString(1, s.getMesto());

    prepStat.executeUpdate();
} catch(SQLException e) {
    e.printStackTrace();
}
```

`executeUpdate` vraca broj promenjenih redova


Kada citamo podatke ne mozemo rezultat da preuzmemo kao tabelu. Ono sto predstavlja
tabelu, tj. redove tabele je u Javi `ResultSet`.

Za citanje se koristi metod `executeQuery` (nad `PreparedStatement`).


`ResultSet` ima iterator. Sa metodom `resultset.next()` prelazimo na sledeci red. U pocetku se
kursor nalazi na redu `-1`, tacnije nalazi se iza/pre prvo reda i onda pozivom metoda `next` 
dolazi se na prvi red. Kada postavimo kursor na odgovarajucu poziciju onda se nalazimo
na nekom redu i mozemo da uzimamo vrednosti njegovih kolona direktno preko objekta `resultset`
putem metoda kao sto je npr. `resultset.getInt("imeKoloneUBazi")`;

Moze se dogoditi da string kolone (atributi) ne ispunjavaju ceo string koji je definisan u bazi
(npr. podeseno je da je string duzine od `255` karaktera) pa da time dobijemo praznine na 
njegovom kraju. To mozemo da resimo sa metodom `trim`, npr. `resultset.getString("nekoIme").trim()`

Kada nema parametra u sql-u mozemo da koristimo obican `Statement` kako bi brze radila aplikacija jer 
nam u tom slucaju ne treba `PreparedStatement`
