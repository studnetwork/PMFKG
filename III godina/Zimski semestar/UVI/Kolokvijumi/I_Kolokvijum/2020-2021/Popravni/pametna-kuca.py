from experta import *
import schema 
import re 

class Zgrada(Fact): 
    tip = Field(schema.Or("KUCA", "POMOCNI_OBJEKAT"))
    adresa = Field(str)
    pametni_uredjaji = Field(list)

class PametniUredjaj(Fact): 
    ip_adresa = Field(lambda x : isinstance(x, str) and re.match(r'[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}', x))

class ElektricniSporet(PametniUredjaj): 
    ukljucena_ringla_1 = Field(bool, default = False)
    ukljucena_ringla_1 = Field(bool, default = False)
    ukljucena_ringla_3 = Field(bool, default = False)
    ukljucena_ringla_4 = Field(bool, default = False)

class Bazen(PametniUredjaj):
    temperatura_vode = Field(float)
    grejanje = Field(bool, default = False)

class Vlasnik(Fact):
    ime = Field(str)
    adresa = Field(str)

class VremenskiUslovi(Fact): 
    stanje = Field(schema.Or("SUNCANO", "KISA", "OBLACNO"))

class Kamera(PametniUredjaj): 
    ukljucena = Field(bool, default = False)
    lokacija = Field(str)

class Kretanje(Fact): 
    lokacija = Field(str)

class Alarm(Fact): 
    ukljucen = Field(bool, default = False)

class Prostorija(Fact): 
    naziv = Field(str)
    temperatura = Field(float, default = 15)

class IzmenjivacToplote(PametniUredjaj): 
    max_temp = Field(float)
    min_temp = Field(float)
    avg_temp = Field(float)

class GaraznaVrata(PametniUredjaj): 
    otvorena = Field(bool, default = False)

class Auto(Fact): 
    pass 

class Log(Fact): 
    ip_adresa = Field(str)
    poruka = Field(str)

class Engine(KnowledgeEngine):

    @DefFacts()
    def loadFacts(self): 
        yield Vlasnik(ime = "Pera", adresa = "Daniciceva")
        yield Zgrada(tip = "KUCA", adresa = "Radoja Domanovica", pametni_uredjaji = 
        ["89.120.24.162", "89.120.25.203", "89.120.20.462", "89.5.20.23", "89.6.20.6", "75.35.56.2", "89.23.2.3"])
        yield ElektricniSporet(ip_adresa = "89.120.24.162", ukljucena_ringla_1 = True, 
        ukljucena_ringla_2 = False, ukljucena_ringla_3 = False, ukljucena_ringla_4 = True)
        yield Bazen(ip_adresa = "89.120.25.203", temperatura_vode = 16.5, grejanje = False)
        yield VremenskiUslovi(stanje = "KISA")
        yield Kretanje(lokacija = "DNEVNA_SOBA")
        yield Kamera(ip_adresa = "89.120.20.462", ukljucena = True, lokacija = "DNEVNA_SOBA")
        yield Kamera(ip_adresa = "89.5.20.23", ukljucena = True, lokacija = "SPAVACA_SOBA")
        yield Alarm(ip_adresa = "89.6.20.6", ukljucen = False)
        yield Prostorija(naziv = "DNEVNA_SOBA", temperatura = 22.0)
        yield Prostorija(naziv = "SPAVACA_SOBA", temperatura = 25.0)
        yield Prostorija(naziv = "KUPATILO", temperatura = 15.0)
        yield Auto()
        yield GaraznaVrata(ip_adresa = "75.35.56.2", otvorena = False)
        yield IzmenjivacToplote(ip_adresa = "89.23.2.3", min_temp = 1000.0, max_temp = -1000.0, avg_temp = 0.0)

    @Rule(
        Log(poruka = MATCH.poruka, ip_adresa = MATCH.ip_adresa), 
        salience = 10
    )
    def stampajLog(self, poruka, ip_adresa): 
        print("{} : {}".format(ip_adresa, poruka))
    

    @Rule(
        Zgrada(tip = "KUCA", adresa = MATCH.adresa_kuce & MATCH.adresa, pametni_uredjaji = MATCH.uredjaji)
    )
    def broadcastUredjaja(self, uredjaji): 
        for uredjaj in uredjaji: 
            self.declare(Log(poruka = "Pametni uredjaj => Pronadjen", ip_adresa = uredjaj))
            self.declare(PametniUredjaj(ip_adresa = uredjaj))
    
    @Rule(
        Vlasnik(adresa = MATCH.adresa), 
        Zgrada(tip = "KUCA", adresa = MATCH.adresa_kuce & ~MATCH.adresa)
    )
    def vlasnikNijeKuci(self): 
        print("Pametna kuca => Vlasnik nije kuci...")
        self.declare(Fact(prazna_kuca = True))

    @Rule(
        Fact(prazna_kuca = True),
        PametniUredjaj(ip_adresa = MATCH.ip_adresa),
        AS.sporet << ElektricniSporet(ip_adresa = MATCH.ip_adresa),
        OR(
            ElektricniSporet(ip_adresa = MATCH.ip_adresa, ukljucena_ringla_1 = True), 
            ElektricniSporet(ip_adresa = MATCH.ip_adresa, ukljucena_ringla_2 = True),
            ElektricniSporet(ip_adresa = MATCH.ip_adresa, ukljucena_ringla_3 = True),
            ElektricniSporet(ip_adresa = MATCH.ip_adresa, ukljucena_ringla_4 = True)
        )
    )
    def iskljuciSporet(self, sporet, ip_adresa): 
        self.declare(Log(poruka = "Sporet => Iskljucujem ringle", ip_adresa = ip_adresa))
        self.modify(sporet, ukljucena_ringla_1 = False, 
                            ukljucena_ringla_2 = False, 
                            ukljucena_ringla_3 = False, 
                            ukljucena_ringla_4 = False)

    @Rule(
        PametniUredjaj(ip_adresa = MATCH.ip_adresa), 
        AS.bazen << Bazen(ip_adresa = MATCH.ip_adresa, temperatura_vode = MATCH.temp, grejanje = False), 
        TEST(lambda temp: temp<18)
    )
    def zagrejBazen(self, bazen, ip_adresa): 
        self.declare(Log(poruka = "Bazen => Grejem vodu", ip_adresa = ip_adresa))
        self.modify(bazen, grejanje = True)

    @Rule(
        Fact(prazna_kuca = True), 
        PametniUredjaj(ip_adresa = MATCH.ip_adresa_kamere), 
        Kamera(ip_adresa = MATCH.ip_adresa_kamere, ukljucena = True, lokacija = MATCH.lokacija), 
        Kretanje(lokacija = MATCH.lokacija), 
        PametniUredjaj(ip_adresa = MATCH.ip_adresa_alarma), 
        AS.alarm << Alarm(ip_adresa = MATCH.ip_adresa_alarma, ukljucen = False)
    )
    def ukljuciAlarm(self, alarm, ip_adresa_kamere, ip_adresa_alarma, lokacija): 
        self.declare(Log(poruka = "Alarm => Aktiviran sam od strane kamere (IP: {})".format(ip_adresa_kamere), ip_adresa = ip_adresa_alarma))
        self.modify(alarm, ukljucen = True)

    @Rule(
        PametniUredjaj(ip_adresa = MATCH.ip_adresa),
        AS.izmenjivac << IzmenjivacToplote(ip_adresa = MATCH.ip_adresa, max_temp = MATCH.max),
        Prostorija(temperatura = MATCH.temp), 
        TEST(lambda max, temp: temp>max)
    )
    def izmeniMax(self, izmenjivac, temp, ip_adresa): 
        self.declare(Log(poruka = "Izmenjivac temperature => Nasao sam novi max {}".format(temp), ip_adresa = ip_adresa))
        self.modify(izmenjivac, max_temp = temp)

    @Rule(
        PametniUredjaj(ip_adresa = MATCH.ip_adresa),
        AS.izmenjivac << IzmenjivacToplote(ip_adresa = MATCH.ip_adresa, min_temp = MATCH.min),
        Prostorija(temperatura = MATCH.temp), 
        TEST(lambda min, temp: min>temp)
    )
    def izmeniMin(self, izmenjivac, temp, ip_adresa): 
        self.declare(Log(poruka = "Izmenjivac temperature => Nasao sam novi min {}".format(temp), ip_adresa = ip_adresa))
        self.modify(izmenjivac, min_temp = temp)

    @Rule( 
        PametniUredjaj(ip_adresa = MATCH.ip_adresa),
        AS.izmenjivac << IzmenjivacToplote(ip_adresa = MATCH.ip_adresa, max_temp = MATCH.max, min_temp = MATCH.min),
        TEST(lambda max, min: max-min>5),
        salience = -10
    )
    def nasaoSamMaxAndMin(self, max, min, izmenjivac, ip_adresa): 
        avg_temp = ((max+min)/2)
        self.declare(Log(poruka = "Izmenjivac temperature => Nasao sam max : {}, min : {}, avg : {}".format(max,min,avg_temp), ip_adresa = ip_adresa))
        self.modify(izmenjivac, avg_temp = avg_temp)
        self.declare(Fact(podesi_temp = True))

    @Rule(
        AS.faza << Fact(podesi_temp = True), 
        PametniUredjaj(ip_adresa = MATCH.ip_adresa),
        AS.izmenjivac << IzmenjivacToplote(ip_adresa = MATCH.ip_adresa, max_temp = MATCH.max, 
                                           min_temp = MATCH.min, avg_temp = MATCH.avg), 
        AS.max_soba << Prostorija(temperatura = MATCH.max), 
        AS.min_soba << Prostorija(temperatura = MATCH.min)
    )
    def promeniTemp(self, max_soba, min_soba, avg, izmenjivac, faza, ip_adresa): 
        self.declare(Log(poruka = "Menjam temperature", ip_adresa = ip_adresa))
        self.modify(max_soba, temperatura = avg)
        self.modify(min_soba, temperatura = avg)
        self.modify(izmenjivac, min_temp = 1000.0, max_temp = -1000.0, avg_temp = 0.0)
        self.retract(faza)

    @Rule(
        Auto()
    )
    def stigaoAuto(self): 
        self.declare(Fact(auto_ispred_garaze = True))

    @Rule(
        Auto(),
        PametniUredjaj(ip_adresa = MATCH.ip_adresa), 
        AS.vrata<<GaraznaVrata(ip_adresa = MATCH.ip_adresa, otvorena = False), 
        Fact(auto_ispred_garaze = True)
    )
    def otvoriVrata(self, vrata, ip_adresa): 
        self.declare(Log(poruka = "Garazna vrata => Stigao auto, otvaram", ip_adresa = ip_adresa))
        self.modify(vrata, otvorena = True)

    @Rule(
        PametniUredjaj(ip_adresa = MATCH.ip_adresa), 
        GaraznaVrata(ip_adresa = MATCH.ip_adresa, otvorena = True), 
        Auto(), 
        AS.fact << Fact(auto_ispred_garaze = True)
    )
    def autoJeUGarazi(self, fact, ip_adresa): 
        self.declare(Log(poruka = "Garazna vrata => Stigao auto, otvaram", ip_adresa = ip_adresa))
        self.retract(fact)
        self.declare(Fact(auto_u_garazi = True))

    @Rule(
        Fact(auto_u_garazi = True), 
        PametniUredjaj(ip_adresa = MATCH.ip_adresa), 
        AS.vrata<<GaraznaVrata(ip_adresa = MATCH.ip_adresa, otvorena = True)
    )
    def zatvoriVrata(self, vrata, ip_adresa): 
        self.declare(Log(poruka = "Garazna vrata => Auto je u garazi, zatvaram", ip_adresa = ip_adresa))
        self.modify(vrata, otvorena = False)
    
engine = Engine()
engine.reset()
engine.run()