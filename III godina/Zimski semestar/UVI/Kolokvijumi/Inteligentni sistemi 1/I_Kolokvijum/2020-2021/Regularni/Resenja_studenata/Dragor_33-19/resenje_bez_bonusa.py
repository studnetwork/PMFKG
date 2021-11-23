import schema, re
from experta import *
from experta.utils import freeze

### Data Classes ###

# -- Klase definisane zadatkom --

class Film(Fact):
    naziv = Field(str)
    reziser = Field(str)
    kategorija = Field(schema.Or("AKCIJA", "DRAMA", "HOROR", "TRILER", "NAUCNA_FANTASTIKA", "KOMEDIJA"))
    opis = Field(str)
    datum_premijere = Field(lambda x: re.compile(r"[0-9]{4}-[0-9]{2}-[0-9]{2}").match(x) != None)
    lista_glumaca = Field(list)
    duzina_trajanja = Field(float)
    preporuka = Field(float, default = 50.0)

    # dodatna polja
    prosecna_ocena = Field(float, default = 0)
    check = Field(list, default = freeze([]))


class SrodneKategorije(Fact):
    naziv_prve_kategorije = Field(str)
    naziv_druge_kategorije = Field(str)

class FilmskaNagrada(Fact):
    naziv_filma = Field(str)
    nagrada = Field(schema.Or("ZLATNA_PALMA", "OSKAR", "ZLATNI_LAV"))
    check = Field(list, default = freeze([]))

class Recenzija(Fact):
    naziv_filma = Field(str)
    tekst_recenzije = Field(str)
    ocena = Field(lambda x: isinstance(x, int) and x >= 0 and x <= 10)

    # dodatna polja
    sabrana = Field(bool, default = False)


# -- Pomocne klase --

class KorisnickiPodaci(Fact):
    naziv_omiljenog_filma = Field(str)
    naziv_omiljene_kategorije = Field(str)
    naziv_omiljenog_glumca = Field(str)
    naziv_nepozeljne_kategorije = Field(str)

# info o prosecnoj oceni filma
class ZbirOcena(Fact):
    naziv_filma = Field(str)
    zbir = Field(int, default = 0)
    broj_ocena = Field(int, default = 0)

# faza
class Faza(Fact):
    pass

# za sortiranje
class FilmMax(Fact):
    naziv = Field(str, default = "")
    preporuka = Field(float, default = -1)
    counter = Field(int)


# -- Pomocne funkcije --

sadrzi = lambda lista, x: list(lista).count(x) != 0
dodaj = lambda lista, x: list(lista) + [x]


### Ekspertski sistem ###

class MyEngine(KnowledgeEngine):

    def png(self):
        print(self.facts)
        print(self.agenda)
    
    @DefFacts()
    def init(self):
        yield Film(naziv = "A", reziser = "Pera", kategorija = "AKCIJA", 
                    opis = "Opis...", datum_premijere = "2020-11-11", 
                    lista_glumaca = ["Misa", "Dule", "Neca"], duzina_trajanja = 2.5)

        yield Film(naziv = "B", reziser = "Mika", kategorija = "DRAMA", 
                    opis = "Opis...", datum_premijere = "2020-11-11", 
                    lista_glumaca = ["Misa", "Dule", "Neca"], duzina_trajanja = 2.5)

        yield Film(naziv = "C", reziser = "Laza", kategorija = "TRILER", 
                    opis = "Opis...", datum_premijere = "2020-11-11", 
                    lista_glumaca = ["Misa", "Dule", "Neca"], duzina_trajanja = 2.5)

        yield Film(naziv = "D", reziser = "Pera", kategorija = "AKCIJA", 
                    opis = "Opis...", datum_premijere = "2020-11-11", 
                    lista_glumaca = ["Dule", "Neca"], duzina_trajanja = 2.5)
        
        yield Film(naziv = "E", reziser = "Pera", kategorija = "NAUCNA_FANTASTIKA", 
                    opis = "Opis...", datum_premijere = "2020-11-11", 
                    lista_glumaca = ["Misa", "Dule", "Neca"], duzina_trajanja = 2.5)

        yield SrodneKategorije(naziv_prve_kategorije = "AKCIJA", naziv_druge_kategorije = "TRILER")
        yield SrodneKategorije(naziv_prve_kategorije = "AKCIJA", naziv_druge_kategorije = "NAUCNA_FANTASTIKA")
        yield SrodneKategorije(naziv_prve_kategorije = "DRAMA", naziv_druge_kategorije = "KOMEDIJA")
        yield SrodneKategorije(naziv_prve_kategorije = "HOROR", naziv_druge_kategorije = "NAUCNA_FANTASTIKA")

        yield FilmskaNagrada(naziv_filma = "A", nagrada = "ZLATNA_PALMA")
        yield FilmskaNagrada(naziv_filma = "B", nagrada = "OSKAR")

        yield Recenzija(naziv_filma = "A", tekst_recenzije = "Tekst 1...", ocena = 0)
        yield Recenzija(naziv_filma = "A", tekst_recenzije = "Tekst 2...", ocena = 1)
        yield Recenzija(naziv_filma = "B", tekst_recenzije = "Tekst 3...", ocena = 8)
        yield Recenzija(naziv_filma = "B", tekst_recenzije = "Tekst 4...", ocena = 6)
        yield Recenzija(naziv_filma = "C", tekst_recenzije = "Tekst 5...", ocena = 5)
        yield Recenzija(naziv_filma = "C", tekst_recenzije = "Tekst 6...", ocena = 4)
        yield Recenzija(naziv_filma = "D", tekst_recenzije = "Tekst 7...", ocena = 9)
        yield Recenzija(naziv_filma = "D", tekst_recenzije = "Tekst 8...", ocena = 7)
        yield Recenzija(naziv_filma = "E", tekst_recenzije = "Tekst 9...", ocena = 5)
        yield Recenzija(naziv_filma = "E", tekst_recenzije = "Tekst 10...", ocena = 10)

        yield Faza("setup")
        yield FilmMax(counter = 3) # treba ispisati 3 najpogodnija filma


    # > > > FAZA: setup

    # Unos korisnickih podataka
    @Rule(
        Faza("setup"),
        NOT(KorisnickiPodaci())
    )
    def unos_korisnickih_podataka(self):
        print("Omiljeni film:")
        o_film = input()
        print("Omiljena kategorija:")
        o_kat = input()
        print("Omiljeni glumac:")
        o_glum = input()
        print("Nepozeljna kategorija:")
        n_kat = input()

        self.declare(KorisnickiPodaci(naziv_omiljenog_filma = o_film,
                                    naziv_omiljene_kategorije = o_kat,
                                    naziv_omiljenog_glumca = o_glum,
                                    naziv_nepozeljne_kategorije = n_kat))

    # Uklanjanje nepozeljnih filmova
    @Rule(
        Faza("setup"),
        KorisnickiPodaci(naziv_nepozeljne_kategorije = MATCH.nep),
        AS.f << Film(kategorija = MATCH.nep, check = MATCH.check)
    )
    def uklanjanje_nepozeljnih_filmova(self, f):
        self.retract(f)

    # Unos recenzije
    @Rule(
        Faza("setup"),
        KorisnickiPodaci(naziv_omiljenog_filma = MATCH.film)
    )
    def unos_recenzije(self, film):
        print("Unosenje recenzije za film \"{}\"".format(film))
        print("Tekst:")
        tekst = input()
        print("Ocena:")
        ocena = int(input())

        self.declare(Recenzija(naziv_filma = film, tekst_recenzije = tekst, ocena = ocena))


    # > > > FAZA: proseci

    # Kreiranje ZbirOcena
    @Rule(
        Faza("proseci"),
        Film(naziv = MATCH.naziv)
    )
    def kreiranje_zbir_ocena(self, naziv):
        self.declare(ZbirOcena(naziv_filma = naziv))

    # Sabiranje ocena
    @Rule(
        Faza("proseci"),
        AS.r << Recenzija(naziv_filma = MATCH.naziv, ocena = MATCH.ocena, sabrana = False),
        AS.z << ZbirOcena(naziv_filma = MATCH.naziv, zbir = MATCH.zbir, broj_ocena = MATCH.broj)
    )
    def sabiranje_ocena(self, r, z, ocena, zbir, broj):
        self.modify(z, zbir = zbir + ocena, broj_ocena = broj + 1)
        self.modify(r, sabrana = True)

    # Cuvanje prosecnih ocena
    @Rule(
        Faza("proseci"),
        ZbirOcena(naziv_filma = MATCH.naziv, zbir = MATCH.zbir, broj_ocena = MATCH.broj & P(lambda x: x > 0)),
        AS.f << Film(naziv = MATCH.naziv, check = MATCH.check),

        TEST(lambda check: not sadrzi(check, "cuvanje_prosecnih_ocena"))
    )
    def cuvanje_prosecnih_ocena(self, f, zbir, broj, check):
        self.modify(f, prosecna_ocena = zbir / broj, check = dodaj(check, "cuvanje_prosecnih_ocena"))

    
    # > > > FAZA: preporuke
    
    ## Uodnosu na prosek
    # Povecanje
    @Rule(
        Faza("preporuke"),
        AS.f << Film(preporuka = MATCH.prep, prosecna_ocena = MATCH.pros & P(lambda x: x >= 5), check = MATCH.check),

        TEST(lambda check: not sadrzi(check, "prep_prosek_povecaj"))
    )
    def prep_prosek_povecaj(self, f, prep, pros, check):
        self.modify(f, preporuka = prep + pros, check = dodaj(check, "prep_prosek_povecaj"))

    # Smanjenje
    @Rule(
        Faza("preporuke"),
        AS.f << Film(preporuka = MATCH.prep, prosecna_ocena = MATCH.pros & P(lambda x: x < 5), check = MATCH.check),

        TEST(lambda check: not sadrzi(check, "prep_prosek_smanji"))
    )
    def prep_prosek_smanji(self, f, prep, pros, check):
        self.modify(f, preporuka = prep - pros, check = dodaj(check, "prep_prosek_smanji"))

    
    ## U odnosu na prosek omiljenog filma
    # Povecaj
    @Rule(
        Faza("preporuke"),
        KorisnickiPodaci(naziv_omiljenog_filma = MATCH.om_naziv),
        Film(naziv = MATCH.om_naziv, prosecna_ocena = MATCH.om_pros),
        AS.f << Film(prosecna_ocena = MATCH.pros, preporuka = MATCH.prep, check = MATCH.check),

        TEST(lambda pros, om_pros, check: pros > om_pros and not sadrzi(check, "prep_prosek_omiljenog"))
    )
    def prep_prosek_omiljenog(self, f, prep, check):
        self.modify(f, preporuka = prep + 5.0, check = dodaj(check, "prep_prosek_omiljenog"))


    ## U odnosu na kategoriju omiljenog
    # Povecaj za 10
    @Rule(
        Faza("preporuke"),
        KorisnickiPodaci(naziv_omiljenog_filma = MATCH.om_naziv),
        Film(naziv = MATCH.om_naziv, kategorija = MATCH.om_kat),
        AS.f << Film(naziv = ~MATCH.om_naziv, kategorija = MATCH.om_kat, preporuka = MATCH.prep, check = MATCH.check),

        TEST(lambda check: not sadrzi(check, "prep_kategorija_omiljenog"))
    )
    def prep_kategorija_omiljenog(self, f, prep, check):
        self.modify(f, preporuka = prep + 10.0, check = dodaj(check, "prep_kategorija_omiljenog"))

    # Povecaj za 5
    @Rule(
        Faza("preporuke"),
        KorisnickiPodaci(naziv_omiljenog_filma = MATCH.om_naziv),
        Film(naziv = MATCH.om_naziv, kategorija = MATCH.om_kat),
        AS.f << Film(kategorija = MATCH.kat, preporuka = MATCH.prep, check = MATCH.check),
        OR(
            SrodneKategorije(naziv_prve_kategorije = MATCH.kat, naziv_druge_kategorije = MATCH.om_kat),
            SrodneKategorije(naziv_prve_kategorije = MATCH.om_kat, naziv_druge_kategorije = MATCH.kat)
        ),

        TEST(lambda check: not sadrzi(check, "prep_slicna_kategorija_omiljenog"))
    )
    def prep_slicna_kategorija_omiljenog(self, f, prep, check):
        self.modify(f, preporuka = prep + 5.0, check = dodaj(check, "prep_slicna_kategorija_omiljenog"))


    ## U odnosu na nagrade
    # Za svaku, +2
    @Rule(
        Faza("preporuke"),
        AS.n << FilmskaNagrada(naziv_filma = MATCH.naziv, nagrada = MATCH.nagr, check = MATCH.check),
        AS.f << Film(naziv = MATCH.naziv, preporuka = MATCH.prep),

        TEST(lambda check: not sadrzi(check, "prep_za_nagradu"))
    )
    def prep_za_nagradu(self, f, n, prep, check):
        self.modify(f, preporuka = prep + 2.0)
        self.modify(n, check = dodaj(check, "prep_za_nagradu"))

    # Ako nema nijednu
    @Rule(
        Faza("preporuke"),
        AS.f << Film(naziv = MATCH.naziv, preporuka = MATCH.prep, check = MATCH.check),
        NOT(FilmskaNagrada(naziv_filma = MATCH.naziv)),

        TEST(lambda check: not sadrzi(check, "prep_nijedna_nagrada"))
    )
    def prep_nijedna_nagrada(self, f, prep, check):
        self.modify(f, preporuka = prep - 7.0, check = dodaj(check, "prep_nijedna_nagrada"))


    ## U odnosu omiljenog glumca i reditelja omiljenog filma
    # Ako postoji
    @Rule(
        Faza("preporuke"),
        KorisnickiPodaci(naziv_omiljenog_filma = MATCH.om_naziv, naziv_omiljenog_glumca = MATCH.om_glum),
        Film(naziv = MATCH.om_naziv, reziser = MATCH.om_rez),
        AS.f << Film(naziv = MATCH.naziv, lista_glumaca = MATCH.glumci, reziser = MATCH.rez, preporuka = MATCH.prep, check = MATCH.check),
        
        TEST(lambda om_glum, om_rez, glumci, rez, check: om_rez == rez and sadrzi(glumci, om_glum) and not sadrzi(check, "prep_glumac_reditelj"))
    )
    def prep_glumac_reditelj(self, f, prep, check):
        self.modify(f, preporuka = prep + 10.0, check = dodaj(check, "prep_glumac_reditelj"))


    ## U ondosu na dodatni zahtev
    # Ako je ispunjen
    @Rule(
        Faza("preporuke"),
        AS.f << Film(duzina_trajanja = P(lambda x: x < 3.0), kategorija = L("TRILER") | L("KOMEDIJA"), preporuka = MATCH.prep, check = MATCH.check),
        
        TEST(lambda check: not sadrzi(check, "prep_dodatno"))
    )
    def prep_dodatno(self, f, prep, check):
        self.modify(f, preporuka = prep + 5.0, check = dodaj(check, "prep_dodatno"))


    # > > > FAZA: max - Pronalazak filma sa najvecom preporukom
    @Rule(
        Faza("max"),
        KorisnickiPodaci(naziv_omiljenog_filma = MATCH.om_naziv),
        Film(naziv = MATCH.naziv & ~MATCH.om_naziv, preporuka = MATCH.prep),
        AS.m << FilmMax(preporuka = MATCH.m_prep),
        TEST(lambda prep, m_prep: prep > m_prep)
    )
    def nadnji_max(self, m, naziv, prep):
        self.modify(m, naziv = naziv, preporuka = prep)


    # > > > FAZA: ispis_max - Ispis filma sa najvecom preporukom
    @Rule(
        Faza("ispis_max"),
        FilmMax(naziv = MATCH.m_naziv, preporuka = MATCH.prep)
    )
    def ispis_max(self, m_naziv, prep):
        print("Film: {}, preporuka {}".format(m_naziv, prep))

    
    # > > > FAZA: ispis_rec - Ispis recenzije za prethodno pronadjenog filma sa najvecom preporukom
    @Rule(
        Faza("ispis_rec"),
        FilmMax(naziv = MATCH.m_naziv),
        Recenzija(naziv_filma = MATCH.m_naziv, tekst_recenzije = MATCH.tekst)
    )
    def ispis_recenzije(self, tekst):
        print("Recenzija: {}".format(tekst))

    
    # > > > FAZA: kraj - Brisanje filma sa najvecom preporukom i reset polja cinjenice koja cuva info o tom filmu
    @Rule(
        Faza("kraj"),
        AS.m << FilmMax(naziv = MATCH.m_naziv, counter = MATCH.cntr),
        AS.f << Film(naziv = MATCH.m_naziv)
    )
    def opet_max(self, m, f, cntr):
        self.retract(f)
        self.modify(m, naziv = "", preporuka = -1.0, counter = cntr - 1)


    ### Kontrola toka ###

    @Rule(
        AS.f << Faza("setup"),
        salience = -10
    )
    def kt_setup_to_proseci(self, f):
        self.modify(f, _0 = "proseci")

    @Rule(
        AS.f << Faza("proseci"),
        salience = -10
    )
    def kt_proseci_to_preporuke(self, f):
        self.modify(f, _0 = "preporuke")

    @Rule(
        AS.f << Faza("preporuke"),
        salience = -10
    )
    def kt_preporuke_to_max(self, f):
        self.modify(f, _0 = "max")


    # -- Za sortiranje --

    @Rule(
        AS.f << Faza("max"),
        salience = -10
    )
    def kt_max_to_ispis_max(self, f):
        self.modify(f, _0 = "ispis_max")

    @Rule(
        AS.f << Faza("ispis_max"),
        salience = -10
    )
    def kt_ispis_max_to_rec(self, f):
        self.modify(f, _0 = "ispis_rec")

    @Rule(
        AS.f << Faza("ispis_rec"),
        salience = -10
    )
    def kt_ispis_rec_to_kraj(self, f):
        self.modify(f, _0 = "kraj")

    # Vracanje na fazu "max" ukoliko brojac jos nije dostigao 0
    @Rule(
        AS.f << Faza("kraj"),
        AS.m << FilmMax(counter = P(lambda x: x > 0)),
        salience = -10
    )
    def kt_kraj_to_max(self, f):
        self.modify(f, _0 = "max")
    
    # Zavrsetak programa (brisanje cinjenice za fazu) ukoliko je brojac 0
    @Rule(
        AS.f << Faza("kraj"),
        AS.m << FilmMax(counter = 0),
        salience = -10
    )
    def kt_finito(self, f):
        self.retract(f)

    

# watch("ACTIVATIONS")

ng = MyEngine()
ng.reset()

# ng.png()

ng.run()

ng.png()

# watch(level=0)

