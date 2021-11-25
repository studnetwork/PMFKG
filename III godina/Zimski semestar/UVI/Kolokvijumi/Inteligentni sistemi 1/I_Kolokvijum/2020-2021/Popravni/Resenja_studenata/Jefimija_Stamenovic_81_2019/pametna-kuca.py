from typing import Match
from experta import *
import schema
import re
class Zgrada(Fact): 
    tip = Field(schema.Or("KUCA","POMOCNI_OBJEKAT"))
    adresa = Field(str)
    pametni_uredjaji = Field(list)
    prisutan_vlasnik = Field(bool, default=False)

class PametniUredjaj(Fact):
    ip_adresa = Field(lambda x :isinstance(x,str) and re.compile(r'[0-255].[0-255].[0-255].[0-255]'), mandatory=True)

class ElektricniSporet(PametniUredjaj): 
    ukljucena_ringla_1 = Field(bool, default=False)
    ukljucena_ringla_2 = Field(bool, default=False)
    ukljucena_ringla_3 = Field(bool, default=False)
    ukljucena_ringla_4 = Field(bool, default=False)

class Bazen(PametniUredjaj): 
    temperatura = Field(float)
    ukljucen = Field(bool, default=False)

class Vlasnik(Fact):
    ime = Field(str, mandatory=True)
    adresa = Field(str, mandatory=True)

class VremenskiUslovi(Fact): 
    tip = Field(schema.Or("SUNCANO","KISA","OBLACNO"))

class IzmenjivacToplote(PametniUredjaj): 
    ukljucen = Field(bool, default=False)

class Prostorija(Fact): 
    zgrada = Field(str, mandatory=True)
    
class Soba(Prostorija):
    temperatura = Field(float)
    proveren_max = Field(bool, default=False)
    proveren_min = Field(bool, default=False)

class GaraznaVrata(PametniUredjaj):
    vrata = Field(schema.Or("OTVORENA","ZATVORENA"),default="ZATVORENA")

class Log(Fact): 
    ip_adresa = Field(str, mandatory=True)
    poruka = Field(str, mandatory=True)

class Max(Soba): 
    pass
class Min(Soba):
    pass

class Engine(KnowledgeEngine):
    @DefFacts()
    def ucitaj(self):
        yield Zgrada(tip="KUCA", adresa="1", pametni_uredjaji = ["225.220.103.189","181.221.210.162","83.130.70.199"], prisutan_vlasnik=True)
        yield Zgrada(tip="POMOCNI_OBJEKAT", adresa="2", pametni_uredjaji = ["72.141.20.103","61.192.154.2","88.75.69.169"], prisutan_vlasnik=False)
        yield Zgrada(tip="KUCA", adresa="3", pametni_uredjaji = ["27.102.134.138","209.212.83.229","56.118.233.147"], prisutan_vlasnik=False)

        yield ElektricniSporet(ip_adresa="27.102.134.138",  ukljucena_ringla_1=True,  ukljucena_ringla_2=False, ukljucena_ringla_3 = False, ukljucena_ringla_4=False)
        yield ElektricniSporet(ip_adresa="225.220.103.189", ukljucena_ringla_1=True,  ukljucena_ringla_2=False, ukljucena_ringla_3 = True,  ukljucena_ringla_4=False)
        yield ElektricniSporet(ip_adresa="72.141.20.103",   ukljucena_ringla_1=False, ukljucena_ringla_2=False, ukljucena_ringla_3 = False, ukljucena_ringla_4=True)

        yield VremenskiUslovi(tip="OBLACNO")
        yield Bazen(ip_adresa="56.118.233.147", temperatura = 18.5)
        yield Bazen(ip_adresa="83.130.70.199", temperatura = 15.0)

        yield IzmenjivacToplote(ip_adresa="181.221.210.162")
        yield Soba(zgrada = "1", temperatura = 13.0)
        yield Soba(zgrada = "1", temperatura = 15.0)
        yield Soba(zgrada = "1", temperatura = 16.0)
        yield Soba(zgrada = "1", temperatura = 20.0)
        yield Soba(zgrada = "1", temperatura = 21.0)

        yield IzmenjivacToplote(ip_adresa="61.192.154.2")
        yield Soba(zgrada = "2", temperatura = 14.0)
        yield Soba(zgrada = "2", temperatura = 17.0)
        yield Soba(zgrada = "2", temperatura = 16.0)
        yield Soba(zgrada = "2", temperatura = 20.0)
        yield Soba(zgrada = "2", temperatura = 20.0)

        yield GaraznaVrata(ip_adresa="88.75.69.169")

    @Rule(
        NOT(Log()),
        Zgrada(prisutan_vlasnik=False, adresa=MATCH.adresa, pametni_uredjaji=MATCH.lista_uredjaja),
        AS.sporet<<ElektricniSporet(ip_adresa=MATCH.ip_adresa), 
        OR(
            ElektricniSporet(ip_adresa=MATCH.ip_adresa, ukljucena_ringla_1=True), 
            ElektricniSporet(ip_adresa=MATCH.ip_adresa, ukljucena_ringla_2=True),
            ElektricniSporet(ip_adresa=MATCH.ip_adresa, ukljucena_ringla_3=True),
            ElektricniSporet(ip_adresa=MATCH.ip_adresa, ukljucena_ringla_4=True)
        ),
        TEST(lambda ip_adresa, lista_uredjaja:ip_adresa in lista_uredjaja)
    )
    def iskljuci_sporete(self, sporet,ip_adresa):
        self.declare(Log(ip_adresa=ip_adresa, poruka="Iskljucujem sporet..."))
        self.modify(sporet, ukljucena_ringla_1=False, ukljucena_ringla_2=False, ukljucena_ringla_3=False, ukljucena_ringla_4=False) 

    @Rule(
        NOT(Log()),
        VremenskiUslovi(tip=~L("SUNCANO")), 
        Zgrada(adresa=MATCH.zgrada, pametni_uredjaji=MATCH.lista_uredjaja),
        AS.bazen << Bazen(temperatura=MATCH.temperatura & P(lambda x:x<18), 
                        ukljucen=False,ip_adresa=MATCH.ip_adresa),
        TEST(lambda ip_adresa, lista_uredjaja:ip_adresa in lista_uredjaja)
    )
    def ukljuci_bazen(self,bazen,ip_adresa): 
        self.declare(Log(ip_adresa=ip_adresa, poruka="Ukljucujem grejanje u bazenu..."))
        self.modify(bazen, ukljucen=True)

    @Rule(  
        NOT(Log()),
        Zgrada(adresa=MATCH.zgrada, pametni_uredjaji=MATCH.lista_uredjaja),
        IzmenjivacToplote(ip_adresa=MATCH.ip_adresa), 
        TEST(lambda ip_adresa, lista_uredjaja:ip_adresa in lista_uredjaja),
        NOT(Min(zgrada=MATCH.zgrada)),
        NOT(Max(zgrada=MATCH.zgrada)), 
        Soba(zgrada=MATCH.zgrada, temperatura=MATCH.temperatura)
    )
    def kreiraj_max_min(self,zgrada,temperatura): 
        self.declare(Max(zgrada=zgrada, temperatura=temperatura))
        self.declare(Min(zgrada=zgrada, temperatura=temperatura))

    @Rule(  
        NOT(Log()),
        AS.max << Max(zgrada=MATCH.zgrada,temperatura=MATCH.temp_max),
        Soba(zgrada=MATCH.zgrada, temperatura=MATCH.temp, proveren_max=False),
        TEST(lambda temp,temp_max:temp>temp_max)
    )
    def proveri_max(self,max,temp): 
        self.modify(max, temperatura=temp)

    @Rule(  
        NOT(Log()),
        AS.min << Min(zgrada=MATCH.zgrada,temperatura=MATCH.temp_min),
        Soba(zgrada=MATCH.zgrada, temperatura=MATCH.temp,proveren_min=False),
        TEST(lambda temp,temp_min:temp<temp_min)
    )
    def proveri_min(self, min, temp):
        self.modify(min, temperatura=temp)

    @Rule(  
        NOT(Log()),
        Min(zgrada=MATCH.zgrada,temperatura=MATCH.temp_min),
        AS.soba<<Soba(zgrada=MATCH.zgrada, temperatura=MATCH.temp,proveren_min=False),
        TEST(lambda temp,temp_min:temp>=temp_min)
    )
    def obradi_min(self, soba): 
        self.modify(soba, proveren_min=True)

    @Rule(  
        NOT(Log()),
        Max(zgrada=MATCH.zgrada,temperatura=MATCH.temp_max),
        AS.soba<<Soba(zgrada=MATCH.zgrada, temperatura=MATCH.temp,proveren_max=False),
        TEST(lambda temp,temp_max:temp<=temp_max)
    )
    def obradi_max(self, soba):
        self.modify(soba, proveren_max=True)

    @Rule(
        NOT(Log()),
        Zgrada(adresa=MATCH.zgrada, pametni_uredjaji=MATCH.lista_uredjaja),
        IzmenjivacToplote(ip_adresa=MATCH.ip_adresa),
        Max(zgrada=MATCH.zgrada,temperatura=MATCH.temp_max),
        Min(zgrada=MATCH.zgrada,temperatura=MATCH.temp_min),
        NOT(Soba(zgrada=MATCH.zgrada, proveren_max=False)), 
        NOT(Soba(zgrada=MATCH.zgrada, proveren_min=False)),
        AS.soba1 << Soba(zgrada=MATCH.zgrada, temperatura=MATCH.temp1 & MATCH.temp_max), 
        AS.soba2 << Soba(zgrada=MATCH.zgrada, temperatura=MATCH.temp2&MATCH.temp_min), 
        TEST(lambda temp1, temp2:abs(temp1-temp2)>5)
    )
    def ukljuci_izmenjivac_toplote(self, zgrada, ip_adresa,soba1,soba2): 
        prosek = (soba1['temperatura']+soba2['temperatura'])/2
        ispis = "Zgrada" + str(zgrada)+" => U sobama sa temperaturama "+str(soba1['temperatura'])+" i "+str(soba2['temperatura']) +" se setuje prosek..."
        self.declare(Log(ip_adresa=ip_adresa, poruka=ispis))
        self.modify(soba1, temperatura=prosek)
        self.modify(soba2, temperatura=prosek)
    
    @Rule(
        NOT(Log()),
        NOT(Fact('detektovan-automobil')), 
        NOT(Fact('auto-u-garazi')),
        Zgrada(pametni_uredjaji=MATCH.lista_uredjaja, tip="POMOCNI_OBJEKAT"),
        GaraznaVrata(ip_adresa=MATCH.ip_adresa),
        TEST(lambda ip_adresa, lista_uredjaja:ip_adresa in lista_uredjaja)
    )
    def detektuj_auto(self,ip_adresa): 
        self.declare(Log(ip_adresa=ip_adresa, poruka="Detektovan auto..."))
        self.declare(Fact('detektovan-automobil'))

    @Rule(
        NOT(Log()),
        AS.garaza << GaraznaVrata(ip_adresa = MATCH.ip_adresa, vrata=L("ZATVORENA")),
        AS.auto << Fact('detektovan-automobil')
    )
    def podigni_vrata(self, garaza, auto,ip_adresa):
        self.declare(Log(ip_adresa=ip_adresa, poruka='Otvaram vrata ...'))
        self.modify(garaza, vrata='OTVORENA') 

    @Rule(
        NOT(Log()),
        GaraznaVrata(ip_adresa = MATCH.ip_adresa, vrata=L("OTVORENA")),
        AS.auto << Fact('detektovan-automobil'),
        NOT(Fact('auto-u-garazi'))
    )
    def ubacujem_auto(self, auto, ip_adresa):
        self.declare(Log(ip_adresa=ip_adresa, poruka="Ulazi auto..."))
        self.declare(Fact('auto-u-garazi'))
        self.retract(auto)

    @Rule(
        NOT(Log()),
        AS.garaza << GaraznaVrata(ip_adresa = MATCH.ip_adresa, vrata=L("OTVORENA")),
        Fact('auto-u-garazi')
    )
    def spusti_vrata(self, garaza, ip_adresa):
        self.declare(Log(ip_adresa=ip_adresa, poruka="Zatvaram vrata..."))
        self.modify(garaza, vrata='ZATVORENA') 

    @Rule(
        AS.poruka<<Log(ip_adresa=MATCH.ip_adresa, poruka=MATCH.tekst)
    )    
    def stampaj_log(self,ip_adresa,poruka,tekst):
        print("Uredjaj {} : {}".format(ip_adresa,tekst))
        self.retract(poruka)
engine = Engine()
engine.reset()

engine.run()