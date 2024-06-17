from experta import *
import schema 
import re

class Film(Fact):
    naziv = Field(str)
    reziser = Field(str)
    kategorija = Field(schema.Or("AKCIJA", "DRAMA", "HOROR", "TRILER", "NAUCNA_FANTASTIKA", "KOMEDIJA"))
    opis = Field(str)
    datum_premijere = Field(lambda x: isinstance(x, str) and re.match(r"^[0-9]{4}-[0-9]{2}-[0-9]{2}$", x))
    glavna_uloga = Field(str)
    sporedne_uloge = Field(list)
    preporuka = Field(float, default=50.0)

    nema_nagradu = Field(bool, default=False)
    ista_kategorija = Field(bool, default=False)
    ima_omiljenog_glumca = Field(bool, default=False)
    nema_omiljenog_glumca = Field(bool, default=False)
    uracunata_prosecna = Field(bool, default=False)

    broj_ocena = Field(int, default=0)
    suma_ocena = Field(int, default=0)
    prosecna_ocena = Field(float, default=0)
    dobijena_prosecna = Field(bool, default=False)

    rang = Field(int, default=0)
    ispisan_film = Field(bool, default=False)
    predji_na_sledeci = Field(bool, default=False)

class Recenzija(Fact):
    recezent = Field(str)
    naziv_filma = Field(str)
    tekst_recenzije = Field(str)
    ocena = Field(lambda x: isinstance(x, int) and (0 <= x <= 10))

    uracunata = Field(bool, default=False)
    uracunata_prijatelj = Field(bool, default=False)
    ispisana_recenzija = Field(bool, default=False)

class FilmskaNagrada(Fact):
    naziv_filma = Field(str)
    nagrada = Field(schema.Or("ZLATNA_PALMA", "OSKAR", "ZLATNI_LAV"))

class Prijatelj(Fact):
    osoba_1 = Field(str)
    osoba_2 = Field(str)

class Korisnik(Fact):
    omiljeni_film = Field(str)
    omiljena_kategorije = Field(schema.Or("AKCIJA", "DRAMA", "HOROR", "TRILER", "NAUCNA_FANTASTIKA", "KOMEDIJA"))
    omiljeni_glumac = Field(str)
    ime = Field(str)

    postoji_film_recenzija = Field(bool, default=False)

class Engine(KnowledgeEngine):
    @DefFacts()
    def ucitaj_aksiome(self):
        yield Fact(faza="1")
        yield Fact(brojac=0)
        yield Fact(ispisani_filmovi=0)

        yield Film(naziv="Film A", reziser="Reziser A", kategorija="AKCIJA", opis="Opis filma A", datum_premijere="2023-10-11", glavna_uloga="Glumac A", sporedne_uloge=["Glumac B", "Glumac C"])
        yield Film(naziv="Film B", reziser="Reziser B", kategorija="DRAMA", opis="Opis filma B", datum_premijere="1995-10-12", glavna_uloga="Glumac B", sporedne_uloge=["Glumac A", "Glumac E"])
        yield Film(naziv="Film C", reziser="Reziser C", kategorija="HOROR", opis="Opis filma C", datum_premijere="2005-10-13", glavna_uloga="Glumac A", sporedne_uloge=["Glumac B", "Glumac C", "Glumac E"])
        yield Film(naziv="Film D", reziser="Reziser D", kategorija="TRILER", opis="Opis filma D", datum_premijere="2022-10-14", glavna_uloga="Glumac B", sporedne_uloge=["Glumac C", "Glumac E"])
        yield Film(naziv="Film E", reziser="Reziser B", kategorija="NAUCNA_FANTASTIKA", opis="Opis filma E", datum_premijere="2023-10-15", glavna_uloga="Glumac C", sporedne_uloge=["Glumac A", "Glumac B"])
        yield Film(naziv="Film F", reziser="Reziser C", kategorija="KOMEDIJA", opis="Opis filma F", datum_premijere="2021-10-12", glavna_uloga="Glumac D", sporedne_uloge=["Glumac C", "Glumac E"])
        yield Film(naziv="Film G", reziser="Reziser A", kategorija="AKCIJA", opis="Opis filma G", datum_premijere="2022-10-13", glavna_uloga="Glumac E", sporedne_uloge=["Glumac A", "Glumac C"])
        yield Film(naziv="Film H", reziser="Reziser A", kategorija="DRAMA", opis="Opis filma H", datum_premijere="2022-10-11", glavna_uloga="Glumac E", sporedne_uloge=["Glumac B", "Glumac C"])
        yield Film(naziv="Film I", reziser="Reziser C", kategorija="AKCIJA", opis="Opis filma I", datum_premijere="2022-10-24", glavna_uloga="Glumac A", sporedne_uloge=["Glumac E", "Glumac D"])

        yield Recenzija(recezent="Recezent A", naziv_filma="Film A", tekst_recenzije="Recenzija filma A od strane recezenta A...", ocena=8)
        yield Recenzija(recezent="Recezent B", naziv_filma="Film A", tekst_recenzije="Recenzija filma A od strane recezenta B...", ocena=8)
        yield Recenzija(recezent="Recezent C", naziv_filma="Film B", tekst_recenzije="Recenzija filma B od strane recezenta C...", ocena=8)
        yield Recenzija(recezent="Recezent D", naziv_filma="Film B", tekst_recenzije="Recenzija filma B od strane recezenta D...", ocena=6)
        yield Recenzija(recezent="Recezent E", naziv_filma="Film C", tekst_recenzije="Recenzija filma C od strane recezenta E...", ocena=8)
        yield Recenzija(recezent="Recezent A", naziv_filma="Film C", tekst_recenzije="Recenzija filma C od strane recezenta A...", ocena=4)
        yield Recenzija(recezent="Recezent B", naziv_filma="Film D", tekst_recenzije="Recenzija filma D od strane recezenta B...", ocena=2)
        yield Recenzija(recezent="Recezent C", naziv_filma="Film D", tekst_recenzije="Recenzija filma D od strane recezenta C...", ocena=3)
        yield Recenzija(recezent="Recezent D", naziv_filma="Film E", tekst_recenzije="Recenzija filma E od strane recezenta D...", ocena=9)
        yield Recenzija(recezent="Recezent E", naziv_filma="Film E", tekst_recenzije="Recenzija filma E od strane recezenta E...", ocena=6)
        yield Recenzija(recezent="Recezent A", naziv_filma="Film F", tekst_recenzije="Recenzija filma F od strane recezenta A...", ocena=3)
        yield Recenzija(recezent="Recezent B", naziv_filma="Film F", tekst_recenzije="Recenzija filma F od strane recezenta B...", ocena=8)
        yield Recenzija(recezent="Recezent C", naziv_filma="Film G", tekst_recenzije="Recenzija filma G od strane recezenta C...", ocena=10)
        yield Recenzija(recezent="Recezent D", naziv_filma="Film G", tekst_recenzije="Recenzija filma G od strane recezenta D...", ocena=10)
        yield Recenzija(recezent="Recezent E", naziv_filma="Film H", tekst_recenzije="Recenzija filma H od strane recezenta E...", ocena=6)
        yield Recenzija(recezent="Recezent C", naziv_filma="Film H", tekst_recenzije="Recenzija filma H od strane recezenta C...", ocena=9)
        yield Recenzija(recezent="Recezent A", naziv_filma="Film I", tekst_recenzije="Recenzija filma I od strane recezenta A...", ocena=10)
        yield Recenzija(recezent="Recezent B", naziv_filma="Film I", tekst_recenzije="Recenzija filma I od strane recezenta B...", ocena=6)

        yield Prijatelj(osoba_1="Korisnik A", osoba_2="Recezent B")
        yield Prijatelj(osoba_1="Recezent C", osoba_2="Korisnik A")

        yield FilmskaNagrada(naziv_filma="Film A", nagrada="ZLATNA_PALMA")
        yield FilmskaNagrada(naziv_filma="Film A", nagrada="OSKAR")
        yield FilmskaNagrada(naziv_filma="Film B", nagrada="ZLATNI_LAV")
        yield FilmskaNagrada(naziv_filma="Film C", nagrada="ZLATNI_LAV")
        yield FilmskaNagrada(naziv_filma="Film D", nagrada="ZLATNI_LAV")
        yield FilmskaNagrada(naziv_filma="Film E", nagrada="ZLATNI_LAV")
        yield FilmskaNagrada(naziv_filma="Film F", nagrada="ZLATNI_LAV")
        yield FilmskaNagrada(naziv_filma="Film G", nagrada="ZLATNI_LAV")
        yield FilmskaNagrada(naziv_filma="Film H", nagrada="ZLATNI_LAV")
        yield FilmskaNagrada(naziv_filma="Film I", nagrada="ZLATNI_LAV")

        # Ovo se moze odkomentarisati, radi lakseg debuga

        # yield Korisnik(ime="Korisnik A", omiljeni_film="Film A", omiljena_kategorija="AKCIJA", omiljeni_glumac="Glumac A")

    # На старту програма корисник треба да унесе податке о:
    #     • називу омиљеног филма,
    #     • омиљене категорије,
    #     • име омиљеног глумца,
    #     • као и своје име.

    @Rule(
        Fact(faza="1"),
        NOT(Korisnik())
    )
    def ucitaj_korisnika(self):
        omiljeni_film = input("Unesi svoj omiljeni film: ")
        omiljena_kategorija = input("Unesi svoju omiljenu kategoriju: ")
        omiljeni_glumac = input("Unesi svog omiljenog glumca: ")
        ime = input("Unesi svoje ime: ")

        self.declare(Korisnik(ime=ime, omiljeni_film=omiljeni_film, omiljena_kategorija=omiljena_kategorija, omiljeni_glumac=omiljeni_glumac))


    # Уколико постоји запис о омиљеном филму и барем једна рецензија за омиљени филм 
    # корисник добија информацију да је одабрани филм оцењен

    @Rule(
        Fact(faza="1"),
        AS.korisnik << Korisnik(omiljeni_film=MATCH.film, postoji_film_recenzija=False),
        AND(
            Film(naziv=MATCH.film),
            Recenzija(naziv_filma=MATCH.film)
        )
    )
    def nastavi_sa_radom(self, korisnik):
        print("Omiljeni film je ocenjen!")
        self.modify(korisnik, postoji_film_recenzija=True)

    # у супротном програм завршава са радом.

    @Rule(
        Fact(faza="1"),
        Korisnik(omiljeni_film=MATCH.film),
        OR(
            NOT(Film(naziv=MATCH.film)),
            NOT(Recenzija(naziv_filma=MATCH.film))
        )
    )
    def prekini_sa_radom(self):
        print("Ne postoji ili zapis o omiljenom filmu ili njegova recenzija, prekidam sa radom!")
        exit()

    @Rule(
        AS.faza << Fact(faza="1"),
        salience=-10
    )
    def faza_1_u_2(self, faza):
        self.modify(faza, faza="2")

    # У наредном кораку уклонити све филмове који су се појавили пре 2022. године,

    @Rule(
        Fact(faza="2"),
        AS.film << Film(datum_premijere=MATCH.datum),
        TEST(lambda datum: int(datum.split("-")[0]) < 2022)
    )
    def obrisi_stare_filmove(self, film):
        self.retract(film)

    @Rule(
        AS.faza << Fact(faza="2"),
        salience=-10
    )
    def faza_2_u_3(self, faza):
        self.modify(faza, faza="3")

    # а потом проверити да ли сваки од преосталих филмова има филмску награду, уколико је тако корисник добија поруку да сви филмови награђени.

    @Rule(
        Fact(faza="3"),
        FORALL(
            Film(naziv=MATCH.film),
            FilmskaNagrada(naziv_filma=MATCH.film)
        )
    )
    def svi_imaju_nagrade(self):
        print("Svi preostali filmovi su nagradjeni!")

    @Rule(
        AS.faza << Fact(faza="3"),
        salience=-10
    )
    def faza_3_u_4(self, faza):
        self.modify(faza, faza="4")

    # Филмовима који немају ни једну филмску награду препорука се умањује за 15.

    @Rule(
        Fact(faza="4"),
        AS.film << Film(naziv=MATCH.naziv, preporuka=MATCH.preporuka, nema_nagradu=False),
        NOT(FilmskaNagrada(naziv_filma=MATCH.naziv))
    )
    def skini_zbog_nagrade(self, film, preporuka):
        self.modify(film, preporuka=preporuka-15.0, nema_nagradu=True)
    
    # Филмовима који припадају истој категорији као и омиљени филм увећати препоруку за 10.

    @Rule(
        Fact(faza="4"),
        Korisnik(omiljeni_film=MATCH.naziv),
        Film(naziv=MATCH.naziv, kategorija=MATCH.kategorija),
        AS.film << Film(naziv=~MATCH.naziv, kategorija=MATCH.kategorija, preporuka=MATCH.preporuka, ista_kategorija=False)
    )
    def dodaj_zbog_iste_kategorije(self, film, preporuka):
        self.modify(film, preporuka=preporuka+10.0, ista_kategorija=True)

    # Ако постоји филм у којем игра омиљени глумац, а режирао га је исти редитељ као и редитељ омиљеног
    # филма, онда том филму увећати препоруку за 10

    @Rule(
        Fact(faza="4"),
        Korisnik(omiljeni_glumac=MATCH.glumac, omiljeni_film=MATCH.naziv),
        Film(naziv=MATCH.naziv, reziser=MATCH.reziser),
        AS.film << Film(reziser=MATCH.reziser, glavna_uloga=MATCH.glavna, sporedne_uloge=MATCH.sporedne, ima_omiljenog_glumca=False, preporuka=MATCH.preporuka),
        TEST(lambda glumac, glavna, sporedne: glumac == glavna or glumac in sporedne)
    )
    def dodaj_zbog_omiljenog_glumca(self, film, preporuka):
        self.modify(film, preporuka=preporuka+10.0, ima_omiljenog_glumca=True)

    # а филмовима у којима се не појављује омиљени глумац смањити препоруку за 7.

    @Rule(
        Fact(faza="4"),
        Korisnik(omiljeni_glumac=MATCH.glumac),
        AS.film << Film(glavna_uloga=MATCH.glavna, sporedne_uloge=MATCH.sporedne, nema_omiljenog_glumca=False, preporuka=MATCH.preporuka),
        TEST(lambda glumac, glavna, sporedne: glumac != glavna and glumac not in sporedne)
    )
    def skini_zbog_omiljenog_glumca(self, film, preporuka):
        self.modify(film, preporuka=preporuka-7.0, nema_omiljenog_glumca=True)

    # На основу свих рецензија, доделити просечну оцену свим филмовима.

    @Rule(
        Fact(faza="4"),
        AS.film << Film(naziv=MATCH.naziv, suma_ocena=MATCH.suma_ocena, broj_ocena=MATCH.broj_ocena),
        AS.recenzija << Recenzija(naziv_filma=MATCH.naziv, ocena=MATCH.ocena, uracunata=False)
    )
    def dodaj_ocenu_filmu(self, film, recenzija, suma_ocena, broj_ocena, ocena):
        self.modify(film, suma_ocena=suma_ocena+ocena, broj_ocena=broj_ocena+1)
        self.modify(recenzija, uracunata=True)

    @Rule(
        Fact(faza="4"),
        AS.film << Film(naziv=MATCH.naziv, suma_ocena=MATCH.suma_ocena, broj_ocena=MATCH.broj_ocena, dobijena_prosecna=False),
        NOT(Recenzija(naziv_filma=MATCH.naziv, uracunata=False)),
        TEST(lambda broj_ocena: broj_ocena > 0)
    )
    def izracunaj_prosecnu(self, film, suma_ocena, broj_ocena):
        self.modify(film, prosecna_ocena=suma_ocena/broj_ocena, dobijena_prosecna=True)

    # Ако је просечна оцена филма 5 или већа, вредност препоруке се увећава за износ 2 ∗𝑝𝑟𝑜𝑠𝑒𝑐𝑛𝑎𝑂𝑐𝑒𝑛𝑎

    @Rule(
        Fact(faza="4"),
        AS.film << Film(prosecna_ocena = MATCH.prosecna, dobijena_prosecna=True, uracunata_prosecna=False, preporuka=MATCH.preporuka),
        TEST(lambda prosecna: prosecna >= 5.0)
    )
    def dodaj_zbog_prosecne(self, film, preporuka, prosecna):
        self.modify(film, preporuka=preporuka+prosecna*2, uracunata_prosecna=True)

    # а у супротном се смањује за вредност просечне оцене.

    @Rule(
        Fact(faza="4"),
        AS.film << Film(prosecna_ocena = MATCH.prosecna, dobijena_prosecna=True, uracunata_prosecna=False, preporuka=MATCH.preporuka),
        TEST(lambda prosecna: prosecna < 5.0)
    )
    def skini_zbog_prosecne(self, film, preporuka, prosecna):
        self.modify(film, preporuka=preporuka-prosecna, uracunata_prosecna=True)

    # Додатно филмовима са већом просечном оценом од омиљеног филма за сваку позитивну рецензију пријатеља корисника (оцена преко 5) увећати preporuku за 7.

    @Rule(
        Fact(faza="4"),
        Korisnik(ime=MATCH.ime, omiljeni_film=MATCH.omiljeni),
        AS.film << Film(naziv=~MATCH.omiljeni & MATCH.naziv, prosecna_ocena=MATCH.prosecna, dobijena_prosecna=True, preporuka=MATCH.preporuka),
        Film(naziv=MATCH.omiljeni, prosecna_ocena=MATCH.o_prosecna, dobijena_prosecna=True),
        TEST(lambda prosecna, o_prosecna: prosecna > o_prosecna),
        AS.recenzija << Recenzija(naziv_filma=MATCH.naziv, recezent=~MATCH.ime & MATCH.recezent, ocena=MATCH.ocena, uracunata_prijatelj=False),
        OR(
            Prijatelj(osoba_1=MATCH.ime, osoba_2=MATCH.recezent),
            Prijatelj(osoba_1=MATCH.recezent, osoba_2=MATCH.ime)
        ),
        TEST(lambda ocena: ocena > 5)
    )
    def dodaj_zbog_prijatelja(self, film, recenzija, preporuka):
        self.modify(film, preporuka=preporuka+7.0)
        self.modify(recenzija, uracunata_prijatelj=True)

    @Rule(
        AS.faza << Fact(faza="4"),
        salience=-10
    )
    def faza_4_u_5(self, faza):
        self.modify(faza, faza="5")

    # Тек пошто је свим филмовима одређена вредност препоруке исписати три најбоље препоручена филма:

    @Rule(
        Fact(faza="5"),
        Korisnik(omiljeni_film=MATCH.omiljeni),
        AS.film << Film(naziv=~MATCH.omiljeni & MATCH.naziv1, rang=MATCH.rang, preporuka=MATCH.preporuka1),
        Film(naziv=~MATCH.omiljeni & ~MATCH.naziv1 & MATCH.naziv2, preporuka=MATCH.preporuka2),
        NOT(Fact(film1=MATCH.naziv1, film2=MATCH.naziv2)),
        TEST(lambda preporuka1, preporuka2: preporuka1 < preporuka2)
    )
    def dodaj_rang(self, film, rang, naziv1, naziv2):
        self.modify(film, rang=rang+1)
        self.declare(Fact(film1=naziv1, film2=naziv2))

    @Rule(
        AS.faza << Fact(faza="5"),
        salience=-10
    )
    def faza_5_u_6(self, faza):
        self.modify(faza, faza="6")

    @Rule(
        Fact(faza="6"),
        Fact(brojac=MATCH.i),
        AS.ispisani << Fact(ispisani_filmovi=MATCH.broj_ispisanih),
        Korisnik(omiljeni_film=MATCH.omiljeni),
        AS.film << Film(naziv=~MATCH.omiljeni & MATCH.naziv, rang=MATCH.rang, ispisan_film=False, preporuka=MATCH.preporuka),
        TEST(lambda rang, i, broj_ispisanih: rang == i and broj_ispisanih < 3)
    )
    def ispisi_film(self, film, naziv, preporuka, rang, ispisani, broj_ispisanih):
        print(f"{rang + 1}. Film: {naziv}, preporuka: {preporuka}")
        self.modify(film, ispisan_film=True)
        self.modify(ispisani, ispisani_filmovi=broj_ispisanih+1)

    @Rule(
        Fact(faza="6"),
        Film(naziv=MATCH.naziv, ispisan_film=True),
        AS.recenzija << Recenzija(naziv_filma=MATCH.naziv, tekst_recenzije=MATCH.tekst, ispisana_recenzija=False)
    )
    def ispisi_recenziju(self, recenzija, tekst):
        print(f"Recenzija: {tekst}")
        self.modify(recenzija, ispisana_recenzija=True)

    
    @Rule(
        Fact(faza="6"),
        AS.brojac << Fact(brojac=MATCH.br),
        AS.film << Film(naziv=MATCH.naziv, ispisan_film=True, predji_na_sledeci=False),
        NOT(Recenzija(naziv_filma=MATCH.naziv, ispisana_recenzija=False)),
    )
    def povecaj_brojac(self, brojac, br, film):
        print()
        print()
        self.modify(brojac, brojac=br+1)
        self.modify(film, predji_na_sledeci=True)

engine = Engine()
engine.reset()
engine.run()