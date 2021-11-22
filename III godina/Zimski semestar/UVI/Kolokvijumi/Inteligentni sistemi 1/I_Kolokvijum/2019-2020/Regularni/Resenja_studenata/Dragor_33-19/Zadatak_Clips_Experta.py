from experta import *
from experta.utils import freeze
import schema

def e_print(engine: KnowledgeEngine):
    print(engine.facts)
    print(engine.agenda)

class Faza(Fact):
    pass

class Putnik(Fact):
    ime                 = Field(str,                                    True)
    drzava_porekla      = Field(str,                                    True)
    broj_godina         = Field(lambda x: isinstance(x, int) and x > 0, True)
    sadrzaj_torbe       = Field(list)
    ima_dosije          = Field(schema.Or("DA", "NE"),                  True)
    procena_rizika      = Field(lambda x: x >= 0 and x <= 1,            False,  0.5)
    
    potvrda             = Field(list, False, freeze([]))


class MyEngine(KnowledgeEngine):

    @DefFacts()
    def init(self):
        yield Putnik(ime = "Pera", drzava_porekla = "Iran",     broj_godina = 33, ima_dosije = "NE", sadrzaj_torbe = ["noz"])
        yield Putnik(ime = "Mika", drzava_porekla = "Libija",   broj_godina = 51, ima_dosije = "DA", sadrzaj_torbe = [])
        yield Putnik(ime = "Laza", drzava_porekla = "Kanada",   broj_godina = 23, ima_dosije = "DA", sadrzaj_torbe = ["kamen"])
        yield Putnik(ime = "Zika", drzava_porekla = "Srbija",   broj_godina = 27, ima_dosije = "NE", sadrzaj_torbe = ["noz"])
        yield Putnik(ime = "Mumb", drzava_porekla = "Nigerija", broj_godina = 17, ima_dosije = "DA", sadrzaj_torbe = ["pistolj"])

        yield Fact(max_rizik = -1, max_ime = "")
        yield Faza("ip")



    # [1] Inicijalna provera (ip)

    # Sa dosijeom
    @Rule(
        Faza("ip"),
        AS.p << Putnik(ima_dosije = "DA", procena_rizika = MATCH.riz, potvrda = MATCH.pot),
        TEST(lambda pot: pot.count("ip_dosije") == 0)
    )
    def ip_dosije(self, p, riz, pot):
        # print("ip_dosije: {}".format(p["ime"])) # DEBUG
        self.modify(p, procena_rizika = 1 if riz + 0.2 > 1 else riz + 0.2, potvrda = list(pot) + ["ip_dosije"])


    # Iz Libije ili Irana
    @Rule(
        Faza("ip"),
        AS.p << Putnik(drzava_porekla = L("Libija") | L("Iran"), procena_rizika = MATCH.riz, potvrda = MATCH.pot),
        TEST(lambda pot: pot.count("ip_libija_iran") == 0)
    )
    def ip_libija_iran(self, p, riz, pot):
        # print("ip_libija_iran: {}".format(p["ime"])) # DEBUG
        self.modify(p, procena_rizika = 1 if riz + 0.25 > 1 else riz + 0.25, potvrda = list(pot) + ["ip_libija_iran"])

    
    # Nije iz Nigerije
    @Rule(
        Faza("ip"),
        AS.p << Putnik(drzava_porekla = ~(L("Libija") | L("Iran") | L("Nigerija")), procena_rizika = MATCH.riz, potvrda = MATCH.pot),
        TEST(lambda pot: pot.count("ip_nije_nigerija") == 0)
    )
    def ip_nije_nigerija(self, p, riz, pot):
        # print("ip_nije_nigerija: {}".format(p["ime"])) # DEBUG
        self.modify(p, procena_rizika = 0 if riz - 0.1 < 0 else riz - 0.1, potvrda = list(pot) + ["ip_nije_nigerija"])

    
    # Dovoljno star/mlad
    @Rule(
        Faza("ip"),
        AS.p << Putnik(broj_godina = MATCH.god, procena_rizika = MATCH.riz, potvrda = MATCH.pot),
        TEST(lambda pot, god: (god < 18 or god > 50) and pot.count("ip_starost") == 0)
    )
    def ip_starost(self, p, riz, pot):
        # print("ip_starost: {}".format(p["ime"])) # DEBUG
        self.modify(p, procena_rizika = 0 if riz - 0.15 < 0 else riz - 0.15, potvrda = list(pot) + ["ip_starost"])
    
    

    # [2] Ispis rizicnih (ir)

    @Rule(
        Faza("ir"),
        Putnik(ime = MATCH.ime, procena_rizika = MATCH.riz),
        TEST(lambda riz: riz > 0.5)
    )
    def ir_ispis(self, ime, riz):
        print("{}, rizik: {}".format(ime, riz))

    

    # [3] Pregled torbi (pt)
    
    @Rule(
        Faza("pt"),
        AS.p << Putnik(ime = MATCH.ime, procena_rizika = MATCH.riz, sadrzaj_torbe = MATCH.tor),
        TEST(lambda riz, tor: riz > 0.5 and (tor.count("noz") > 0 or tor.count("pistolj") > 0))
    )
    def pt_pregled(self, ime, p):
        print("izbacuje se: {}".format(ime))
        self.retract(p)

    
    
    # [4] Analiza rizika (ar)

    @Rule(
        Faza("ar"),
        AS.mr << Fact(max_rizik = MATCH.max),
        Putnik(ime = MATCH.ime, procena_rizika = MATCH.riz),
        TEST(lambda riz, max: riz > max)
    )
    def ar_novi_max(self, riz, ime, mr):
        # print("novi max: {} {}".format(ime, riz)) # DEBUG
        self.modify(mr, max_rizik = riz, max_ime = ime)

    
    @Rule(
        Faza("ar"),
        Fact(max_ime = MATCH.ime),
        salience = -1
    )
    def ar_ispis(self, ime):
        print("Najrizicniji: {}".format(ime))


    
    # KONTROLA TOKA

    # Inicijalna provera -> Ispis rizicnih
    @Rule(
        AS.f << Faza("ip"),
        salience = -1
    )
    def ip_ir(self, f):
        self.retract(f)
        self.declare(Faza("ir"))

    
    # Ispis rizicnih -> Pregled torbi
    @Rule(
        AS.f << Faza("ir"),
        salience = -1
    )
    def ir_pt(self, f):
        self.retract(f)
        self.declare(Faza("pt"))

    
    # Pregled torbi -> Analiza rizika
    @Rule(
        AS.f << Faza("pt"),
        salience = -1
    )
    def pt_ar(self, f):
        self.retract(f)
        self.declare(Faza("ar"))



# MAIN

engine = MyEngine()
engine.reset()

# e_print(engine) # DEBUG

engine.run()

# e_print(engine) # DEBUG
