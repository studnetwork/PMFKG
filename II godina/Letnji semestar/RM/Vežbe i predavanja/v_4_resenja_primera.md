## Hamingov kod

 
#### 1. Pošiljalac treba da pošalje niz bitova vrednosti 0xCCAA. Koristeći Hamingov kod, napisati tok bitova koji se stvarno šalje. Ako je 7. bit sa desne stane invertovan, dokazati da primalac detektuje grešku.

0xCCAA = 1100 1100 1010 1010

Tok bitova koji će biti poslat:  
**10**1**0**100**0**1100101**0**01010  


Invertovanje 7. bita sa desne strane:  
10101000110010**0**001010  

Provera:  
p1: zbir je 4, a p1 je 1 => greška

p2: zbir je 3, a p2 je 0 => greška

p4: zbir je 3, a p4 je 0 => greška

p8: zbir je 3, a p8 je 0 => greška

p16: zbir je 2, a p16 je 0 => ispravno


Pozicija greške: 1+2+4+8=15  
Greška se nalazi na bitu sa rednim brojem 15, tj. bitu koji smo invertovali



#### 2. Pošiljalac treba da pošalje niz bitova vrednosti 0x0F0F. Koristeći Hamingov kod, napisati tok bitova koji se stvarno šalje. Ako je 4 bit sa desne stane invertovan, dokazati da primalac detektuje grešku.

0x0F0F = 0000 1111 0000 1111  

[0][0]0[1]000[0]1111000[0]01111  

Tok bitova koji će biti poslat:  
000100001111000001111

Invertovanje 4. bita sa desne strane:  
00010000111100000**0**111  


Provera:
p1: zbir je 4, a p1 je 0 => ispravno

p2: zbir je 3, a p2 je 0 => greška

p4: zbir je 3, a p4 je 1 => ispravno

p8: zbir je 4, a p8 je 0 => ispravno

p16: zbir je 3, a p16 je 0 => greška


Pozicija greške: 2+16=18  
Greška se nalazi na bitu sa rednim brojem 18, tj. bitu koji smo invertovali

---

## Cyclic Redundancy Check (CRC)

#### 1. Pošiljalac treba da pošalje niz bitova vrednosti 0xCCAA. Napisati tok bitova koji se stvarno šalje, ako se za prenos koristi standardna CRC metoda sa generatorskim polinomom 𝑥<sup>5</sup> + 𝑥<sup>4</sup> + x<sup>3</sup>.

0xCCAA = 1100 1100 1010 1010

G(x) = x<sup>5</sup> + x<sup>4</sup> + x<sup>3</sup> == 111000

Stepen geratora je 5, pa iz tog razloga dodajemo 5 nula:  
1100110010101010**00000**  

```
110011001010101000000
111000|||||||||||||||
------V||||||||||||||
 010110||||||||||||||
 000000||||||||||||||
 ------V|||||||||||||
  101100|||||||||||||
  111000|||||||||||||
  ------V||||||||||||
   101001||||||||||||
   111000||||||||||||
   ------V|||||||||||
    100010|||||||||||
    111000|||||||||||
    ------V||||||||||
     110101||||||||||
     111000||||||||||
     ------V|||||||||
      011010|||||||||
      000000|||||||||
      ------V||||||||
       110101||||||||
       111000||||||||
       ------V|||||||
        011010|||||||
        000000|||||||
        ------V||||||
         110101||||||
         111000||||||
         ------V|||||
          011010|||||
          000000|||||
          ------V||||
           110100||||
           111000||||
           ------V|||
            011000|||
            000000|||
            ------V||
             110000||
             111000||
             ------V|
              010000|
              000000|
              ------V
               100000
               111000
               ------
                11000
```

Ostatak je: 11000

Tok bitova koji se šalje:  
1100110010101010**11000**

