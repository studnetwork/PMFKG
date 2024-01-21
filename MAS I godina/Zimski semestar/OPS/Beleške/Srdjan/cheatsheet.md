# Legenda

| Oznaka          | Opis                                        | Formula                                                               |
|:---------------:|:-------------------------------------------:|:---------------------------------------------------------------------:|
| $n$             | obim uzorka                                 |                                                                       |
| $m$             | aritmeticka sredina                         |                                                                       |
| $M$             | medijana                                    |                                                                       |
| $\bar{X_{n}}$   | srednju vrednost uzorka                     | $\displaystyle\frac {1} {n} \sum_{i=1}^n {X_{i}}$                     |
| $\bar{S_{n}}$   | uzoracka standardna devijacija (odstupanje) | $\sqrt {\bar{S_{n}^2}}$                                               |
| $\bar{S_{n}^2}$ | disperzija uzorka                           | $\displaystyle\frac {1} {n} \sum_{i=1}^n {(X_{i} - \bar{X_{n}})^2}$   |
| $\hat{S_{n}^2}$ | korigovana disperzija uzorka                | $\displaystyle\frac {1} {n-1} \sum_{i=1}^n {(X_{i} - \bar{X_{n}})^2}$ |

# Testovi

Pri testiranju imamo sledece vrednosti:
* `p-value`: opisuje statisticki znacaj dobijenog zakljucka
  * ovako se obicno i oznacava
  * dobija se kao rezultat testa u R-u
  * na osnovu poredjenja sa alfa (nivo znacajnosti) biramo odgovarajucu hipotezu
* `vrednost test statistike`: broj koji predstavlja rezultat test statistike
  * koristimo je kada rucno vrsimo racun
  * proverav se da li se nalazi u kriticnom regionu i na osnovu toga biramo hipotezu
* `vrednost za odgovarajucu tehniku`: vrednost koja predstavlja neku osobinu ili zakljucak
  * koristimo je nakon sto zakljucakom testa potvrdimo da postoji ta neka osobina
  * primer: korelacija izmedju neka 2 obelezja


## Zakljucivanje

Zakljucivanje (R testovi):
1. Izbor testa
2. Odredjivanje $\alpha$
   * ako nije navedemo, koristimo vrednost `0.05`
3. Izbor alternativne hipoteze
4. Vrsimo test
5. Poredimo p-value i $\alpha$
   * ako je $\text{p-value} > \alpha$, prihvatamo $H_{0}$
   * ako je $\text{p-value} \le \alpha$, prihvatamo $H_{1}$

---
   
Zakljucivanje (rucno testiranje):
1. Izbor testa
2. Odredjivanje $\alpha$
   * ako nije navedemo, koristimo vrednost `0.05`
3. Izbor alternativne hipoteze
4. Racunamo **test statistiku**
5. Proveravamo da li vrednost test statistike (oznacene kao `t`), upada u kriticni region (oznacen sa `C`)
   * ako je $t \notin C$, prihvatamo $H_{0}$
   * ako je $t \in C$, prihvatamo $H_{1}$

## t-testovi

### One-Sample t-test

* Parametarski test.
* Testira da li je sredina populacije neki odredjeni broj

---

Uslovi:
* 1 neprekidno obelezje jednog uzorka
* posmatrano obelezje ima normalnu raspodelu

---

Nulta hipoteza - sredine je (jednaka vrednosti) $m_{0}$:

$$
H_{0}(m=m_{0})
$$

---

Test statistika:

$$
t_{n-1} = \frac {\bar{x_{n}} - m_{0}} {\displaystyle\frac {\bar{S_{n}}} {\sqrt{n-1}}}
$$

$n$ je obim uzorka.

### Nezavisni t-test

* Parametarski test (njegova neparametarska alternativa je: [Mann-Whitney test](#mann-whitney-test)).
* Testira da li je sredina populacije neki odredjeni broj

---

Uslovi:
* **po** 1 neprekidno obelezje iz 2 uzorka (grupe)
* posmatrano obelezje ima normalnu raspodelu

---

Nulta hipoteza - sredine u obe grupe su jednake:

$$
H_{0}(m = 0) \\
ili \\
H_{0}(m_{1} = m_{2})
$$

gde je $m_{1}$ sredina jednog uzorka, a $m_{2}$ sredina drugog, a $m = m_{1} - m_{2}$.

---

Test statistika:

$$
t = 
\frac 
    {\bar{X}_{n_{1}} - \bar{X}_{n_{2}}}
    {\displaystyle\sqrt {
      \displaystyle\frac {(n_{1}-1)\hat{S_{1}^2} + (n_{2}-1)\hat{S_{2}^2}} {n_{1}+n_{2}-2} 
      \left(\frac {1} {n_{1}} + \frac {1} {n_{2}}\right)
      }
    }
$$

### Mann-Whitney test

### Pomocni testovi

#### Levinov test

