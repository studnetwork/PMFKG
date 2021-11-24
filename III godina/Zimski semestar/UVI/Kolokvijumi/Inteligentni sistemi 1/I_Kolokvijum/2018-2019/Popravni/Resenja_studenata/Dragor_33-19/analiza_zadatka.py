### Analiza zadatka ###
'''
FAZA: setup

    > Korisnik unosi zelje

    > Brisu se laptopovi skuplji od zeljene max cene


FAZA: cf

    > Ako je laptop jeftiniji od zeljene cene za 10.000+, CF += 25
    | Ako je laptop skuplji od zeljene cene za 10.000+, CF -= 20
    ---[XOR]

    > Ako tip procesora nije odgovarajuci, CF -= 20

    > Ako je zeljen SSD a laptop ga nema, CF -= 15
    | Ako nije zeljen SSD a laptop ga ima, CF += 10
    ---[XOR]

    > Ako ima manje RAM-a od zeljenog, CF -= 15
    | Ako imas vise RAM-a od zeljenog, za svaki nivo CF += 10
    ---[XOR]

    > Ako ima manje mem za GPU od zeljenog, CF -= 15
    | Ako imas vise mem za GPU od zeljenog, za svaki nivo CF += 10
    ---[XOR]

    > Ako je dijagonala ona zeljena, CF + 15


FAZA: max

    > Nadji max

    * Prelazak na [FAZU: ispis] (salience = -10)

FAZA: ispis

    > Ispisi max

    * Prelazak na [FAZU: max] (ako postoji laptop, salience = -10)
    * Brisanje faze [znaci KRAJ] (ako NE postoji laptop, salience = -10)

'''