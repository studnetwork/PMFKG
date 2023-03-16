kosa linija kod trapeznog oblika se racuna preko jednacine prave
(jer je to obicna prava linija)

singltoni su najjednostavniji oblik
potpuno diskretan domen
prikazuju se stubicima (kao barplot)

fuzzy logika se uglavnom koristi u kontrolerskim sistemima

**napomena**: kada imamo vise skupova oni ne moraju da pocinju tamo gde se prethodni zavrsava

u inzenjerskoj primeni najcesce se koriste **trougaone** f-je pripadnosti, npr. za gresku u merenju,
tj. toleranciju greske

Fazi skup obuhvata i vrednosti za koje je stepen pripadnosti `0`

# karakteristike f-je pripadnosti (FP)

**core** (jezgro): svi `x`-ovi za koje je `FP(x) = 1`
**support**: svi `x`-ovi za koje je `FP(x) > 0`
**boundary** (granice): svi `x`-ovi za koje vazi `0 < FP(x) < 1`

**visina fuzzy skupa** je vrednost za koju FP ima maksimalnu vrednost 

fuzzy skup nije normalan ako nema x takvo da vazi `FP(x) = 1`.

U fazi zakljucivanja se mogu dobiti takvi skupovi

**centar fuzzy skupa** je srednja vrednost svih x-ova datog skupa za koje vazi `FP(x) = 1`   
**Napomena**: centar ne mora da bude deo core-a

suprotno od konveksnog fuzzy skupa nije konkavni fuzzy skup vec skup koju nije konvesan.

isto vazi i za konkavni.

konveksan ako za svake dve tacke postoji treca cija je pripadnost veca od pripadnosti neke od te 2 tacke

unija 2 fuzzy skupa se formira tako sto se uzima veca od 2 pripadnosti za neku vrednost

za uniju je suprotno, uzi na se minimum

komplement: `fp_k = 1 - fp(x)`
