from experta import *
import re
import schema

class Film(Fact): 
    naziv = Field(str)
    reziser = Field(str)
    kategorija = Field(schema.Or("AKCIJA", "DRAMA", "HOROR", "TRILER", "NAUCNA_FANTASTIKA", "KOMEDIJA"))
    opis = Field(str)
    datum_premijere = Field(lambda x: re.match(r'[0-9]{4}-[0-9]{2}-[0-9]{2}', x))
    lista_glumaca = Field(list)
    duzina_trajanja = Field(float)
    preporuka = Field(float, default = 50)
    dodato_za_istu_kategoriju = Field(bool, default = False)
    dodato_za_srodnu_kategoriju = Field(bool, default = False)  
    skinuto_zbog_nagrade = Field(bool, default = False)
    dodato_zbog_omiljenog_glumca = Field(bool, default = False)
    dodato_zbog_zanra = Field(bool, default = False)
    rang = Field(int, default = 0)
    otstampana = Field(bool, default = False)

class SrodneKategorije(Fact): 
    naziv_prve_kategorije = Field(str)
    naziv_druge_kategorije = Field(str)

class Recenzija(Fact): 
    naziv_filma = Field(str)
    tekst_recenzije = Field(str)
    ocena = Field(lambda x: isinstance(x, int) and (0<=x<=10))
    dodato_prosek = Field(bool, default = False)
    otstampana = Field(bool, default = False)

class FilmskaNagrada(Fact): 
    naziv_filma = Field(str)
    nagrada = schema.Or("ZLATNA_PALMA", "OSKAR", "ZLATNI_LAV")
    dodata_filmu = Field(bool, default = False)

class ProsecnaOcena(Fact): 
    suma = Field(int, default = 0)
    brojac = Field(int, default = 0)
    prosek = Field(float, default = 0) 
    obradjena = Field(bool, default = False)
    dodata_u_preporuku = Field(bool, default = False)
    dodato_zbog_veceg_proseka = Field(bool, default = False)

class Korisnik(Fact):
    omiljeni_film = Field(str)
    omiljena_kategorija = Field(schema.Or("AKCIJA", "DRAMA", "HOROR", "TRILER", "NAUCNA_FANTASTIKA", "KOMEDIJA"))
    omiljeni_glumac = Field(str)
    neomiljena_kategorija = Field(schema.Or("AKCIJA", "DRAMA", "HOROR", "TRILER", "NAUCNA_FANTASTIKA", "KOMEDIJA"))

class Engine(KnowledgeEngine): 

    @DefFacts()
    def loadFacts(self): 
        yield Film(naziv = "A", reziser = "Pera", kategorija = "AKCIJA", opis = "Opis...", datum_premijere = "2020-11-11",
                    lista_glumaca = ["Misa", "Dule", "Nexi"], duzina_trajanja = 2.5)

        yield Film(naziv = "B", reziser = "Mika", kategorija = "KOMEDIJA", opis = "Opis...", datum_premijere = "2018-12-26",
                    lista_glumaca = ["Misa", "Dule", "Nexi"], duzina_trajanja = 1.5)

        yield Film(naziv = "C", reziser = "Laza", kategorija = "HOROR", opis = "Opis...", datum_premijere = "2021-01-11",
                    lista_glumaca = ["Masa", "Dule", "Nexi"], duzina_trajanja = 2.5)

        yield Film(naziv = "D", reziser = "Zika", kategorija = "TRILER", opis = "Opis...", datum_premijere = "2001-10-10",
                    lista_glumaca = ["Misa", "Sale", "Bane"], duzina_trajanja = 2.5)

        yield Film(naziv = "E", reziser = "Sale", kategorija = "AKCIJA", opis = "Opis...", datum_premijere = "2002-11-11",
                    lista_glumaca = ["Misa", "Sale", "Bane"], duzina_trajanja = 1.6)
        
        yield Film(naziv = "F", reziser = "Pera", kategorija = "DRAMA", opis = "Opis...", datum_premijere = "2019-03-04",
                    lista_glumaca = ["Misa", "Boris", "Bane"], duzina_trajanja = 2.1)

        yield SrodneKategorije(naziv_prve_kategorije = "AKCIJA", naziv_druge_kategorije = "TRILER")
        yield SrodneKategorije(naziv_prve_kategorije = "HOROR", naziv_druge_kategorije = "TRILER")
        yield SrodneKategorije(naziv_prve_kategorije = "DRAMA", naziv_druge_kategorije = "AKCIJA")
        yield SrodneKategorije(naziv_prve_kategorije = "KOMEDIJA", naziv_druge_kategorije = "DRAMA")

        yield Recenzija(naziv_filma = "A", tekst_recenzije = "Ocena za A...", ocena = 9)
        yield Recenzija(naziv_filma = "B", tekst_recenzije = "Ocena za B...", ocena = 8)
        yield Recenzija(naziv_filma = "C", tekst_recenzije = "Ocena za C...", ocena = 7)
        yield Recenzija(naziv_filma = "D", tekst_recenzije = "Ocena za D...", ocena = 6)
        yield Recenzija(naziv_filma = "A", tekst_recenzije = "Ocena za A...", ocena = 3)
        yield Recenzija(naziv_filma = "B", tekst_recenzije = "Ocena za B...", ocena = 4)
        yield Recenzija(naziv_filma = "C", tekst_recenzije = "Ocena za C...", ocena = 7)
        yield Recenzija(naziv_filma = "D", tekst_recenzije = "Ocena za D...", ocena = 8)
        yield Recenzija(naziv_filma = "E", tekst_recenzije = "Ocena za E...", ocena = 8)
        yield Recenzija(naziv_filma = "E", tekst_recenzije = "Ocena za E...", ocena = 1)
        yield Recenzija(naziv_filma = "E", tekst_recenzije = "Ocena za E...", ocena = 2)
        
        yield Recenzija(naziv_filma = "F", tekst_recenzije = "Ocena za F...", ocena = 10)
        yield Recenzija(naziv_filma = "F", tekst_recenzije = "Ocena za F...", ocena = 9)
        yield Recenzija(naziv_filma = "F", tekst_recenzije = "Ocena za F...", ocena = 9)

        yield FilmskaNagrada(naziv_filma = "A", nagrada = "ZLATNA_PALMA")
        yield FilmskaNagrada(naziv_filma = "B", nagrada = "OSKAR")
        yield FilmskaNagrada(naziv_filma = "C", nagrada = "ZLATNI_LAV")

        yield Korisnik(omiljeni_film = "A", 
                       omiljena_kategorija = "AKCIJA", 
                       omiljeni_glumac = "Misa", 
                       neomiljena_kategorija = "HOROR", 
                       dao_recenziju = True)
        yield Recenzija(naziv_filma = "A", 
                               tekst_recenzije = "-", 
                               ocena = 10)
    @Rule(
        NOT(Korisnik()), 
        salience = 10
    )
    def ucitajPodatke(self): 
        omiljeni_film = input("Unesite naziv omiljenog filma: ")
        omiljena_kategorija = input("Unesite naziv omiljene kategorije: ")
        omiljeni_glumac = input("Unesite ime omiljenog glumca: ")
        neomiljena_kategorija = input("Unesite naziv kategorije koju ne volite: ")
        self.declare(Korisnik(omiljeni_film = omiljeni_film, 
                              omiljena_kategorija = omiljena_kategorija, 
                              omiljeni_glumac = omiljeni_glumac, 
                              neomiljena_kategorija = neomiljena_kategorija, 
                              dao_recenziju = False))
    

    @Rule(
        AS.korisnik << Korisnik(omiljeni_film = MATCH.omiljeni_film, dao_recenziju = False), 
        salience = 10
    )
    def dajRecenziju(self, korisnik, omiljeni_film): 
        ocena = int(input("Dajte recenziju za svoj omiljeni film: "))
        tekst = input("Unesite tekst recenzije: ")
        self.declare(Recenzija(naziv_filma = omiljeni_film, 
                               tekst_recenzije = tekst, 
                               ocena = ocena))
        self.modify(korisnik, dao_recenziju = True)

    @Rule(
        Korisnik(dao_recenziju = True), 
        Film(naziv = MATCH.film), 
        NOT(ProsecnaOcena(naziv_filma = MATCH.film))
    )
    def izracunajRecenzije(self, film): 
        print("Kreiram prosecnu ocenu za film {}".format(film))
        self.declare(ProsecnaOcena(naziv_filma = film, suma = 0, brojac = 0))

    @Rule(
        AS.prosecna_ocena << ProsecnaOcena(naziv_filma = MATCH.naziv_filma, suma = MATCH.suma, brojac = MATCH.brojac), 
        AS.recenzija << Recenzija(naziv_filma = MATCH.naziv_filma, ocena = MATCH.ocena, dodato_prosek = False)
    )
    def dodajSumuIBrojac(self,prosecna_ocena, suma, brojac, naziv_filma, recenzija, ocena): 
        print("Dodajem ocenu {} za film {}".format(ocena, naziv_filma))
        self.modify(prosecna_ocena, suma = suma + ocena, brojac = brojac + 1)
        self.modify(recenzija, dodato_prosek = True)

    @Rule(
        AS.prosecna_ocena << ProsecnaOcena(naziv_filma = MATCH.naziv_filma, suma = MATCH.suma, 
                                           brojac = MATCH.brojac, prosek = 0, obradjena = False), 
        NOT(Recenzija(naziv_filma = MATCH.naziv_filma, ocena = MATCH.ocena, dodato_prosek = False))
    )
    def izracunajProsek(self, prosecna_ocena, suma, brojac,naziv_filma):
        print("Prosecna ocena za film {} je {}".format(naziv_filma, suma/brojac))
        self.modify(prosecna_ocena, prosek = suma/brojac, obradjena = True)

    @Rule(
        AS.prosecna_ocena << ProsecnaOcena(naziv_filma = MATCH.naziv_filma, 
                                           prosek = MATCH.prosek & P(lambda prosek : prosek >= 5), 
                                           obradjena = True, dodata_u_preporuku = False), 
        AS.film << Film(naziv = MATCH.naziv_filma, preporuka = MATCH.preporuka)
    )
    def dodajProsekUPreporuku(self, naziv_filma, prosek, preporuka, film, prosecna_ocena): 
        print("Filmu {} dodajem prosecnu ocenu {} u preporuku {}. Sada je {}".format(naziv_filma, prosek, 
                                                                            preporuka, prosek+preporuka))
        self.modify(film, preporuka = preporuka + prosek)
        self.modify(prosecna_ocena, dodata_u_preporuku = True)

    @Rule(
        AS.prosecna_ocena << ProsecnaOcena(naziv_filma = MATCH.naziv_filma, 
                                           prosek = MATCH.prosek & P(lambda prosek : prosek < 5), 
                                           obradjena = True, dodata_u_preporuku = False), 
        AS.film << Film(naziv = MATCH.naziv_filma, preporuka = MATCH.preporuka)
    )
    def skiniProsekOdPreporuke(self, naziv_filma, prosek, preporuka, film, prosecna_ocena): 
        print("Filmu {} skidam prosecnu ocenu {} u preporuku {}. Sada je {}".format(naziv_filma, prosek, 
                                                                            preporuka, preporuka - prosek))
        self.modify(film, preporuka = preporuka - prosek)
        self.modify(prosecna_ocena, dodata_u_preporuku = True)
    
    @Rule(
        Korisnik(omiljeni_film = MATCH.omiljeni_film), 
        AS.film<<Film(naziv = MATCH.naziv_filma & ~MATCH.omiljeni_film, preporuka = MATCH.preporuka), 
        ProsecnaOcena(naziv_filma = MATCH.omiljeni_film, 
                      prosek = MATCH.prosek_omiljeni_film, 
                      obradjena = True), 
        AS.prosecna_ocena << ProsecnaOcena(naziv_filma = MATCH.naziv_filma, 
                                           prosek = MATCH.prosek, 
                                           obradjena = True, 
                                           dodato_zbog_veceg_proseka = False), 
        TEST(
            lambda prosek, prosek_omiljeni_film: prosek > prosek_omiljeni_film
        )
    )
    def dodajPreporukuZbogVecegProseka(self, film, preporuka, naziv_filma, prosecna_ocena):
        print("Film {} ima veci prosek od omiljenog. Uvecavam preporuku za 5".format(naziv_filma))
        self.modify(film, preporuka = preporuka + 5.0)
        self.modify(prosecna_ocena,  dodato_zbog_veceg_proseka = True)

    @Rule(
        Korisnik(omiljeni_film = MATCH.omiljeni_film), 
        Film(naziv = MATCH.omiljeni_film, kategorija = MATCH.kategorija), 
        AS.film << Film(naziv = MATCH.naziv_filma & ~MATCH.omiljeni_film, kategorija = MATCH.kategorija, 
                dodato_za_istu_kategoriju = False, preporuka = MATCH.preporuka)
    )
    def dodajZaIstuKategoriju(self, preporuka, naziv_filma, film): 
        print("Filmu {} uvecavam preporuku za 10 zbog iste kategorije".format(naziv_filma))
        self.modify(film, preporuka = preporuka + 10.0, dodato_za_istu_kategoriju = True)

    @Rule(
        Korisnik(omiljeni_film = MATCH.omiljeni_film), 
        Film(naziv = MATCH.omiljeni_film, kategorija = MATCH.kategorija_omiljenog_filma), 
        AS.film << Film(naziv = MATCH.naziv_filma & ~MATCH.omiljeni_film, 
                        kategorija = MATCH.kategorija_filma, 
                        dodato_za_srodnu_kategoriju = False, 
                        preporuka = MATCH.preporuka), 
        OR(
            SrodneKategorije(
                naziv_prve_kategorije = MATCH.kategorija_omiljenog_filma, 
                naziv_druge_kategorije = MATCH.kategorija_filma
            ), 
            SrodneKategorije(
                naziv_prve_kategorije = MATCH.kategorija_filma, 
                naziv_druge_kategorije = MATCH.kategorija_omiljenog_filma
            )
        )
    )
    def dodajZaIstuKategoriju(self, preporuka, naziv_filma, film): 
        print("Filmu {} uvecavam preporuku za 5 zbog srodne kategorije".format(naziv_filma))
        self.modify(film, preporuka = preporuka + 5.0, dodato_za_srodnu_kategoriju = True)

    @Rule(
        AS.film << Film(naziv = MATCH.naziv_filma, preporuka = MATCH.preporuka), 
        AS.nagrada << FilmskaNagrada(naziv_filma = MATCH.naziv_filma, 
                                     nagrada = MATCH.naziv_nagrade,
                                     dodata_filmu = False)
    )
    def dodajFilmskuNagradu(self, film, nagrada, preporuka, naziv_filma, naziv_nagrade): 
        print("Filmu {} uvecavam preporuku zbog nagrade {}".format(naziv_filma, naziv_nagrade))
        self.modify(nagrada, dodata_filmu = True)
        self.modify(film, preporuka = preporuka + 2.0)

    @Rule(
        AS.film << Film(naziv = MATCH.naziv_filma, preporuka = MATCH.preporuka, 
                        skinuto_zbog_nagrade = False), 
        NOT(FilmskaNagrada(naziv_filma = MATCH.naziv_filma))
    )
    def skiniJerNemaNagradu(self, film, naziv_filma, preporuka): 
        print("Filmu {} skidam preporuku jer nema nagradu".format(naziv_filma))
        self.modify(film, preporuka = preporuka - 7.0, skinuto_zbog_nagrade = True)

    @Rule(
        Korisnik(omiljeni_glumac = MATCH.glumac, omiljeni_film = MATCH.omiljeni_film), 
        Film(naziv = MATCH.omiljeni_film, reziser = MATCH.reziser),
        AS.film << Film(naziv = MATCH.naziv_filma & ~MATCH.omiljeni_film, lista_glumaca = MATCH.glumci, 
        dodato_zbog_omiljenog_glumca = False, preporuka = MATCH.preporuka, reziser = MATCH.reziser),
        TEST(lambda glumac, glumci: glumac in glumci)
    )
    def nadjiOmiljenogGlumcaUFilmu(self, film, glumac, naziv_filma, preporuka):
        print("Nasao sam omiljenog glumca {} u filmu {}".format(glumac, naziv_filma))
        self.modify(film, preporuka = preporuka + 10.0, dodato_zbog_omiljenog_glumca = True)

    @Rule(
        AS.film << Film(naziv = MATCH.naziv_filma, kategorija = MATCH.kategorija & (L("KOMEDIJA") | L("TRILER")), 
        dodato_zbog_zanra = False, preporuka = MATCH.preporuka, 
        duzina_trajanja = MATCH.trajanje & P(lambda trajanje: trajanje < 3))
    )
    def dodajZbogZanra(self, film, naziv_filma, kategorija, preporuka, trajanje): 
        print("-->Filmu {} dodajem preporuku zbog zanra {} i trajanja {}".format(naziv_filma, kategorija, trajanje))
        self.modify(film, dodato_zbog_zanra = True, preporuka = preporuka + 5.0)

    @Rule(
        salience = -10
    )
    def izracunajPrvaTri(self): 
        print("--------------------------------------")
        print("Prelazim na racunanje najbolja tri: ")
        self.declare(Fact('faza-rangiranje'))

    @Rule(
        Fact('faza-rangiranje'),
        AS.film << Film(naziv = MATCH.film1, preporuka = MATCH.preporuka1, rang = MATCH.rang), 
        Film(naziv = MATCH.film2, preporuka = MATCH.preporuka2),
        TEST(lambda preporuka1, preporuka2 : preporuka1<=preporuka2), 
        NOT(Fact(prvi_film = MATCH.film1, drugi_film = MATCH.film2))
    )
    def rangirajFilm(self, film1, film2, film, rang): 
        print("Rang filma {} je za sad {}".format(film1, rang))
        self.declare(Fact(prvi_film = film1, drugi_film = film2))
        self.modify(film, rang = rang + 1)

    @Rule(
        Fact('faza-rangiranje'),
        salience = -10
    )
    def predjiNaStampanje(self): 
        print("Kreiram brojac...")
        self.declare(Fact(brojac = 1))

    @Rule(
        Fact(brojac = MATCH.counter & P(lambda counter: counter <= 3)),
        AS.film << Film(naziv = MATCH.naziv_filma, preporuka = MATCH.preporuka, 
                        rang = MATCH.counter, otstampana = False) 
    )
    def stampajFilm(self, naziv_filma, preporuka, counter, film): 
        print("{} Film : {}, preporuka : {}".format(counter, naziv_filma ,preporuka)) 
        self.modify(film, otstampana = True)
    @Rule(
        Fact(brojac = MATCH.counter & P(lambda counter: counter <= 3)),
        Film(naziv = MATCH.naziv_filma, preporuka = MATCH.preporuka, rang = MATCH.counter, otstampana = True), 
        AS.recenzija << Recenzija(naziv_filma = MATCH.naziv_filma, 
                                  tekst_recenzije = MATCH.tekst, otstampana = False)
    )
    def stampajRecenzije(self, recenzija, tekst): 
        print("Recenzija : {}".format(tekst))
        self.modify(recenzija, otstampana = True)

    @Rule(
        AS.brojac << Fact(brojac = MATCH.counter & P(lambda counter: counter <= 3)),
        Film(naziv = MATCH.naziv_filma, rang = MATCH.counter ), 
        NOT(Recenzija(naziv_filma = MATCH.naziv_filma, otstampana = False))
    )
    def uvecajBrojac(self, brojac, counter): 
        print("\n")
        self.modify(brojac, brojac = counter + 1) 

engine = Engine()
engine.reset()
engine.run()