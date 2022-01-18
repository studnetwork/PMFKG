# Predmet: Uvod u veštačku inteligenciju
# Program: 2019
# Napisao: Srđan Todorović

# Napomena: Podaci koje treba uneti na standardni ulaz ne moraju da se unose ručno
#           moguće je samo nalepiti ih u terminal pomoću kombinacije: CTRL + SHIFT + v


from experta import *
import schema

# 1. Napraviti  šablon osoba koji će sadržati sledeće podatke u vezi osobe: 
# ime(bez prezimena) tipa symbol, 
# pol(dozvoljene vrednosti su oznake m ili z), 
# ime-supružnika, 
# ime-oca, 
# ime-majke. 
# 
# Napraviti deftemplate upit koji ima slot ime tipa symboli slot tip tipa symbol.


class Osoba(Fact):
    ime            = Field(str, mandatory=True)
    pol            = Field( schema.Or('m','z'), mandatory=True )
    ime_supruznika = Field(str, mandatory=False)
    ime_oca        = Field(str, mandatory=True)
    ime_majke      = Field(str, mandatory=True)
    

class Upit(Fact):
    ime = Field(str)
    tip = Field( lambda x : isinstance(x, int) and x in [1,2,3] )

    prosao_odabir_tipa_podataka = Field(bool, default=False)


class Faza(Fact):
    pass

class Odgovor(Fact):
    pass

class Supruznik(Fact):
    ime = Field(str)
    ciji = Field(str)

class Brat(Fact):
    ime = Field(str)
    ciji = Field(str)

class Ujak(Fact):
    ime = Field(str)
    ciji = Field(str)

class KE(KnowledgeEngine):

    @DefFacts()
    def ucitaj(self):
        yield Odgovor('da')
        yield Faza('prikupljanje_upita')
        yield Osoba( ime = 'Vladimir', pol = 'm', ime_majke = 'Sara', ime_oca = 'Stefan' )
        yield Osoba( ime = 'Srecko', pol = 'm', ime_majke = 'Sara', ime_oca = 'Stefan' )
        yield Osoba( ime = 'Jagoda', pol = 'z', ime_majke = 'Sara', ime_oca = 'Stefan' )
        yield Osoba( ime = 'Sara', pol = 'z', ime_supruznika = 'Stefan', ime_majke = 'Milica', ime_oca = 'Predrag' )
        yield Osoba( ime = 'Vladan', pol = 'm', ime_supruznika = 'Bogdana', ime_majke = 'Milica', ime_oca = 'Predrag' )
        yield Osoba( ime = 'Stefan', pol = 'm', ime_supruznika = 'Sara',ime_majke = 'Radmila', ime_oca = 'Zoran' )
        yield Osoba( ime = 'Nebojsa', pol = 'm', ime_supruznika = 'Dragana', ime_majke = 'Radmila', ime_oca = 'Zoran' )
        yield Osoba( ime = 'Milica', pol = 'z', ime_supruznika = 'Predrag', ime_majke = 'Milanka', ime_oca = 'Branislav' )
        yield Osoba( ime = 'Predrag', pol = 'm', ime_supruznika = 'Milica', ime_majke = 'Ljubica', ime_oca = 'Marko' )


################################################################################################
# Faza: prikupljanje_upita

    # 2. Napisati funkciju "prikupljanje_upita" koja korisniku postavlja pitanje 
    # “Navedite ime osobe za koju ispitujete stablo”. Na osnovu korisnikovog odgovora, 
    # funkcija u listu činjenica ubacuje činjenicu po šablonu upit, pri čemu slot tip 
    # ostaje nepopunjen. Potom pitati korisnika da li želi da ispita stablo za još neku 
    # osobu, i ako je odgovor da,ponovo izvršti sve prethodno navedeno. 


    # 3. ES treba prvo da od korisnika traži da navede imena osoba za koje želi da ispita 
    # porodično stablo(korišćenjem funkcije prikupljanje_upita)

    @Rule(
        Faza('prikupljanje_upita'),
        AS.o_ref << Odgovor('da')
    )
    def prikupljanje_upita(self, o_ref):
        self.retract(o_ref)

        odgovor = input("\nNavedite ime osobe za koju ispitujete stablo: ")
        self.declare( Upit(ime = odgovor) )

        odgovor = Odgovor( input("Da li zelite da ispitate stablo za jos neku osobu? (da/ne)\n") )
        self.declare( odgovor )


    @Rule(
        Faza('prikupljanje_upita'),
        AS.o_ref << Odgovor( ~L('da') )
    )
    def brisanje_odgovora(self, o_ref):
        self.retract(o_ref)

    
    ## prelaz prikupljanje_upita > odabir_tipa
    @Rule(
        AS.f_ref << Faza('prikupljanje_upita'),
        salience = -10
    )
    def prelaz_na_odabir_tipa(self, f_ref):
        self.retract(f_ref)
        self.declare( Faza('odabir_tipa') )

        print( '\n' + '-'*10 + "prelazak sa 'prikupljanje_upita' na 'odabir_tipa'" + '-'*10 + '\n')


################################################################################################
# Faza: odabir_tipa

    # 4.Potom se za svaku osobu za koju je postavljen upit utvrđuje tip podataka koji 
    # se potražuju iz stable:
    #   1. Ime supružnika
    #   2. Imena rođene braće
    #   3. Imena rođenih ujaka
    
    # 5.Odabir tipa podataka se vrši navođenjem željenog rednog broja koji se potom dodaju u 
    # činjenicu po šablonu upit, i to za odgovarajuću osobu.


    @Rule(
        Faza('odabir_tipa'),
        AS.u_ref << Upit( ime = MATCH.ime, prosao_odabir_tipa_podataka = False )
    )
    def odabir_tipa_podataka(self, u_ref, ime):
        print("\nTipovi podataka:\n1. Ime supružnika\n2. Imena rođene braće\n3. Imena rođenih ujaka")
        tip = input('\nUnesite redni broj tip podatka za osobu {}: '.format( ime ))

        tip = int(tip) # ovde moze dodci do greske ukoliko nije int; pozeljno bi bilo da se odradi neka validacija

        self.modify( u_ref, tip = tip, prosao_odabir_tipa_podataka = True )


    ## prelaz odabir_tipa > odredjivanje_rodbinskih_veza
    @Rule(
        AS.f_ref << Faza('odabir_tipa'),
        salience = -10
    )
    def prelaz_na_odredjivanje_rodbinskih_veza(self, f_ref):
        self.retract( f_ref )
        self.declare( Faza('odredjivanje_rodbinskih_veza') )
        print()

        print( "-"*10 + "prelazak sa 'odabir_tipa' na 'odredjivanje_rodbinskih_veza'" + "-"*10 + '\n')

################################################################################################
# Faza: odredjivanje_rodbinskih_veza

    # 6. Napraviti pravila koja omogućavaju da se za osobu za koju se upit postavlja pronadju podaci o:
    #   1. Supružniku
    #   2. Rođenoj braći
    #   3. Rođenim ujacima

    
    @Rule(
        Faza('odredjivanje_rodbinskih_veza'),
        Upit( ime = MATCH.ime, tip = 1 ),
        Osoba( ime = MATCH.ime, ime_supruznika = MATCH.ime_supruznika )
    # v1; ne radi ukoliko ne postoji takva osoba u listi cinjenica
    #    Osoba( ime = MATCH.ime ),
    #    Osoba( ime = MATCH.ime_supruznika, ime_supruznika = MATCH.ime )
    )
    def odredi_supruznika(self, ime, ime_supruznika):
        self.declare( Supruznik( ime = ime_supruznika, ciji = ime ) )


    @Rule(
        Faza('odredjivanje_rodbinskih_veza'),
        Upit( ime = MATCH.ime, tip = 1 ),
        Osoba( ime = MATCH.ime ),
        NOT(
            Osoba( ime = MATCH.ime, ime_supruznika = W() ),
            #v1; neispravno; Osoba( ime_supruznika = MATCH.ime )
        )
    )
    def obavesti_da_nema_supruznika(self, ime):
        print('Osoba {} nema supruznika'.format( ime ))



    @Rule(
        Faza('odredjivanje_rodbinskih_veza'),
        Upit( ime = MATCH.ime, tip = 2 ),
        Osoba( ime = MATCH.ime, pol = 'm', ime_majke = MATCH.ime_majke, ime_oca = MATCH.ime_oca ),
        Osoba( ime = MATCH.ime_brata & ~MATCH.ime, pol = 'm', ime_majke = MATCH.ime_majke, ime_oca = MATCH.ime_oca )
    )
    def odredi_rodjenog_brata(self, ime, ime_brata):
        self.declare( Brat( ime = ime_brata, ciji = ime ) )

    @Rule(
        Faza('odredjivanje_rodbinskih_veza'),
        Upit( ime = MATCH.ime, tip = 2 ),
        Osoba( ime = MATCH.ime, ime_majke = MATCH.ime_majke, ime_oca = MATCH.ime_oca ),
        NOT(
            Osoba( ime = ~MATCH.ime, pol = 'm', ime_majke = MATCH.ime_majke, ime_oca = MATCH.ime_oca )
        )
    )
    def obavesti_da_nema_rodjenog_brata(self, ime):
        print('Osoba {} nema rodjenog brata'.format( ime ))



    @Rule(
        Faza('odredjivanje_rodbinskih_veza'),
        Upit( ime = MATCH.ime, tip = 3 ),
        Osoba( ime = MATCH.ime, ime_majke = MATCH.ime_majke ),
        Osoba( ime = MATCH.ime_majke, pol = 'z', ime_majke = MATCH.ime_babe, ime_oca = MATCH.ime_dede ),
        Osoba( ime = MATCH.ime_ujaka, pol = 'm', ime_majke = MATCH.ime_babe, ime_oca = MATCH.ime_dede )
    )
    def odredi_rodjenog_ujaka(self, ime, ime_ujaka):
        self.declare( Ujak( ime = ime_ujaka, ciji = ime ) )


    @Rule(
        Faza('odredjivanje_rodbinskih_veza'),
        Upit( ime = MATCH.ime, tip = 3 ),
        Osoba( ime = MATCH.ime, ime_majke = MATCH.ime_majke ),
        Osoba( ime = MATCH.ime_majke, pol = 'z', ime_majke = MATCH.ime_babe, ime_oca = MATCH.ime_dede ),
        NOT(
            Osoba( pol = 'm', ime_majke = MATCH.ime_babe, ime_oca = MATCH.ime_dede )
        )
    )
    def obavesti_da_nema_rodjenog_ujaka(self, ime):
        print('Osoba {} nema rodjenog ujaka'.format( ime ))
        


    @Rule(
        Faza('odredjivanje_rodbinskih_veza'),
        Upit( ime = MATCH.ime ),   
        NOT(
            Osoba( ime = MATCH.ime )
        ) 
    )
    def obavesti_da_takva_osoba_ne_postoji(self, ime):
        print('Upit nije validan. Osoba {} ne postoji u spisku osoba'.format( ime ))

    ## ovo pravilo nije neophodno (nije trazeno u zadatku)
    @Rule(
        AS.f_ref << Faza('odredjivanje_rodbinskih_veza'),
        salience = -10
    )
    def kraj(self, f_ref):
        self.retract( f_ref )

################################################################################################


engine = KE()
engine.reset()


print('#'*35)
print('Lista cinjenica:')
print('#'*35)


print('='*35)
print('Pocetak')
print('='*35)

engine.run()

print('\n' + '='*35)
print(engine.facts)