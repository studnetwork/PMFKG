from experta import *
from experta.utils import freeze
import schema

#watch('ACTIVATIONS','RULES','FACTS')

class Faza(Fact):
    pass

class Laptop(Fact):
    model = Field(str)
    procesor = Field(schema.Or("i3","i5","i7"))
    ssd = Field(schema.Or("DA","NE"))
    ram = Field(schema.Or(4,8,12,16))
    gpu = Field(schema.Or(1,2,3,4))
    dijagonala_ekrana = Field(float)
    cena = Field(lambda x: isinstance(x,int) and x > 0)
    cf = Field(lambda x: isinstance(x,int) and -100 <= x <= 100, default = 0)

    flag = Field(list, False, freeze([]))

class ZeljeKorisnika(Laptop):
    zeljena_cena = Field(lambda x: isinstance(x,int) and x > 0)
    max_cena = Field(lambda x: isinstance(x,int) and x > 0)

class Engine(KnowledgeEngine):
    laptopovi = list()

    @DefFacts()
    def ucitavanje_cinjenica(self):
        yield Faza("Unos")

        yield Laptop(model = "Asus",
                     procesor = "i7",
                     ssd = "DA",
                     ram = 16,
                     gpu = 4,
                     dijagonala_ekrana = 19.5,
                     cena = 110000)
        
        yield Laptop(model = "Acer",
                     procesor = "i5",
                     ssd = "NE",
                     ram = 8,
                     gpu = 2,
                     dijagonala_ekrana = 18.7,
                     cena = 75000)
        
        yield Laptop(model = "Lenovo",
                     procesor = "i3",
                     ssd = "NE",
                     ram = 8,
                     gpu = 2,
                     dijagonala_ekrana = 16.7,
                     cena = 85000)
  
    # Unos korisnika    
    @Rule(Faza("Unos"))
    def unos_korisnika(self):
        self.declare(ZeljeKorisnika(procesor = "i7",
                                    ssd = "DA",
                                    ram = 16,
                                    gpu = 4,
                                    dijagonala_ekrana = 18.7,
                                    zeljena_cena = 60000,
                                    max_cena = 85000))
        '''
        self.declare(ZeljeKorisnika(procesor = str(input()),
                                    ssd = str(input()),
                                    ram = int(input()),
                                    gpu = int(input()),
                                    dijagonala_ekrana = float(input()),
                                    zeljena_cena = int(input()),
                                    max_cena = int(input())))
        '''
    
    # Kontrola toka: Unos -> Brisi
    @Rule(
        AS.faza << Faza("Unos"),
        salience = -10
    )
    def kontrola_unos_brisi(self,faza):
        self.retract(faza)
        self.declare(Faza("Brisi"))

    @Rule(
        Faza("Brisi"),
        AS.laptop << Laptop(cena = MATCH.cena),
        ZeljeKorisnika(max_cena = MATCH.max),
        TEST(lambda cena,max: cena > max)
    )
    def obrisi_preskupe(self,laptop):
        print("Izbrisan je model {}".format(laptop["model"]))
        self.retract(laptop)

    # Kontrola toka: Brisi -> CF
    @Rule(
        AS.faza << Faza("Brisi"),
        salience = -10
    )
    def kontrola_brisi_cf(self,faza):
        self.retract(faza)
        self.declare(Faza("CF"))
    
    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(cena = MATCH.cena, cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(zeljena_cena = MATCH.zeljena),
        TEST(lambda cena, zeljena, flag:  cena + 10000 < zeljena and flag.count("jeftiniji") == 0)
    )
    def jeftiniji(self,laptop,cf,flag):
        self.modify(laptop, cf = cf + 25, flag = list(flag) + ["jeftiniji"])

    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(cena = MATCH.cena, cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(zeljena_cena = MATCH.zeljena),
        TEST(lambda cena,zeljena,flag: cena - 10000 > zeljena and flag.count("skuplji") == 0)
    )
    def skuplji(self,laptop,cf,flag):
        self.modify(laptop, cf = cf - 20, flag = list(flag) + ["skuplji"])
    
    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(procesor = MATCH.procesor, cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(procesor = MATCH.zeljeni_procesor),
        TEST(lambda procesor, zeljeni_procesor, flag: procesor != zeljeni_procesor and flag.count("tip_procesora") == 0)
    )
    def tip_procesora(self,laptop,cf,flag):
        self.modify(laptop, cf = cf - 20, flag = list(flag) + ["tip_procesora"])

    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(ssd = "NE", cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(ssd = "DA"),
        TEST(lambda flag: flag.count("zeli_ssd") == 0)
    )
    def zeli_ssd(self,laptop,cf,flag):
        self.modify(laptop, cf = cf - 15, flag = list(flag) + ["zeli_ssd"])
    
    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(ssd = "NE", cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(ssd = "DA"),
        TEST(lambda flag: flag.count("zeli_ssd") == 0)
    )
    def zeli_ssd(self,laptop,cf,flag):
        self.modify(laptop, cf = cf - 15, flag = list(flag) + ["zeli_ssd"])
    
    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(ssd = "DA", cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(ssd = "NE"),
        TEST(lambda flag: flag.count("ne_zeli_ssd") == 0)
    )
    def ne_zeli_ssd(self,laptop,cf,flag):
        self.modify(laptop, cf = cf + 10, flag = list(flag) + ["ne_zeli_ssd"])

    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(ram = MATCH.ram, cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(ram = MATCH.zeljeni_ram),
        TEST(lambda ram, zeljeni_ram, flag: ram < zeljeni_ram and flag.count("manje_rama") == 0)
    )
    def manje_rama(self,laptop,cf,flag):
        self.modify(laptop, cf = cf - 15, flag = list(flag) + ["manje_rama"])

    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(ram = MATCH.ram, cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(ram = MATCH.zeljeni_ram),
        TEST(lambda ram, zeljeni_ram, flag: ram > zeljeni_ram and flag.count("vise_rama") == 0)
    )
    def vise_rama(self,laptop,cf,ram,zeleni_ram,flag):
        koef = (ram - zeleni_ram) / 4
        self.modify(laptop, cf = cf + 10 * koef, flag = list(flag) + ["vise_rama"])

    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(gpu = MATCH.gpu, cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(gpu = MATCH.zeljeni_gpu),
        TEST(lambda gpu, zeljeni_gpu, flag: gpu < zeljeni_gpu and flag.count("manje_gpu") == 0)
    )
    def manje_gpu(self,laptop,cf,flag):
        self.modify(laptop, cf = cf - 15, flag = list(flag) + ["manje_gpu"])

    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(gpu = MATCH.gpu, cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(gpu = MATCH.zeljeni_gpu),
        TEST(lambda gpu, zeljeni_gpu, flag: gpu > zeljeni_gpu and flag.count("vise_gpu") == 0)
    )
    def vise_gpu(self,laptop,gpu,zeleni_gpu,cf,flag):
        koef = (gpu - zeleni_gpu) / 4
        self.modify(laptop, cf = cf + 10 * koef, flag = list(flag) + ["vise_gpu"])
        
    @Rule(
        Faza("CF"),
        AS.laptop << Laptop(dijagonala_ekrana = MATCH.dijagonala, cf = MATCH.cf, flag = MATCH.flag),
        ZeljeKorisnika(dijagonala_ekrana = MATCH.zeljena_dijagonala),
        TEST(lambda dijagonala, zeljena_dijagonala, flag: dijagonala == zeljena_dijagonala and flag.count("odgovarajuca_dijagonala") == 0)
    )
    def odgovarajuca_dijagonala(self,laptop,cf,flag):
        self.modify(laptop, cf = cf + 15, flag = list(flag) + ["odgovarajuca_dijagonala"])

    # Kontrola toka:
    @Rule(
        AS.faza << Faza("CF"),
        salience = -10
    )
    def kontrola_cf_zavrsna(self,faza):
        self.retract(faza)
        self.declare(Faza("Zavrsna"))
    
    @Rule(
        Faza("Zavrsna"),
        AS.laptop << Laptop(model = MATCH.model, cf = MATCH.cf, cena = MATCH.cena)
    )
    def lista_laptopova(self,laptop,model,cf,cena):
        self.laptopovi.append({"model":model,"cf":cf,"cena":cena})
        self.retract(laptop)

engine = Engine()
engine.reset()
engine.run()

lista = engine.laptopovi

def sortiraj_cena(x):
  return x['cena']

def sortiraj_cf(x):
    return x['cf']
  
lista.sort(key=sortiraj_cf)
print("Sortirano po CF u opadajucem redosledu:")
for el in lista:
    print("Model = {}, CF = {}, Cena = {}".format(el['model'],el['cf'],el['cena']))

lista.sort(key=sortiraj_cena)
print("Sortirano po ceni u rastucem redosledu:")
for el in lista:
    print("Model = {}, CF = {}, Cena = {}".format(el['model'],el['cf'],el['cena']))
