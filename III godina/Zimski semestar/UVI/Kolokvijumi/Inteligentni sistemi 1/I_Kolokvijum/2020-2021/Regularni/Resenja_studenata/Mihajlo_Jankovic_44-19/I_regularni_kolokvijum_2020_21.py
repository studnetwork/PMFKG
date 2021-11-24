from experta import *
from experta.utils import freeze
import schema
import re

#watch("ACTIVATIONS","RULES","FACTS")

class Faza(Fact):
    pass

class ZbirOcena(Fact):
    naziv_filma = Field(str)
    zbir = Field(int, default = 0)
    broj_ocena = Field(int, default = 0)

class Film(Fact):
    naziv = Field(str)
    reziser = Field(str)
    kategorija = schema.Or("AKCIJA","DRAMA","HOROR","TRILER","NAUCNA_FANTASTIKA","KOMEDIJA")
    opis = Field(str)
    datum_premijere = Field(lambda x: isinstance(x,str) and re.compile(r"[0-9]{4}-[0-9]{2}-[0-9]{2}").match(x) != None)
    lista_glumaca = Field(list)
    duzina_trajanja = Field(lambda x: isinstance(x,float) and 0 < x < 24)
    preporuka = Field(float,default = 50)

    # Dodato
    prosecna_ocena = Field(float, default = 0)
    flag = Field(list,False,freeze([]))

class SrodneKategorije(Fact):
    naziv_prve_kategorije = Field(str)
    naziv_druge_kategorije = Field(str)

class Recenzija(Fact):
    naziv_filma = Field(str)
    tekst_recenzije = Field(str)
    ocena = Field(lambda x: isinstance(x,int) and 0 <= x <= 10)

    # Dodato
    sabrana = Field(bool,default = False)

class FilmskaNagrada(Fact):
    naziv_filma = Field(str)
    nagrada = schema.Or("ZLATNA_PALMA","OSKAR","ZLATNI_LAV")

    # Dodato
    uvazena = Field(bool,default = False)

class Korisnik(Fact):
    omiljeni_film = Field(str)
    omiljena_kategorija = Field(str)
    omiljeni_glumac = Field(str)
    kategorija_koju_ne_voli = Field(str)

class MaxFilm(Fact):
    naziv = Field(str,default = "")
    preporuka = Field(float, default = -1)
    counter = Field(int, default = 3)

class Engine(KnowledgeEngine):
    @DefFacts()
    def init(self):
        yield Faza("Unos")

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

        yield SrodneKategorije(naziv_prve_kategorije = "AKCIJA", naziv_druge_kategorije = "TRILER")
        yield SrodneKategorije(naziv_prve_kategorije = "AKCIJA", naziv_druge_kategorije = "NAUCNA_FANTASTIKA")
        yield SrodneKategorije(naziv_prve_kategorije = "DRAMA", naziv_druge_kategorije = "KOMEDIJA")
        yield SrodneKategorije(naziv_prve_kategorije = "HOROR", naziv_druge_kategorije = "NAUCNA_FANTASTIKA")

        yield MaxFilm()

    # Unos korisnickih podataka sa standardnog ulaza
    @Rule(
        Faza("Unos")
    )
    def korisnicki_unos(self):
        self.declare(Korisnik(omiljeni_film = "A", 
                     omiljena_kategorija = "AKCIJA", 
                     omiljeni_glumac = "Misa", 
                     kategorija_koju_ne_voli = "NAUCNA_FANTASTIKA"))
        '''
        self.declare(omiljeni_film = str(input()), 
                     omiljena_kategorija = str(input()), 
                     omiljeni_glumac = str(input()), 
                     kategorija_koju_ne_voli = str(input()))
        '''

    # Kontrola toka: Unos -> Obrisi Kategoriju 
    # {
    @Rule(
        AS.faza << Faza("Unos"),
        salience = -10
    )
    def kontrola_iz_unos_u_obrisi_kategoriju(self,faza):
        self.retract(faza)
        self.declare(Faza("Obrisi Kategoriju"))
    # }

    # Brisanje svih filmova iz kategorije koju korisnik ne voli
    @Rule(
        Faza("Obrisi Kategoriju"),
        Korisnik(kategorija_koju_ne_voli = MATCH.kategorija),
        AS.film << Film(kategorija = MATCH.kategorija)
    )
    def ukloni_film(self,film):
        self.retract(film)

    # Kontrola toka: Obrisi Kategoriju -> Dodaj Recenziju
    # {
    @Rule(
        AS.faza << Faza("Obrisi Kategoriju"),
        salience = -10
    )
    def kontrola_iz_obrisi_kategoriju_u_dodaj_recenziju(self,faza):
        self.retract(faza)
        self.declare(Faza("Dodaj Recenziju"))
    # }

    # Dodavanje recenzije sa standardnog ulaza
    @Rule(
        Faza("Dodaj Recenziju"),
        Korisnik(omiljeni_film = MATCH.naziv)
    )
    def dodaj_recenziju(self,naziv):
        self.declare(Recenzija(naziv_filma = naziv, tekst_recenzije = "Opis ...", ocena = 9))
        #self.declare(Recenzija(naziv_filma = naziv, tekst_recenzije = str(input()), ocena = int(input())))

    # Kontrola toka: Dodaj Recenziju -> Prosek
    # {
    @Rule(
        AS.faza << Faza("Dodaj Recenziju"),
        salience = -10
    )
    def kontrola_iz_dodaj_recenziju_u_prosek(self,faza):
        self.retract(faza)
        self.declare(Faza("Prosek"))
    # }

    # Kreiranje cinjenica ZbirOcena
    @Rule(
        Faza("Prosek"),
        Film(naziv = MATCH.naziv)
    )
    def kreiraj_zbir_ocena(self,naziv):
        self.declare(ZbirOcena(naziv_filma = naziv))

    # Sabiranje ocena
    @Rule(
        Faza("Prosek"),
        AS.recenzija << Recenzija(naziv_filma = MATCH.naziv, ocena = MATCH.ocena, sabrana = False),
        AS.zbir_ocena << ZbirOcena(naziv_filma = MATCH.naziv, zbir = MATCH.zbir, broj_ocena = MATCH.br)
    )
    def saberi_ocene(self,recenzija, ocena, zbir_ocena, zbir, br):
        self.modify(zbir_ocena, zbir = zbir + ocena, broj_ocena = br + 1)
        self.modify(recenzija, sabrana = True)

    # Dodela ocena filmovima
    @Rule(
        Faza("Prosek"),
        ZbirOcena(naziv_filma = MATCH.naziv, zbir = MATCH.zbir, broj_ocena = MATCH.broj_ocena),
        AS.film << Film(naziv = MATCH.naziv, flag = MATCH.flag),
        NOT(Recenzija(naziv_filma = MATCH.naziv, sabrana = False)),
        TEST(lambda flag: "Prosek" not in flag)
    )
    def dodela_proseka(self,film,zbir,broj_ocena,flag):
        self.modify(film, prosecna_ocena = zbir/broj_ocena, flag = list(flag) + ["Prosek"])

    # Kontrola toka: Prosek -> Preporuke
    # {
    @Rule(
        AS.faza << Faza("Prosek"),
        salience = -10
    )
    def kontrola_iz_prosek_u_preporuke(self,faza):
        self.retract(faza)
        self.declare(Faza("Preporuke"))
    # }

    # Povecavanje preporuke po proseku
    @Rule(
        Faza("Preporuke"),
        AS.film << Film(prosecna_ocena = MATCH.prosecna, preporuka = MATCH.preporuka, flag = MATCH.flag),
        TEST(lambda prosecna,flag: prosecna >= 5 and "uvecaj_preporuku_po_proseku" not in flag)
    )
    def uvecaj_preporuku_po_proseku(self,film,prosecna,preporuka,flag):
        self.modify(film,preporuka = preporuka + prosecna, flag = list(flag) + ["uvecaj_preporuku_po_proseku"])

    # Smanjenje preporuke po proseku
    @Rule(
        Faza("Preporuke"),
        AS.film << Film(prosecna_ocena = MATCH.prosecna, preporuka = MATCH.preporuka, flag = MATCH.flag),
        TEST(lambda prosecna,flag: prosecna < 5 and "umanji_preporuku_po_proseku" not in flag)
    )
    def umanji_preporuku_po_proseku(self,film,prosecna,preporuka,flag):
        self.modify(film,preporuka = preporuka - prosecna, flag = list(flag) + ["umanji_preporuku_po_proseku"])

    # Povecavanje preporuke po omiljenom filmu
    @Rule(
        Faza("Preporuke"),
        Korisnik(omiljeni_film = MATCH.naziv),
        Film(naziv = MATCH.naziv, prosecna_ocena = MATCH.prosecna_omiljenog),
        AS.film << Film(naziv = ~MATCH.naziv, prosecna_ocena = MATCH.prosecna, preporuka = MATCH.preporuka, flag = MATCH.flag),
        TEST(lambda prosecna_omiljenog,prosecna,flag: prosecna_omiljenog < prosecna and "uvecaj_preporuku_po_omiljenom" not in flag)
    )
    def uvecaj_preporuku_po_omiljenom(self,film,preporuka,flag):
        self.modify(film, preporuka = float(preporuka + 5), flag = list(flag) + ["uvecaj_preporuku_po_omiljenom"])

    # Povecavanje preporuke po istoj kategoriji
    @Rule(
        Faza("Preporuke"),
        Korisnik(omiljeni_film = MATCH.naziv),
        Film(naziv = MATCH.naziv, kategorija = MATCH.kategorija),
        AS.film << Film(naziv = ~MATCH.naziv, kategorija = MATCH.kategorija, preporuka = MATCH.preporuka, flag = MATCH.flag),
        TEST(lambda flag: "uvecaj_preporuku_po_istoj_kategoriji" not in flag)
    )
    def uvecaj_preporuku_po_istoj_kategoriji(self,film,preporuka,flag):
        self.modify(film, preporuka = float(preporuka + 10), flag = list(flag) + ["uvecaj_preporuku_po_istoj_kategoriji"])

    # Povecavanje preporuke po slicnoj kategoriji
    @Rule(
        Faza("Preporuke"),
        Korisnik(omiljeni_film = MATCH.naziv),
        Film(naziv = MATCH.naziv, kategorija = MATCH.kategorija_omiljenog),
        AS.film << Film(naziv = ~MATCH.naziv, kategorija = MATCH.kategorija, preporuka = MATCH.preporuka, flag = MATCH.flag),
        SrodneKategorije(naziv_prve_kategorije = MATCH.prva, naziv_druge_kategorije = MATCH.druga),
        TEST(lambda prva,druga,kategorija_omiljenog,kategorija,flag: ((prva == kategorija_omiljenog and druga == kategorija) or
                                                                     (prva == kategorija and druga == kategorija_omiljenog)) and
                                                                     "uvecaj_preporuku_po_slicnoj_kategoriji" not in flag)
    )
    def uvecaj_preporuku_po_slicnoj_kategoriji(self,film,preporuka,flag):
        self.modify(film, preporuka = float(preporuka + 5), flag = list(flag) + ["uvecaj_preporuku_po_slicnoj_kategoriji"])
    
    # Povecavanje preporuke po filmskoj nagradi
    @Rule(
        Faza("Preporuke"),
        AS.nagrada << FilmskaNagrada(naziv_filma = MATCH.naziv, uvazena = False),
        AS.film << Film(naziv = MATCH.naziv, preporuka = MATCH.preporuka)
    )
    def uvecaj_preporuku_po_nagradi(self,film,preporuka,nagrada):
        self.modify(film, preporuka = float(preporuka + 2))
        self.modify(nagrada, flag = True)
    
    # Smanjenje preporuke po filmskoj nagradi
    @Rule(
        Faza("Preporuke"),
        AS.film << Film(naziv = MATCH.naziv, preporuka = MATCH.preporuka, flag = MATCH.flag),
        NOT(FilmskaNagrada(naziv = MATCH.naziv)),
        TEST(lambda flag: "umanji_preporuku_po_nagradi" not in flag)
    )
    def umanji_preporuku_po_nagradi(self,film,preporuka,flag):
        self.modify(film, preporuka = float(preporuka - 7), flag = list(flag) + ["umanji_preporuku_po_nagradi"])
    
    # Povecavanje preporuke po omiljenom glumcu
    @Rule(
        Faza("Preporuke"),
        Korisnik(omiljeni_film = MATCH.naziv, omiljeni_glumac = MATCH.omiljeni_glumac),
        Film(naziv = MATCH.naziv, reziser = MATCH.reziser_omiljenog),
        AS.film << Film(lista_glumaca = MATCH.lista_glumaca, reziser = MATCH.reziser_omiljenog, preporuka = MATCH.preporuka, flag = MATCH.flag),
        TEST(lambda omiljeni_glumac,lista_glumaca,flag: omiljeni_glumac in lista_glumaca and "uvecaj_preporuku_po_omiljenom_glumcu" not in flag)
    )
    def uvecaj_preporuku_po_omiljenom_glumcu(self,film,preporuka,flag):
        self.modify(film, preporuka = float(preporuka + 10), flag = list(flag) + ["uvecaj_preporuku_po_omiljenom_glumcu"])

    # Povecavanje preporuke komediji i trileru
    @Rule(
        Faza("Preporuke"),
        AS.film << Film(kategorija = L("KOMEDIJA") | L("TRILER"), duzina_trajanja = MATCH.trajanje, preporuka = MATCH.preporuka, flag = MATCH.flag),
        TEST(lambda trajanje,flag: trajanje < 3 and "uvecaj_preporuku_komediji_i_trileru" not in flag)
    )
    def uvecaj_preporuku_komediji_i_trileru(self,film,preporuka,flag):
        self.modify(film, preporuka = float(preporuka + 10), flag = list(flag) + ["uvecaj_preporuku_komediji_i_trileru"])

    # Kontrola toka: Preporuke -> Max
    # {
    @Rule(
        AS.faza << Faza("Preporuke"),
        salience = -10
    )
    def kontrola_iz_preporuke_u_max(self,faza):
        self.retract(faza)
        self.declare(Faza("Max"))
    # }
    
    # Pronalazenje filma sa najvecom preporukom
    @Rule(
        Faza("Max"),
        Korisnik(omiljeni_film = MATCH.naziv_omiljenog),
        Film(naziv = MATCH.naziv & ~MATCH.naziv_omiljenog, preporuka = MATCH.preporuka),
        AS.max << MaxFilm(preporuka = MATCH.max_preporuka),
        TEST(lambda preporuka, max_preporuka: preporuka > max_preporuka)
    )
    def nadji_max(self,max,naziv,preporuka):
        self.modify(max, naziv = naziv, preporuka = preporuka)
    
    # Kontrola toka: Max -> Ispisi Max
    # {
    @Rule(
        AS.faza << Faza("Max"),
        salience = -10
    )
    def kontrola_iz_max_u_max_ispis(self,faza):
        self.retract(faza)
        self.declare(Faza("Ispisi Max"))
    # }

    # Ispis filma sa najvecom preporukom
    @Rule(
        Faza("Ispisi Max"),
        MaxFilm(naziv = MATCH.naziv, preporuka = MATCH.preporuka)
    )
    def max_ispis(self,naziv,preporuka):
        print("Film {}, preporuka {}".format(naziv,preporuka))

    # Kontrola toka: Ispisi Max -> Ispisi Recenzije
    # {
    @Rule(
        AS.faza << Faza("Ispisi Max"),
        salience = -10
    )
    def kontrola_iz_max_ispis_u_max_recenzije(self,faza):
        self.retract(faza)
        self.declare(Faza("Ispisi Recenzije"))
    # }

    # Ispis recenzija filma sa najvecom preporukom
    @Rule(
        Faza("Ispisi Recenzije"),
        MaxFilm(naziv = MATCH.naziv),
        Recenzija(naziv_filma = MATCH.naziv, tekst_recenzije = MATCH.tekst, ocena = MATCH.ocena)
    )
    def recenzije_ispis(self,naziv,tekst,ocena):
        print("Recenzija - naziv filma: {}, tekst: {}, ocena: {}".format(naziv,tekst,ocena))
    
    # Kontrola toka: Ispisi Recenzije -> Poslednja
    # {
    @Rule(
        AS.faza << Faza("Ispisi Recenzije"),
        salience = -10
    )
    def kontrola_iz_max_recenzije_u_poslednja(self,faza):
        self.retract(faza)
        self.declare(Faza("Poslednja"))
    # }

    # Brisanje ispisanog filma i reset MaxFilm-a
    @Rule(
        Faza("Poslednja"),
        AS.max << MaxFilm(naziv = MATCH.naziv, counter = MATCH.counter),
        AS.film << Film(naziv = MATCH.naziv)
    )
    def poseldnja(self,film,max,counter):
        self.retract(film)
        self.modify(max, naziv = "", preporuka = -1.0, counter = counter - 1)

    # Kontrola toka: Ispisi Max -> Ispisi Recenzije
    # {
    @Rule(
        AS.faza << Faza("Poslednja"),
        MaxFilm(counter = P(lambda x: x > 0)),
        salience = -10
    )
    def kontrola_iz_poslednja_u_max(self,faza):
        self.retract(faza)
        self.declare(Faza("Max"))
    # }

engine = Engine()
engine.reset()
engine.run()
