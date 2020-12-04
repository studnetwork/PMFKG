# Tipovi zadatka
U ovom fajlu se nalaze primeri specifičnih tipova zadataka i opis ideje za njihovo rešavanje
## Prvi kolokvijum

### Odrediti *jedinstveni* i *najveći(najmanji)*
**Primer:** Najveće jedinstvene ponude za svaki oglas (**idOglasa**, **ponudjenaCena**)  
( Baze podataka 1 - prvi kolokvijum - 09.12.2019. )

**Relacioni model:**  
_**tip_vozila (idTipaVozila, naziv)**_ - Spisak svih tipova vozila.  
_**marka_vozila (idMarkeVozila, naziv)**_ - Spisak svih marki vozila.  
_**modeli_vozila (idModela, idTipaVozila, idMarkeVozila, nazivModela)**_ - Spisak svih modela vozila.</br>
_**osobe (idOsobe, ime)**_ - Spisak svih osoba koje mogu biti vlasnici ili kupci vozila.  
_**vozila(idVozila, idModela, kubikaža, snag, tipGoriva, godinaProizvodnje, idVlasnika)**_ - Spisak svih proizvedenih vozila.  
_**oglasi(idOglasa, idVozila, datumPostavljanja, datumZavršetka, početnaCena)**_ - Spisak svih vozila koja se prodaju. Oglas je aktivan u periodu 
[datumPostavljanja - datumZavršetka].  
_**ponude(idPonude, idOglasa, datumPonude, ponuđenaCena, idPonuđača)**_ - Spisak svih ponuda za vozila.   


**Rešavanje:**  
*Jedinstvenost redova* možemo dobiti tako što izbacimo redove koji imaju iste vrednost za posmatrani atribut. To je moguće postići korišćenjem Left/Right Join-a.
Vrši se spajanje tabele sa samom sobom, npr. `t1 LEFT-JOIN t2`. Cilj je da se povežu redovi koji predstavljaju duplikate i da redovi koji su jedinstveni ostanu
nepovezani. Nakon toga je potrebno izdvojiti redove koji imaju jedinstvene vrednost za posmatrani atribut. To činimo selekcijom redova po uslovu da neka od kolona
koja leve/desne tabele ima nedefinisanu vrednost, `t2.kol1 is NULL`.

Određivanje reda sa *najvećom(najmanjom) vrednošću* se vrši korišćenjem Left/Right Join. Spajamo tabelu sa samom sobom (en. *Self Join*). Cilj je kao i kod ostalih 
upotreba Left/Right Join-a, da se spoje redovi koji nam nisu potrebni, tako da se traženi redovi ne spoje ni sa jednim redom, što će kao posledicu imati da kolone 
koje nisu na strani po kojoj dati Join nosi ime budu ispunjene sa `NULL` za date redove. To postižemo ispitivanjem da li je data vrednost posmatranog atributa jedne
tabele *manja* od vrednost tog atributa druge tabele, u slučaju kada se traži najveća vrednost, odnosno, *veća* u slučaju kada se traži najmanja vrednost. Razlog za
to je taj što najveća vrednost nema osobinu da je manja od sebe ili od ostalih elemenata, anologno se može zaključiti i za najmanju vrednost. **Lakši način za pamćenje
ove osobine je da je znak uvek suprotan od onoga što se traži, ako se traži najveća vrednost, znak je `<`, ukoliko se traži najmanja, znak je `>`**.
