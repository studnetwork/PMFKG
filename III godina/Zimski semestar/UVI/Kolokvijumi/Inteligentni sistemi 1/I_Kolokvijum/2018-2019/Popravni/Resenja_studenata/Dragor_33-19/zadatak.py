# Web prodavnica

import re, schema
from experta import *
from experta.utils import freeze

### Klase ###

class Laptop(Fact):
    model = Field(str)
    procesor = Field(lambda x: x in ["i3", "i5", "i7"])
    ssd = Field(lambda x: x in ["DA", "NE"])
    ram = Field(lambda x: x in [4, 8, 12, 16])
    gpu = Field(lambda x: x in [1, 2, 3, 4])
    dijagonala_ekrana = Field(float)
    cena = Field(lambda x: x > 0)
    cf = Field(lambda x: x >= -100 and x <= 100, default = 0)

    #dodatno
    check = Field(list, default = freeze([]))

class Zelje(Laptop):
    max_cena = Field(lambda x: x > 0)

# proizvoljne

class Faza(Fact):
    pass

class LaptopMax(Laptop):
    pass


### ES ###

class MyEngine(KnowledgeEngine):
    
    def png(self):
        print(self.facts)
        print(self.agenda)

    @DefFacts()
    def init(self):
        yield Laptop(model = "Lenovo ThinkBook", procesor = "i3", ssd = "NE", 
                    ram = 8, gpu = 1, dijagonala_ekrana = 15.6, cena = 50000)

        yield Laptop(model = "Acer Nitro", procesor = "i3", ssd = "DA", 
                    ram = 8, gpu = 3, dijagonala_ekrana = 15.6, cena = 65000)

        yield Laptop(model = "Asus ZenBook", procesor = "i5", ssd = "NE", 
                    ram = 4, gpu = 1, dijagonala_ekrana = 14.0, cena = 55000)

        yield Laptop(model = "Apple MacBook Air", procesor = "i5", ssd = "DA", 
                    ram = 4, gpu = 1, dijagonala_ekrana = 13.0, cena = 100000)

        yield Laptop(model = "Dell XPS", procesor = "i7", ssd = "DA", 
                    ram = 16, gpu = 4, dijagonala_ekrana = 15.6, cena = 85000)

        yield Laptop(model = "Huawei MateBook", procesor = "i7", ssd = "DA", 
                    ram = 12, gpu = 2, dijagonala_ekrana = 14.0, cena = 75000)

        
        yield Faza("setup")

        yield LaptopMax(cena = 1, cf = -100)


    ### FAZA: setup

    ## Unos
    @Rule(
        Faza("setup"),
        NOT(Zelje())
    )
    def unos(self):
        self.declare(Zelje(
                        procesor = input(),
                        ssd = input(),
                        ram = int(input()),
                        gpu = int(input()),
                        dijagonala_ekrana = float(input()),
                        cena = int(input()),
                        max_cena = int(input())
                    ))
    
    ## Brisanje
    @Rule(
        Faza("setup"),
        Zelje(max_cena = MATCH.m_cena),
        AS.lap << Laptop(cena = MATCH.cena),
        TEST(lambda m_cena, cena: cena > m_cena)
    )
    def brisanje(self, lap):
        self.retract(lap)


    ### FAZA: cf

    ## U odnosu na CENU
    # CF -
    @Rule(
        Faza("cf"),
        Zelje(cena = MATCH.z_cena),
        AS.lap << Laptop(cena = MATCH.cena, cf = MATCH.cf, check = MATCH.check),
        TEST(lambda z_cena, cena, check: z_cena - cena >= 10000 
            and not "cf_jeftiniji" in check)
    )
    def cf_jeftiniji(self, lap, cf, check):
        # print("cena -")
        self.modify(lap, cf = cf + 25, check = list(check) + ["cf_jeftiniji"])
    
    # CF +
    @Rule(
        Faza("cf"),
        Zelje(cena = MATCH.z_cena),
        AS.lap << Laptop(cena = MATCH.cena, cf = MATCH.cf, check = MATCH.check),
        TEST(lambda z_cena, cena, check: cena - z_cena >= 10000 
            and not "cf_skuplji" in check)
    )
    def cf_skuplji(self, lap, cf, check):
        # print("cena +")
        self.modify(lap, cf = cf - 20, check = list(check) + ["cf_skuplji"])

    
    ## U odnosu na PROCESOR
    @Rule(
        Faza("cf"),
        Zelje(procesor = MATCH.z_cpu),
        AS.lap << Laptop(procesor = MATCH.cpu, cf = MATCH.cf, check = MATCH.check),
        TEST(lambda z_cpu, cpu, check: z_cpu != cpu
            and not "cf_cpu" in check)
    )
    def cf_cpu(self, lap, cf, check):
        # print("cpu")
        self.modify(lap, cf = cf - 20, check = list(check) + ["cf_cpu"])
    
    
    ## U odnosu na SSD
    # CF +
    @Rule(
        Faza("cf"),
        Zelje(ssd = "NE"),
        AS.lap << Laptop(ssd = "DA", cf = MATCH.cf, check = MATCH.check),
        TEST(lambda check: not "cf_ssd_ima" in check)
    )
    def cf_ssd_ima(self, lap, cf, check):
        # print("cpu")
        self.modify(lap, cf = cf + 10, check = list(check) + ["cf_ssd_ima"])

    # CF -
    @Rule(
        Faza("cf"),
        Zelje(ssd = "DA"),
        AS.lap << Laptop(ssd = "NE", cf = MATCH.cf, check = MATCH.check),
        TEST(lambda check: not "cf_ssd_nema" in check)
    )
    def cf_ssd_nema(self, lap, cf, check):
        # print("cpu")
        self.modify(lap, cf = cf + 10, check = list(check) + ["cf_ssd_nema"])
    

    ## U odnosu na RAM
    # CF +
    @Rule(
        Faza("cf"),
        Zelje(ram = MATCH.z_ram),
        AS.lap << Laptop(ram = MATCH.ram, cf = MATCH.cf, check = MATCH.check),
        TEST(lambda z_ram, ram, check: ram > z_ram
            and not "cf_ram_vise" in check)
    )
    def cf_ram_vise(self, lap, ram, z_ram, cf, check):
        # print("ram ima")
        self.modify(lap, cf = cf + (ram - z_ram)/4*10, check = list(check) + ["cf_ram_vise"])

    # CF -
    @Rule(
        Faza("cf"),
        Zelje(ram = MATCH.z_ram),
        AS.lap << Laptop(ram = MATCH.ram, cf = MATCH.cf, check = MATCH.check),
        TEST(lambda z_ram, ram, check: ram < z_ram
            and not "cf_ram_manje" in check)
    )
    def cf_ram_manje(self, lap, cf, check):
        # print("ram nema")
        self.modify(lap, cf = cf - 15, check = list(check) + ["cf_ram_manje"])


    ## U odnosu na GPU
    # CF +
    @Rule(
        Faza("cf"),
        Zelje(gpu = MATCH.z_gpu),
        AS.lap << Laptop(gpu = MATCH.gpu, cf = MATCH.cf, check = MATCH.check),
        TEST(lambda z_gpu, gpu, check: gpu > z_gpu
            and not "cf_gpu_vise" in check)
    )
    def cf_gpu_vise(self, lap, gpu, z_gpu, cf, check):
        # print("gpu vise")
        self.modify(lap, cf = cf + (gpu - z_gpu)*10, check = list(check) + ["cf_gpu_vise"])

    # CF -
    @Rule(
        Faza("cf"),
        Zelje(gpu = MATCH.z_gpu),
        AS.lap << Laptop(gpu = MATCH.gpu, cf = MATCH.cf, check = MATCH.check),
        TEST(lambda z_gpu, gpu, check: gpu < z_gpu
            and not "cf_gpu_manje" in check)
    )
    def cf_gpu_manje(self, lap,cf, check):
        # print("gpu vise")
        self.modify(lap, cf = cf - 15, check = list(check) + ["cf_gpu_manje"])


    ## U odnosu na DIJAGONALU
    @Rule(
        Faza("cf"),
        Zelje(dijagonala_ekrana = MATCH.z_ekr),
        AS.lap << Laptop(dijagonala_ekrana = MATCH.ekr, cf = MATCH.cf, check = MATCH.check),
        TEST(lambda z_ekr, ekr, check: z_ekr == ekr
            and not "cf_dijagonala" in check)
    )
    def cf_dijagonala(self, lap, cf, check):
        # print("cpu")
        self.modify(lap, cf = cf + 15, check = list(check) + ["cf_dijagonala"])



    ### FAZA: max
    @Rule(
        Faza("max"),
        AS.max << LaptopMax(cena = MATCH.m_cena, cf = MATCH.m_cf),
        Laptop(model = MATCH.mod, 
                procesor = MATCH.cpu, 
                ssd = MATCH.ssd, 
                ram = MATCH.ram, 
                gpu = MATCH.gpu, 
                dijagonala_ekrana = MATCH.ekr, 
                cena = MATCH.cena,
                cf = MATCH.cf),
        TEST(lambda cena, cf, m_cena, m_cf: cf > m_cf or (cf == m_cf and cena < m_cena))
    )
    def nadji_max(self, max, mod, cpu, ssd, ram, gpu, ekr, cena, cf):
        self.modify(max,
            model = mod, 
            procesor = cpu, 
            ssd = ssd, 
            ram = ram, 
            gpu = gpu, 
            dijagonala_ekrana = ekr, 
            cena = cena,
            cf = cf
        )


    ### FAZA: ispis

    @Rule(
        Faza("ispis"),
        AS.max << LaptopMax(model = MATCH.od),
        AS.lap << Laptop(model = MATCH.mod, 
                procesor = MATCH.cpu, 
                ssd = MATCH.ssd, 
                ram = MATCH.ram, 
                gpu = MATCH.gpu, 
                dijagonala_ekrana = MATCH.ekr, 
                cena = MATCH.cena,
                cf = MATCH.cf)
    )
    def ispis_max(self, lap, max, mod, cpu, ssd, ram, gpu, ekr, cena, cf):
        print("{} cpu: {}, ssd: {}, ram: {}, gpu: {}, ekr: {}, cena: {}, cf: {}".format(
            mod, cpu, ssd, ram, gpu, ekr, cena, cf
        ))
        self.retract(lap)
        self.retract(max)


    ### Kontrola toka
    @Rule(
        AS.f << Faza("setup"),
        salience = -10
    )
    def kt_setup_to_cf(self, f):
        self.modify(f, _0 = "cf")

    @Rule(
        AS.f << Faza("cf"),
        salience = -10
    )
    def kt_cf_to_max(self, f):
        self.modify(f, _0 = "max")

    @Rule(
        AS.f << Faza("max"),
        salience = -10
    )
    def kt_max_to_ispis(self, f):
        self.modify(f, _0 = "ispis")

    @Rule(
        AS.f << Faza("ispis"),
        Laptop(),
        salience = -10
    )
    def kt_ispis_to_max(self, f):
        self.declare(LaptopMax(cena = 1, cf = -100))
        self.modify(f, _0 = "max")

    @Rule(
        AS.f << Faza("ispis"),
        NOT(Laptop()),
        salience = -10
    )
    def kt_ispis_to_kraj(self, f):
        self.retract(f)

### MAIN ###

ng = MyEngine()
ng.reset()

ng.png()

ng.run()

ng.png()

