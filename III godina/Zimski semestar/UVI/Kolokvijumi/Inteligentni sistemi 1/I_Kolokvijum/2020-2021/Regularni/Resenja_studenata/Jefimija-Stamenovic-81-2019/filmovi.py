from types import prepare_class
from experta import *
import schema
import re
class Film(Fact): 
    naziv = Field(str, mandatory=True)
    reziser = Field(str, default="/")
    kategorija = Field(schema.Or("AKCIJA", "DRAMA", "HOROR", "TRILER", 
                    "NAUCNA_FANTASTIKA", "KOMEDIJA"), mandatory=True)
    opis = Field(str)
    datum_premijere             = Field(lambda x: re.compile(r'[0-9]{4}-[0-9]{2}-[0-9]{2}'))
    lista_glumaca               = Field(list)
    duzina_trajanja             = Field(float)
    preporuka                   = Field(float, default=50)

    obradjen_prosek             = Field(bool, default=False)
    obradjen_omiljeni_film      = Field(bool, default=False)
    obradjena_ista_kategorija   = Field(bool, default=False)
    obradjena_srodna_kategorija = Field(bool, default=False)
    obradjeno_nema_nagradu      = Field(bool, default=False)
    obradjeno_reditelj_glumac   = Field(bool, default=False)
    obradjeno_triler_komedija   = Field(bool, default=False)
    obradjen_reditelj           = Field(bool, default=False)
    obradjen_max                = Field(int, default=0)
    rangiran                    = Field(bool, default=False)
class Brojac(Fact): 
    vrednost = Field(int, default=1)
class SrodneKategorije(Fact): 
    naziv_prve_kategorije = Field(str, mandatory=True)
    naziv_druge_kategorije = Field(str, mandatory=True)

class Recenzija(Fact): 
    naziv_filma = Field(str, mandatory=True)
    tekst_recenzije = Field(str)
    ocena = Field(lambda x: isinstance(x,int) and 0<=x<=10, mandatory=True)
    obradjena = Field(bool, default=False)
    stampana = Field(bool, default=False)

class FilmskaNagrada(Fact): 
    naziv_filma = Field(str, mandatory=True)
    nagrada = Field(schema.Or("ZLATNA_PALMA", "OSKAR", "ZLATNI_LAV"), mandatory=True)
    obradjena = Field(bool, default=False)

class Faza(Fact): 
    pass 

class Korisnik(Fact): 
    omiljeni_film = Field(str, mandatory=True)
    omiljena_kategorija = Field(str, mandatory=True)
    omiljeni_glumac =  Field(str, mandatory=True)
    nepozeljna_kategorija =  Field(str, mandatory=True)

class ProsecnaOcena(Fact): 
    naziv_filma =  Field(str, mandatory=True)
    suma = Field(int, default=0)
    brojac = Field(int, default=0)
    ocena = Field(float, default=0)

class Max(Fact): 
    naziv_filma = Field(str)
    preporuka   = Field(float, default=0)
    stampan = Field(bool, default=False)
class Engine(KnowledgeEngine): 
    
    @DefFacts()
    def ucitaj(self): 
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
        yield Recenzija(naziv_filma = "E", tekst_recenzije = "Ocena za E...", ocena = 6)
        yield Recenzija(naziv_filma = "E", tekst_recenzije = "Ocena za E...", ocena = 7)
        
        yield Recenzija(naziv_filma = "F", tekst_recenzije = "Ocena za F...", ocena = 10)
        yield Recenzija(naziv_filma = "F", tekst_recenzije = "Ocena za F...", ocena = 9)
        yield Recenzija(naziv_filma = "F", tekst_recenzije = "Ocena za F...", ocena = 9)

        yield FilmskaNagrada(naziv_filma = "A", nagrada = "ZLATNA_PALMA")
        yield FilmskaNagrada(naziv_filma = "B", nagrada = "OSKAR")
        yield FilmskaNagrada(naziv_filma = "C", nagrada = "ZLATNI_LAV")

        yield Faza('faza-korisnik')

    @Rule(
        Faza('faza-korisnik')
    )
    def ucitaj_podatke_korisnika(self):
        print("FAZA: Korisnik...") 
        print("=========================================")
        omiljeni_film = input("Unesite omiljeni film: ")
        omiljena_kategorija = input("Unesite omiljenu kategoriju: ")
        omiljeni_glumac = input("Unesite omiljenog glumca: ")
        nepozeljna_kategorija = input("Unesite kategoriju koju ne volite: ")
        self.declare(Korisnik( omiljeni_film = omiljeni_film, 
                               omiljena_kategorija = omiljena_kategorija, 
                               omiljeni_glumac = omiljeni_glumac, 
                               nepozeljna_kategorija = nepozeljna_kategorija
                    ))
        print("=========================================")

    @Rule(
        Faza('faza-korisnik'), 
        Korisnik(nepozeljna_kategorija = MATCH.kategorija), 
        AS.film << Film(naziv = MATCH.naziv, kategorija = MATCH.kategorija)
    )
    def obrisi_filmove_iz_nepozeljne_kategorije(self, film, naziv): 
        print("FAZA: Korisnik...") 
        print("=========================================")
        print("Brisem film {}" . format(naziv))
        self.retract(film)
        print("=========================================")


    
#------------------------------------------------------------------------------------------#   
    @Rule(
        AS.faza << Faza('faza-korisnik'), 
        salience=-10
    )
    def faza_recenzije(self, faza): 
        print("=========================================")
        print("Zavrsena faza korisnika...") 
        print("Prelazim na fazu recenzije")
        self.retract(faza)
        self.declare(Faza('faza-recenzije'))
        print("=========================================")
     
    @Rule(
        Faza('faza-recenzije'), 
        Korisnik(omiljeni_film = MATCH.naziv_filma), 
        NOT(Recenzija(uneo_korisnik = True))
    )
    def unos_korisnicke_recenzije(self, naziv_filma): 
        print("FAZA: Recenzije... ")
        print("=========================================")
        ocena = int(input("Unesite recenziju za omiljeni film: "))
        tekst_recenzije = input("Unesite tekst: ")
        self.declare(Recenzija(
            naziv_filma=naziv_filma, 
            tekst_recenzije=tekst_recenzije, 
            ocena=ocena, 
            uneo_korisnik=True
        ))
    
    @Rule(
        Faza('faza-recenzije'), 
        Recenzija(uneo_korisnik = True), 
        Film(naziv=MATCH.naziv_filma), 
        NOT(ProsecnaOcena(naziv_filma=MATCH.naziv_filma))
    )
    def dodavanje_prosecnih_ocena(self, naziv_filma): 
        print("FAZA: Recenzije...")
        print("=========================================")
        print("Kreiram prosecnu ocenu za film {}...".format(naziv_filma))
        self.declare(ProsecnaOcena(naziv_filma = naziv_filma))

    @Rule(
        Faza('faza-recenzije'), 
        Film(naziv = MATCH.naziv_filma), 
        AS.prosecna_ocena << ProsecnaOcena(naziv_filma=MATCH.naziv_filma, 
                                       suma=MATCH.suma,
                                       brojac=MATCH.brojac),
        AS.recenzija << Recenzija(naziv_filma = MATCH.naziv_filma, 
                                ocena = MATCH.ocena, 
                                obradjena = False)
    )
    def azuriranje_prosecnih_ocena(self, naziv_filma, prosecna_ocena, recenzija,
                                suma, ocena, brojac): 
        print("FAZA: Recenzije...")
        print("=========================================")
        print("Azuriram prosecnu ocenu za film {}...".format(naziv_filma))
        self.modify(prosecna_ocena, suma = suma+ocena, brojac = brojac+1)
        self.modify(recenzija, obradjena = True)

    @Rule(
        Faza('faza-recenzije'),
        AS.prosecna_ocena << ProsecnaOcena(naziv_filma=MATCH.naziv_filma, 
                                       suma=MATCH.suma,
                                       brojac=MATCH.brojac, 
                                       ocena = MATCH.prosek & P(lambda prosek: prosek == 0)), 
        NOT(Recenzija(naziv_filma = MATCH.naziv_filma, 
                      obradjena = False)), 
    )
    def racunanje_prosecnih_ocena(self, prosecna_ocena, naziv_filma, suma, brojac): 
        prosek = suma/brojac 
        self.modify(prosecna_ocena, ocena = prosek)
        print("Prosecna ocena za film {} je {}".format(naziv_filma, prosek))
#------------------------------------------------------------------------------------------#    
    @Rule(
        AS.faza << Faza('faza-recenzije'), 
        salience=-10
    )
    def faza_preporuke(self, faza): 
        print("=========================================")
        print("Zavrsena faza recenzija...") 
        print("Prelazim na fazu preporuka")
        self.retract(faza)
        self.declare(Faza('faza-preporuke'))
        print("=========================================")

    @Rule(
        AS.faza << Faza('faza-preporuke'),  
        AS.film << Film(naziv = MATCH.naziv_filma, preporuka = MATCH.preporuka, obradjen_prosek = False), 
        ProsecnaOcena(naziv_filma = MATCH.naziv_filma, ocena = MATCH.prosek & P(lambda prosek: prosek>=5))
    )
    def povecanje_preporuke_prosek(self, film, naziv_filma, preporuka, prosek): 
        print("Naziv filma {} Preporuka {} Prosek {}".format(naziv_filma,preporuka,prosek))
        print("Povecavam preporuku...")
        self.modify(film, preporuka = preporuka+prosek, obradjen_prosek = True)

    @Rule(
        AS.faza << Faza('faza-preporuke'),  
        AS.film << Film(naziv = MATCH.naziv_filma, preporuka = MATCH.preporuka, obradjen_prosek = False), 
        ProsecnaOcena(naziv_filma = MATCH.naziv_filma, ocena = MATCH.prosek & P(lambda prosek: prosek<5))
    )
    def smanjenje_preporuke_prosek(self, film,naziv_filma, preporuka, prosek): 
        print("Naziv filma {} Preporuka {} Prosek {}".format(naziv_filma,preporuka,prosek))
        print("Smanjujem preporuku...")
        self.modify(film, preporuka = preporuka-prosek, obradjen_prosek = True)

    @Rule(
        Faza('faza-preporuke'), 
        Korisnik(omiljeni_film = MATCH.naziv_filma1), 
        ProsecnaOcena(naziv_filma = MATCH.naziv_filma1, ocena = MATCH.prosek1),
        AS.film << Film(naziv = MATCH.naziv_filma2 & ~MATCH.naziv_filma1,
                        preporuka = MATCH.preporuka, 
                        obradjen_omiljeni_film = False), 
        ProsecnaOcena(naziv_filma = MATCH.naziv_filma2, ocena = MATCH.prosek2), 
        TEST(lambda prosek1, prosek2: prosek1<prosek2)
    )
    def veci_prosek_od_omiljenog_filma(self, naziv_filma1, naziv_filma2, film,
                                    preporuka): 
        print("Film {} ima veci prosek od {}".format(naziv_filma2,naziv_filma1))
        print("Uvecavam preporuku...")
        print("-----------------------")
        self.modify(film, preporuka = preporuka+5.0, obradjen_omiljeni_film = True)
    
    @Rule(
        Faza('faza-preporuke'), 
        Korisnik(omiljeni_film = MATCH.naziv_filma1, omiljena_kategorija = MATCH.kategorija),
        AS.film << Film(naziv = MATCH.naziv_filma2 & ~MATCH.naziv_filma1,
                        kategorija = MATCH.kategorija, 
                        preporuka = MATCH.preporuka, 
                        obradjena_ista_kategorija = False)
    )
    def iste_kategorije(self, naziv_filma1, naziv_filma2, film,
                                    preporuka): 
        print("Film {} i {} su u istoj kategoriji ".format(naziv_filma2,naziv_filma1))
        print("Uvecavam preporuku...")
        print("-----------------------")
        self.modify(film, preporuka = preporuka+10.0, obradjena_ista_kategorija = True)
    
    @Rule(
        Faza('faza-preporuke'), 
        SrodneKategorije(naziv_prve_kategorije = MATCH.prva_kategorija, 
                        naziv_druge_kategorije = MATCH.druga_kategorija),
        Korisnik(omiljeni_film = MATCH.naziv_filma1, omiljena_kategorija = MATCH.kategorija1 & (MATCH.prva_kategorija | MATCH.druga_kategorija)),
        AS.film << Film(naziv = MATCH.naziv_filma2 & ~MATCH.naziv_filma1,
                        kategorija = MATCH.kategorija2 & ~MATCH.kategorija1 & (MATCH.prva_kategorija | MATCH.druga_kategorija), 
                        preporuka = MATCH.preporuka, 
                        obradjena_srodna_kategorija = False)
    )
    def slicne_kategorije(self, film, prva_kategorija, druga_kategorija, naziv_filma1, naziv_filma2, preporuka):
        print("=========================================")
        print("Slicne filmove: {} {} u slicnim kategorijama : {} {} ".format(naziv_filma1, naziv_filma2, prva_kategorija,druga_kategorija))
        self.modify(film, preporuka = preporuka+5.0, obradjena_srodna_kategorija = True)
        print("Uvecavam preporuku...")
        print("=========================================")
#------------------------------------------------------------------------------------------#
    @Rule(
        AS.faza << Faza('faza-preporuke'), 
        salience=-10
    )
    def faza_filmskih_nagrada(self, faza): 
        print("=========================================")
        print("Zavrsena faza preporuka...") 
        print("Prelazim na fazu filmskih nagrada")
        self.retract(faza)
        self.declare(Faza('faza-filmske-nagrade'))
        print("=========================================")

    @Rule(
        Faza('faza-filmske-nagrade'),
        AS.nagrada << FilmskaNagrada(naziv_filma = MATCH.naziv_filma, 
                                    nagrada = MATCH.naziv_nagrade, 
                                    obradjena=False), 
        AS.film << Film (naziv = MATCH.naziv_filma,
                        preporuka = MATCH.preporuka)
    )
    def obrada_nagrada(self, film, nagrada, naziv_filma, naziv_nagrade,preporuka): 
        print("=========================================")
        print("{} ima nagradu {}... Uvecavam preporuku za 2" .format(naziv_filma, naziv_nagrade))
        self.modify(nagrada, obradjena=True)
        self.modify(film, preporuka = preporuka+2.0)
        print("=========================================")

    @Rule(
        Faza('faza-filmske-nagrade'),
        AS.film << Film (naziv = MATCH.naziv_filma, preporuka = MATCH.preporuka, obradjeno_nema_nagradu=False),
        NOT(FilmskaNagrada(naziv_filma = MATCH.naziv_filma))
    )
    def obrada_filma_bez_nagrade(self, film, naziv_filma, preporuka): 
        print("{} nema nagradu i smanjujem preporuku za 7".format(naziv_filma))
        self.modify(film, preporuka=preporuka-7, obradjeno_nema_nagradu=True)

    #Ако постоји филм у којем игра омиљени глумац, режирао га је исти редитељ као и редитељ омиљеног филма, онда том филму увећати препоруку за 10
    @Rule(
        Faza('faza-filmske-nagrade'),
        Korisnik(omiljeni_film = MATCH.omiljeni_film, omiljeni_glumac = MATCH.glumac), 
        Film(naziv=MATCH.omiljeni_film, reziser=MATCH.reziser), 
        AS.film << Film(naziv = MATCH.naziv_filma & ~MATCH.omiljeni_film,
                        reziser = MATCH.reziser,
                        lista_glumaca = MATCH.glumci,  
                        preporuka = MATCH.preporuka, 
                        obradjen_reditelj=False), 
        TEST(lambda glumac, glumci: glumac in glumci)
    )
    def obrada_glumca_i_reditelja(self, film, omiljeni_film, naziv_filma, reziser, preporuka): 
        print("=========================================================================================")
        print("Filmovi {} i {} imaju istog reditelja {}".format(omiljeni_film, naziv_filma, reziser))
        self.modify(film, preporuka=preporuka+10.0, obradjen_reditelj=True)

    #Независно од афинитета гледаоца, свим филмовима који су типа KOMEDIJA или TRILER, а
    #притом трају мање од 3 сата, увећати препоруку за 5.
    @Rule(
        Faza('faza-filmske-nagrade'),
        AS.film << Film (naziv = MATCH.naziv_filma, 
                        kategorija = MATCH.kategorija & (L("KOMEDIJA") | L("TRILER")), 
                        preporuka = MATCH.preporuka, 
                        duzina_trajanja = MATCH.trajanje & P(lambda x : x<3.0),
                        obradjeno_triler_komedija = False
        )
    )
    def nema_nagradu(self, film, preporuka, naziv_filma, kategorija):
        print("=========================================================================================")
        print("Film {} pripada kategoriji {}... Uvecavam preporuku..." .format(naziv_filma,kategorija)) 
        self.modify(film, preporuka = preporuka+5, obradjeno_triler_komedija = True)
        print("=========================================================================================")

#------------------------------------------------------------------------------------------#
    @Rule(
        AS.faza << Faza('faza-filmske-nagrade'), 
        salience=-10
    )
    def faza_rangiranja(self, faza): 
        print("=========================================")
        print("Zavrsena faza filmskih nagrada...") 
        print("Prelazim na fazu rangiranja")
        self.retract(faza)
        self.declare(Faza('faza-rangiranje'))
        self.declare(Brojac())
        print("=========================================")

    @Rule(
        AS.faza << Faza('faza-rangiranje'),
        NOT(Max()), 
        Brojac(vrednost=MATCH.brojac)
    )   
    def kreiraj_max(self, brojac):
        #print("Kreiram {}. max: ". format(brojac))
        self.declare(Max())

    @Rule(
        Faza('faza-rangiranje'), 
        Korisnik(omiljeni_film=MATCH.omiljeni_film),
        Brojac(vrednost=MATCH.brojac),
        AS.max << Max(preporuka=MATCH.preporuka_max),
        Film(naziv=MATCH.naziv_filma & ~MATCH.omiljeni_film,
            preporuka=MATCH.preporuka, obradjen_max=MATCH.obradjen_max & ~MATCH.brojac, rangiran=False),
        TEST(lambda preporuka, preporuka_max : preporuka_max<preporuka)
    )
    def azuriraj_max(self, max, naziv_filma, preporuka): 
        #print("Azuriram max {} {}".format(naziv_filma,preporuka))
        self.modify(max, naziv_filma=naziv_filma, preporuka=preporuka)

    @Rule(
        Faza('faza-rangiranje'), 
        Korisnik(omiljeni_film=MATCH.omiljeni_film),
        Brojac(vrednost=MATCH.brojac),
        Max(preporuka=MATCH.preporuka_max),
        AS.film << Film(naziv=MATCH.naziv_filma,
            preporuka=MATCH.preporuka, obradjen_max=MATCH.obradjen_max &~MATCH.brojac),
        TEST(lambda preporuka, preporuka_max : preporuka_max>=preporuka)
    )
    def setovanje_brojaca(self,naziv_filma,film,brojac): 
        #print("Setujem brojac {} na {}".format(naziv_filma, brojac))
        self.modify(film, obradjen_max=brojac)

    @Rule(
        Faza('faza-rangiranje'),
        Brojac(vrednost=MATCH.brojac),
        NOT(Film(obradjen_max=MATCH.obradjen_max &~MATCH.brojac, rangiran=False)), 
        AS.max<<Max(naziv_filma=MATCH.naziv_filma, preporuka=MATCH.preporuka, stampan=False)
    )
    def stampanje_max(self, max, naziv_filma, preporuka, brojac): 
        print("{}. Film {} Preporuka {}".format(brojac, naziv_filma, preporuka))
        self.modify(max, stampan=True)
    @Rule(
        Faza('faza-rangiranje'),
        Max(stampan=True,naziv_filma=MATCH.naziv_filma),
        AS.recenzija<<Recenzija(naziv_filma=MATCH.naziv_filma, tekst_recenzije=MATCH.tekst, stampana=False)
    )
    def stampanje_recenzija(self, recenzija, tekst):
        print("Recenzija : {}".format(tekst))
        self.modify(recenzija, stampana=True)
    
    @Rule(
        Faza('faza-rangiranje'),
        AS.max<<Max(stampan=True,naziv_filma=MATCH.naziv_filma),
        AS.film<<Film(naziv=MATCH.naziv_filma),
        AS.brojac<<Brojac(vrednost=MATCH.vrednost & P(lambda x: x<3)),
        NOT(Recenzija(naziv_filma=MATCH.naziv_filma, tekst_recenzije=MATCH.tekst, stampana=False))
    )
    def novi_krug(self,max,brojac,vrednost,film):
        #print("Zapocinjem novi krug...")
        self.modify(brojac, vrednost=vrednost+1)
        self.modify(film, rangiran=True)
        self.retract(max)

engine  = Engine()
engine.reset()
engine.run()