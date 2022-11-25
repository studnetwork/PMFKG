from experta import *
import schema 
import re

class Putnik(Fact): 
    ime = Field(str)
    drzava_porekla = Field(str)
    broj_godina = Field(int)
    sadrzaj_torbe = Field(list)
    ima_dosije = Field(schema.Or("DA", "NE"))
    procena_rizika = Field(lambda x: isinstance(x, float) & (0<=x<=1), default=0.5)
    dodato_za_dosije = Field(bool, default = False)
    dodato_za_zemlju = Field(bool, default = False)
    smanjeno_zbog_zemlje = Field(bool, default = False)
    smanjeno_zbog_godina = Field(bool, default = False)
    odstampan = Field(bool, default = False)

class Engine(KnowledgeEngine): 

    @DefFacts()
    def ucitaj_cinjenice(self): 
        yield Putnik(ime = "Muhamed", drzava_porekla = "Libija", broj_godina = 20, sadrzaj_torbe = ["noz"], 
        ima_dosije = "DA") 
        yield Putnik(ime = "Osman", drzava_porekla = "Iran", broj_godina = 16, sadrzaj_torbe = ["pistolj"], 
        ima_dosije = "NE") 
        yield Putnik(ime = "Danilo", drzava_porekla = "Srbija", broj_godina = 22, sadrzaj_torbe = ["pistolj"], 
        ima_dosije = "NE") 
        yield Putnik(ime = "Julija", drzava_porekla = "Crna Gora", broj_godina = 14, sadrzaj_torbe = ["karmin"], 
        ima_dosije = "NE") 
        yield Putnik(ime = "Jovan", drzava_porekla = "Srbija", broj_godina = 19, sadrzaj_torbe = ["pistolj", "noz"], 
        ima_dosije = "NE") 
    @Rule(
        AS.putnik << Putnik(ime = MATCH.ime, ima_dosije = "DA", 
                            dodato_za_dosije = False, procena_rizika = MATCH.rizik)
    )
    def nadjiPutnikeSaDosijeom(self, ime, putnik, rizik): 
        print("Putnik {} ima dosije".format(ime))
        self.modify(putnik, dodato_za_dosije = True, procena_rizika = rizik + 0.2)

    @Rule(
        AS.putnik << Putnik(ime = MATCH.ime, dodato_za_zemlju = False, procena_rizika = MATCH.rizik, 
                    drzava_porekla = MATCH.drzava & (L('Libija') | L('Iran')))
    )
    def nadjiPutnikeIzLibijeIIrana(self, putnik, ime, rizik, drzava):
        print("Putnik {} dolazi iz drzave {}".format(ime, drzava)) 
        self.modify(putnik, dodato_za_zemlju = True, procena_rizika = rizik + 0.25)

    @Rule(
        AS.putnik << Putnik(ime = MATCH.ime, smanjeno_zbog_zemlje = False, procena_rizika = MATCH.rizik, 
                    drzava_porekla = MATCH.drzava & ~(L('Libija') | L('Iran') | L('Nigerija')))
    )
    def nadjiPutnikeKojiSuSigurni(self, putnik, ime, rizik, drzava): 
        print("Putnik {} dolazi iz drzave {} i nije iz Nigerije, Libije ili Irana".format(ime, drzava)) 
        self.modify(putnik, smanjeno_zbog_zemlje = True, procena_rizika = rizik - 0.1)

    @Rule(
        AS.putnik << Putnik(ime = MATCH.ime, smanjeno_zbog_godina = False, procena_rizika = MATCH.rizik,
                            broj_godina = MATCH.godine & P(lambda godine: (godine<18) or (godine>50)))
    )
    def nadjiPutnikeGodine(self, putnik, ime, rizik, godine): 
        print("Putnik {} je ispunio uslov za godine. Godine : {}".format(ime, godine)) 
        self.modify(putnik, smanjeno_zbog_godina = True, procena_rizika = rizik - 0.15)

    @Rule(
        salience = -10
    )
    def predjiNaStampanjeKoraka(self): 
        self.declare(Fact('stampanje-rizicnih'))

    @Rule(
        Fact('stampanje-rizicnih'), 
        AS.putnik << Putnik(ime = MATCH.ime, procena_rizika = MATCH.rizik & P(lambda rizik: rizik>0.5), 
                            odstampan = False)
    )
    def stampajRizicnog(self, putnik, ime, rizik): 
        print("Putnik : {} => Rizik : {}".format(ime, rizik))
        self.modify(putnik, odstampan = True)

    @Rule(
        AS.faza << Fact('stampanje-rizicnih'),
        NOT(Putnik(odstampan = False, procena_rizika = MATCH.rizik & P(lambda rizik: rizik >0.5)))
    )
    def fazaProveraTorbi(self, faza): 
        self.retract(faza)
        self.declare(Fact('provera-torbi'))

    @Rule(
        Fact('provera-torbi'), 
        AS.putnik << Putnik(ime = MATCH.ime, procena_rizika = MATCH.rizik & P(lambda rizik: rizik >0.5), 
        sadrzaj_torbe = MATCH.torba), 
        OR(
            TEST(lambda torba: "noz" in torba), 
            TEST(lambda torba: "pistolj" in torba)
        )
    )
    def ukloniPutnika(self, putnik, ime): 
        print("Putnik {} ima noz/pistolj. Izbacujem ga".format(ime))
        self.retract(putnik)

    @Rule(
        AS.faza << Fact('provera-torbi'), 
        NOT(
            AS.putnik << Putnik(ime = MATCH.ime, procena_rizika = MATCH.rizik & P(lambda rizik: rizik >0.5), 
            sadrzaj_torbe = MATCH.torba), 
            OR(
                TEST(lambda torba: "noz" in torba), 
                TEST(lambda torba: "pistolj" in torba)
            )
        )
    )
    def nemaRizicnih(self, faza): 
        self.retract(faza)
        self.declare(Fact(max_rizik = 0))

    @Rule(
        AS.max << Fact(max_rizik = MATCH.max_rizik), 
        Putnik(procena_rizika = MATCH.rizik), 
        TEST(lambda rizik, max_rizik: max_rizik < rizik)
    )
    def nadjenNoviMax(self, max, rizik): 
        self.modify(max, max_rizik = rizik)

    @Rule(
        Fact(max_rizik = MATCH.max_rizik),
        Putnik(ime = MATCH.ime, procena_rizika = MATCH.max_rizik), 
        salience = -10
    )
    def stampajNajrizicnijeg(self, ime, max_rizik): 
        print("Najrizicniji putnik je {} sa procenom rizika {}".format(ime,max_rizik))

engine = Engine()
engine.reset()
engine.run()