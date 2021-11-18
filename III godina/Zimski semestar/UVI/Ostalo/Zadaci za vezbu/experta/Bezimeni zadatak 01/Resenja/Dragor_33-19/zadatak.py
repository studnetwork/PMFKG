import schema, re
from experta import *
from experta.utils import freeze


class Faza(Fact):
    pass

class Osoba(Fact):

    ime = Field(str)
    pol = Field(schema.Or("m", "z"))
    ime_supruznika = Field(str)
    ime_oca = Field(str)
    ime_majke = Field(str)


class StatusInputa(Fact):
    pass

class TipUpita(Fact):
    pass

class NazivUpita(Fact):
    pass

class Upit(Fact):

    ime = Field(str)
    tip = Field(str)

class ProsaoUpit(Fact):
    pass

class MyEngine(KnowledgeEngine):

    def png(self):
        print(self.facts)
        print(self.agenda)


    @DefFacts()
    def init(self):
        yield StatusInputa("da")

        # Rodjena braca: Pera - Laza - Zika
        # Supruznici: Pera - Nina, Mika - Mina
        # Ujak - sestric: Laza - Mina, Laza - Dule, Zika - Mina, Zika - Dule
        yield Osoba(ime = "Sale", pol = "m",                            ime_oca = "Mika", ime_majke = "Mina")
        yield Osoba(ime = "Pera", pol = "m", ime_supruznika = "Nina")
        yield Osoba(ime = "Mika", pol = "m", ime_supruznika = "Mina")
        yield Osoba(ime = "Laza", pol = "m",                            ime_oca = "Mika", ime_majke = "Mina")
        yield Osoba(ime = "Zika", pol = "m",                            ime_oca = "Mika", ime_majke = "Mina")
        yield Osoba(ime = "Dule", pol = "m",                            ime_oca = "Pera", ime_majke = "Nina")
        yield Osoba(ime = "Nina", pol = "z", ime_supruznika = "Pera",   ime_oca = "Mika", ime_majke = "Mina")
        yield Osoba(ime = "Mina", pol = "z", ime_supruznika = "Mika")
        yield Osoba(ime = "Masa", pol = "z",                            ime_oca = "Pera", ime_majke = "Nina")

        yield NazivUpita(1, "ime_supruznika")
        yield NazivUpita(2, "imena_rodjene_brace")
        yield NazivUpita(3, "imena_rodjenih_ujaka")

        yield Faza("pu")


    # 1. faza (pu)
    @Rule(
        Faza("pu"),
        AS.s << StatusInputa("da")
    )
    def prikupljanje_upita(self, s):
        print("Navedite ime osobe za koju ispitujete stablo:")
        self.declare(Upit(ime = input()))
        print("Da li zelite da ispitate stablo za jos neku osobu? (da/ne)")
        self.modify(s, _0 = input())


    # 2. faza (ut)
    @Rule(
        Faza("ut"),
        Upit(ime = MATCH.i)
    )
    def utvrdjivanje_tipa_upita(self, i):
        print("Izaberite tip upita za osobu \"{}\"".format(i))
        self.declare(TipUpita(ime = i, tip = int(input())))

    
    # 3. faza (dt)
    @Rule(
        Faza("dt"),
        AS.tu << TipUpita(ime = MATCH.i, tip = MATCH.t),
        AS.up << Upit(ime = MATCH.i),
        NazivUpita(MATCH.t, MATCH.n)
    )
    def dodeljivanje_tipa_upita(self, tu, up, n):
        self.modify(up, tip = n)
        self.retract(tu)


    # 4. faza (pr)
    @Rule(
        Faza("pr"),
        AS.up << Upit(ime = MATCH.i, tip = "ime_supruznika"),
        Osoba(ime = MATCH.i, ime_supruznika = MATCH.s),
        Osoba(ime = MATCH.s)

    )
    def ima_supruznika(self, up, i, s):
        print("Supruznik od \"{}\" je \"{}\"".format(i, s))
        self.declare(ProsaoUpit(ime = i, tip = "ime_supruznika"))

    
    @Rule(
        Faza("pr"),
        AS.up << Upit(ime = MATCH.i, tip = "imena_rodjene_brace"),
        Osoba(ime = MATCH.i, ime_oca = MATCH.io, ime_majke = MATCH.im),
        Osoba(ime = MATCH.b & ~MATCH.i, ime_oca = MATCH.io, ime_majke = MATCH.im, pol = "m")

    )
    def ima_brata(self, up, i, b):
        print("Brat od \"{}\" je \"{}\"".format(i, b))
        self.declare(ProsaoUpit(ime = i, tip = "imena_rodjene_brace"))


    @Rule(
        Faza("pr"),
        AS.up << Upit(ime = MATCH.i, tip = "imena_rodjenih_ujaka"),
        Osoba(ime = MATCH.i, ime_majke = MATCH.im1),
        Osoba(ime = MATCH.im1, ime_oca = MATCH.io2, ime_majke = MATCH.im2),
        Osoba(ime = MATCH.u, ime_oca = MATCH.io2, ime_majke = MATCH.im2, pol = "m")

    )
    def ima_ujaka(self, up, i, u):
        print("Ujak od \"{}\" je \"{}\"".format(i, u))
        self.declare(ProsaoUpit(ime = i, tip = "imena_rodjenih_ujaka"))
        

    # 4. faza (ns)

    @Rule(
        Faza("nt"),
        AS.up << Upit(ime = MATCH.i, tip = MATCH.t),
        NOT(
            ProsaoUpit(ime = MATCH.i, tip = MATCH.t)
        )
    )
    def nema_trazenog_srodnika(self, up, i):
        print("{} nema trazenog srodnika".format(i))
        self.retract(up)


    # Promene faza

    # pu -> ut
    @Rule(
        AS.f << Faza("pu"),
        salience = -10
    )
    def pu_to_ut(self, f):
        self.modify(f, _0 = "ut")
        # self.png()

    # ut -> dt
    @Rule(
        AS.f << Faza("ut"),
        salience = -10
    )
    def ut_to_dt(self, f):
        self.modify(f, _0 = "dt")
        # self.png()

    # dt -> pr
    @Rule(
        AS.f << Faza("dt"),
        salience = -10
    )
    def dt_to_pr(self, f):
        self.modify(f, _0 = "pr")
        # self.png()

    # pr -> nt
    @Rule(
        AS.f << Faza("pr"),
        salience = -10
    )
    def pr_to_nt(self, f):
        self.modify(f, _0 = "nt")
        # self.png()



ng = MyEngine()
ng.reset()

ng.png()

ng.run()

ng.png()