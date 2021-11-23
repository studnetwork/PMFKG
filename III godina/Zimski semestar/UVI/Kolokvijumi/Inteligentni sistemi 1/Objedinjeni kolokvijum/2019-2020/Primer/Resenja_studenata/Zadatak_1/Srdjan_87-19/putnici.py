from experta import *
import schema



class Putnik(Fact):
    ime            = Field(str, mandatory=True)
    drzava_porekla = Field(str, mandatory=True)
    broj_godina    = Field( lambda x : isinstance(x, int) and 0 < x < 130)
    sadrzaj_torbe  = Field(list)
    ima_dosije     = Field(schema.Or('DA','Ne'), default='Ne')
    procena_rizika = Field( lambda x : isinstance(x, float) and 0 <= x <= 1, default=0.5 )

    prosao_ima_dosije                          = Field(bool, default=False)
    prosao_dolazi_iz_rizicne_drzave            = Field(bool, default=False)
    prosao_nije_iz_Nigerije                    = Field(bool, default=False)
    prosao_ima_manje_od_18_i_vise_od_50_godina = Field(bool, default=False)
    prosao_ispisi_rizicnog                     = Field(bool, default=False)
    prosao_provera_torbe_rizicnog              = Field(bool, default=False)

class Faza(Fact):
    pass

class NajrizicnijiPutnik(Fact):
    ime            = Field(str)
    procena_rizika = Field( lambda x : isinstance(x, float) and 0 <= x <= 1, default=0.0 )

class KE(KnowledgeEngine):

    @DefFacts()
    def ucitaj(self):
        yield Faza('inicijalna')
        yield Putnik(ime='Pera', drzava_porekla = 'Srbija', broj_godina=23, sadrzaj_torbe=['rakija'])
        yield Putnik(ime='Zika', drzava_porekla = 'Rumunija', broj_godina=56, ima_dosije='DA')
        yield Putnik(ime='Muhamed', drzava_porekla = 'Iran', broj_godina=13, sadrzaj_torbe=['noz'])
        yield Putnik(ime='Mika', drzava_porekla = 'Nigerija', broj_godina=42, sadrzaj_torbe=['pistolj'], ima_dosije='DA')
        

##################################################################################################################################################
# FAZA: inicijalna

    # 1
    # a. Kreirati pravilo koje putnicima sa dosijeom povećavaju procenu rizika za 0.2
    @Rule(
        Faza('inicijalna'),
        AS.putnik << Putnik(procena_rizika = MATCH.pr, ima_dosije = 'DA', prosao_ima_dosije = False)
    )
    def ima_dosije(self, putnik, pr):
        self.modify(putnik, procena_rizika = pr + 0.2, prosao_ima_dosije = True)

        print("# 1) a: Procena rizika putnika {} povecana sa {} na {} jer ima dosije".format( putnik['ime'], pr,pr+0.2 )) # TODO obrisati pred predaju

    

    # b. Kreirati pravilo koje putnicima čija je država porekla Libija ili Iran povećava procenu rizika za 0.25
    @Rule(
        Faza('inicijalna'),
        AS.p << Putnik( procena_rizika = MATCH.pr, drzava_porekla = L('Libija') | L('Iran'), prosao_dolazi_iz_rizicne_drzave = False )
    )
    def dolazi_iz_rizicne_drzave(self, p, pr):
        self.modify(p, procena_rizika = pr + 0.25, prosao_dolazi_iz_rizicne_drzave = True)
        print('# 1) b: Povecana procena rizika sa {} na {} putnika {} jer je poreklom iz {}'.format( pr, pr+0.25, p['ime'], p['drzava_porekla'] )) # TODO obrisati pred predaju


    # c. Kreirati pravilo koje putnicima čija je država porekla nije Nigerija umanjuje procenu rizika za 0.1. Ovo pravilo se ne odnosi pa putnike iz Libije ili Irana
    @Rule(
        Faza('inicijalna'),
        AS.p << Putnik( procena_rizika = MATCH.pr, drzava_porekla = ~( L('Nigerija') | L('Iran') | L('Libija') ), prosao_nije_iz_Nigerije = False )
    )
    def nije_iz_Nigerije(self, p, pr):
        self.modify(p, procena_rizika = pr - 0.1, prosao_nije_iz_Nigerije = True)

        print("# 1) c: Smanjena procena rizika sa {} na {} putnika {} cija drzava porekla nije Nigerija (dolazi iz {})".format( pr, pr-0.1, p['ime'], p['drzava_porekla'] )) # TODO obrisati pred predaju


    # d. Kreirati pravilo koje putnicima s brojem godina manjim od 18 ili većim od 50 umanjuje procenu rizika za 0.15
    @Rule(
        Faza('inicijalna'),
        AS.p << Putnik( 
            procena_rizika = MATCH.pr, 
            broj_godina = P(lambda x: x < 18 or x > 50 ), 
            prosao_ima_manje_od_18_i_vise_od_50_godina = False 
        )
    )
    def ima_manje_od_18_i_vise_od_50_godina(self, p, pr):
        self.modify(p, procena_rizika = pr - 0.15, prosao_ima_manje_od_18_i_vise_od_50_godina = True )

        print('# 1) d: Procena rizika putnika {} se smanjuje sa {} na {} jer ima manje od 18 ili vise od 50 godina (ima {})'.format( p['ime'], pr, pr-0.15, p['broj_godina'] )) # TODO obrisati pred predaju


    ## prelazak inicijalna > ispis_rizicnih
    @Rule(
        AS.f << Faza('inicijalna'),
        salience = -10
    )
    def prelaz_na_ispis_rizicnih(self, f):
        self.retract(f)
        self.declare( Faza('ispis_rizicnih') )

        print( '\n' + '-'*10 + "prelazak iz 'inicijalna' na 'ispis_rizicnih'" + '-'*10 + '\n') # TODO obrisati pred predaju


##################################################################################################################################################
# FAZA: ispis_rizicnih


    # 3.Nakon završene inicijalne provere svih putnika ispisati sve osobe čija je procena rizika veća od 0.5.
    @Rule(
        Faza('ispis_rizicnih'),
        AS.p << Putnik( ime = MATCH.ime, procena_rizika = P(lambda x : x > 0.5), prosao_ispisi_rizicnog = False )
    )
    def ispisi_rizicnog(self, p, ime):
        print(ime)
        self.modify(p, prosao_ispisi_rizicnog = True)

        print("# 3) Putnik {} ima vecu procenu rizika od 0.5 ({})".format( p['ime'], p['procena_rizika'] )) # TODO obrisati pred predaju


    ## prelazak ispis_rizicnih > skeniranje_rizicnih
    @Rule(
        AS.f << Faza('ispis_rizicnih'),
        salience = -10
    )
    def prelaz_na_skeniranje_rizicnih(self, f):
        self.retract(f)
        self.declare( Faza('skeniranje_rizicnih') )

        print( '\n' + '-'*10 + "prelazak iz 'ispis_rizicnih' na 'skeniranje_rizicnih'" + '-'*10 + '\n' ) # TODO obrisati pred predaju

##################################################################################################################################################
# FAZA: skeniranje_rizicnih

    # 4. Potom putnici sa faktorom rizika preko 0.5 daju torbe na pregled skenerom. Ukoliko skener unutar torbe pronađe nož 
    # ili pištolj ispisuje se ime te osobe i odmah se uklanja iz spiska putnika.

    @Rule(
        Faza('skeniranje_rizicnih'),
        AS.p << Putnik(
            ime = MATCH.ime,
            procena_rizika = P( lambda x : x > 0.5 ),
            sadrzaj_torbe = P( lambda x : 'noz' in x or 'pistolj' in x )
        )
    )
    def provera_torbe_rizicnog(self, p, ime):
        print(ime)
        print("4. Putnik {} sa procenom rizika {} ima u torbi noz ili pistolj (ima: {}) i zbog toga se izbacuje sa spiska".format( ime, p['procena_rizika'], ', '.join(p['sadrzaj_torbe']) )) # TODO obrisati pred predaju
        self.retract(p)

    ## prelazak skeniranje_rizicnih > odredjivanje_najrizicnijeg
    @Rule(
        AS.f << Faza('skeniranje_rizicnih'),
        salience = -10
    )
    def prelazak_na_odredjivanje_najrizicnijeg(self, f):
        self.retract(f)
        self.declare( Faza('odredjivanje_najrizicnijeg') )

        print( '\n' + '-'*10 + "prelazak iz 'skeniranje_rizicnih' na 'odredjivanje_najrizicnijeg'" + '-'*10 + '\n' ) # TODO obrisati pred predaju

##################################################################################################################################################
# FAZA: odredjivanje_najrizicnijeg

    # 5. Poslednji korak je provere je dodano analiza rizika koju sprovodi službenik nakon što svi putnici prođu 
    # kontrolu skenerom. Ekspertski sistem treba pronaći osobu sa najvećom procenom rizika i ispisati njegovo ime

    @Rule(
        Faza('odredjivanje_najrizicnijeg'),
        NOT( NajrizicnijiPutnik() )
    )
    def inicijalizuj_pretragu(self):
        self.declare( NajrizicnijiPutnik( ime = 'Dummy', procena_rizika = 0.0 ) )

    # prolazi kroz putnike dok ne nadje najrizicnijeg
    @Rule(
        Faza('odredjivanje_najrizicnijeg'),
        AS.np << NajrizicnijiPutnik( procena_rizika = MATCH.np_pr ),
        Putnik( ime = MATCH.ime, procena_rizika = MATCH.pr ),
        TEST( lambda pr, np_pr : pr > np_pr )
    )
    def pronadjen_novi_kandidat_za_najrizicnijeg(self, np, ime, pr ):

        print("# 5) [{},{}] vise nije najrizicniji. Novi najrizicniji je: [{},{}]".format( np['ime'], np['procena_rizika'], ime, pr )) # TODO obrisati pred predaju
        self.modify( np, ime = ime, procena_rizika = pr )



    ## prelaz odredjivanje_najrizicnijeg > ispis_najrizicnijeg
    @Rule( 
        AS.f << Faza('odredjivanje_najrizicnijeg'),
        salience = -10
    )
    def prelaz_na_ispis_najrizicnijeg(self, f):
        self.retract(f)
        self.declare( Faza('ispis_najrizicnijeg') )

        print( '\n' + '-'*10 + "prelazak iz 'odredjivanje_najrizicnijeg' na 'ispis_najrizicnijeg'" + '-'*10 + '\n' ) # TODO obrisati pred predaju

##################################################################################################################################################
# FAZA: ispis_najrizicnijeg

    @Rule(
        Faza('ispis_najrizicnijeg'),
        NajrizicnijiPutnik( ime = MATCH.i, procena_rizika = MATCH.pr )
    )
    def ispisi_najrizicnijeg(self, i, pr):
        print("Putnik sa najvecom procenom rizika: {} {}".format( i, pr ) )

    ## kraj
    @Rule(
        AS.f << Faza('ispis_najrizicnijeg'),
        salience = -10
    )
    def kraj_procedure(self, f):
        self.retract(f)
        print('Kraj procedure') # TODO obrisati pred predaju

##################################################################################################################################################

#watch('ACTIVATIONS', 'RULES','FACTS')



engine = KE()
engine.reset()



print('#'*35)
print("Pravila za promenu procene:\nIma dosije = +0.2\nDolazi iz Libije ili Irana = +0.25\nNije iz Nigerije = -0.1\nManje od 18 ili vise od 50 godina = -0.15\n")
print('Trenutna lista cinjenica')
print( engine.facts )
print('#'*35)


print('='*35)
print("Pocetak")
print('='*35)

engine.run()

print('='*35)

print( engine.facts )
