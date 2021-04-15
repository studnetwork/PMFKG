### 1. Za niz bitova 0x7FFE odrediti koeficijente Furijeove funkcije.

0111 1111 1111 1110

```
. ______________ .
_|..............|_ 

```
---

Formule:  
<var>
    a<sub>n</sub> = (2/T) &int;<sub>0</sub><sup>T</sup> g(t)sin(2&pi;nft)dt
</var>

<var>
    b<sub>n</sub> = (2/T) &int;<sub>0</sub><sup>T</sup> g(t)cos(2&pi;nft)dt
</var>

<var>
    c = (2/T) &int;<sub>0</sub><sup>T</sup>g(t)dt
</var>

---

<var>

a<sub>n</sub> =
(2/T)( &int;<sub>T/16</sub><sup>15T/16</sup> 1 * sin(2&pi;nft)dt ) =

> 2&pi;nft = x  
> 2&pi;nfdt = dx  
> dt = dx/(2&pi;nf)  
> 
> (2&pi;nfT)/16 = (&pi;nfT)/8 = (&pi;n)/8

= 2/(2&pi;nfT) * (&int;<sub>&pi;n/8</sub><sup>15&pi;n/8</sup> sin(x)dx )) =

= 1/(&pi;n) * (-1) * cos(x)|<sub>&pi;n/8</sub><sup>15&pi;n/8</sup> =

= 1/(&pi;n) * ( cos(&pi;n/8) - cos(15&pi;n/8) ) =

= **1/(&pi;n) * ( cos(0.125&pi;n) - cos(1.875&pi;n) )**

</var>

---

<var>

b<sub>n</sub> =
(2/T)( &int;<sub>T/16</sub><sup>15T/16</sup> 1*cos(2&pi;nft)dt ) =

> 2&pi;nft = x  
> 2&pi;nfdt = dx  
> dt = dx/(2&pi;nf)  
> 
> (2&pi;nfT)/16 = (&pi;nfT)/8 = (&pi;n)/8

= 2/(2&pi;nfT) * (&int;<sub>&pi;n/8</sub><sup>15&pi;n/8</sup> cos(x)dx )) =

= 1/(&pi;n) * sin(x)|<sub>&pi;n/8</sub><sup>15&pi;n/8</sup> =

= **1/(&pi;n) * ( sin(1.875&pi;n) - sin(0.125&pi;n) )**

</var>

---

<var>

c =(2/T) &int;<sub>T/16</sub><sup>15T/16</sup>dt =

= (2/T) * t|<sub>T/16</sub><sup>15T/16</sup> =

= (2/T) * ( (1/16) * 15T - (1/16) * T ) =

= (2/T) * (1/16) * 14 * T = 2 * 14 / 16 =

= 14/8 = 7/4 = **1.75**

</var>

---

<var>

a<sub>n</sub> = 1/(&pi;n) * ( cos(0.125&pi;n) - cos(1.875&pi;n) )

b<sub>n</sub> = 1/(&pi;n) * ( sin(1.875&pi;n) - sin(0.125&pi;n) )

c = 1.75

</var>

---

---


### 2. Za niz bitova 0x7E0F odrediti koeficijente Furijeove funkcije.

0111 1110 0000 1111

```
. ______ ..... ____
_|......|_____|....|
```

---
Formule:  
<var>
    a<sub>n</sub> = (2/T) &int;<sub>0</sub><sup>T</sup> g(t)sin(2&pi;nft)dt
</var>

<var>
    b<sub>n</sub> = (2/T) &int;<sub>0</sub><sup>T</sup> g(t)cos(2&pi;nft)dt
</var>

<var>
    c = (2/T) &int;<sub>0</sub><sup>T</sup>g(t)dt
</var>

---

<var>

a<sub>n</sub> =
(2/T)( &int;<sub>T/16</sub><sup>7T/16</sup> 1 * sin(2&pi;nft)dt + &int;<sub>12T/16</sub><sup>16T/16</sup> 1 * sin(2&pi;nft)dt) =

> 2&pi;nft = x  
> 2&pi;nfdt = dx  
> dt = dx/(2&pi;nf)  
> 
> 2&pi;nf(T/16) = (&pi;nfT)/8 = (&pi;n)/8

= 2/(2&pi;nfT) * (&int;<sub>&pi;n/8</sub><sup>7&pi;n/8</sup> sin(x)dx + &int;<sub>12&pi;n/8</sub><sup>16&pi;n/8</sup> sin(x)dx)) =

= 1/(&pi;n) * (-1) * ( cos(x)|<sub>&pi;n/8</sub><sup>7&pi;n/8</sup> + cos(x)|<sub>12&pi;n/8</sub><sup>16&pi;n/8</sup> ) =

= 1/(&pi;n) * (-1) * ( cos(7/8&pi;n) - cos(1/8&pi;n) + cos(16/8&pi;n) - cos(12/8&pi;n) ) 

= 1/(&pi;n) * (-1) * ( cos(0.875&pi;n) - cos(0.125&pi;n) + cos(2&pi;n) - cos(1.5&pi;n) ) = 

= **1/(&pi;n) * ( cos(0.125&pi;n) - cos(0.875&pi;n) + cos(1.5&pi;n) - cos(2&pi;n) )**

</var>

---

<var>

b<sub>n</sub> =
(2/T)( &int;<sub>T/16</sub><sup>7T/16</sup> 1 * cos(2&pi;nft)dt + &int;<sub>12T/16</sub><sup>16T/16</sup> 1 * cos(2&pi;nft)dt) =

> 2&pi;nft = x  
> 2&pi;nfdt = dx  
> dt = dx/(2&pi;nf)  
> 
> 2&pi;nf(T/16) = (&pi;nfT)/8 = (&pi;n)/8

= 2/(2&pi;nfT) * (&int;<sub>&pi;n/8</sub><sup>7&pi;n/8</sup> cos(x)dx + &int;<sub>12&pi;n/8</sub><sup>16&pi;n/8</sup> cos(x)dx)) =

= 1/(&pi;n) * ( sin(x)|<sub>&pi;n/8</sub><sup>7&pi;n/8</sup> + sin(x)|<sub>12&pi;n/8</sub><sup>16&pi;n/8</sup> ) =

= 1/(&pi;n) * ( sin(0.875&pi;n) - sin(0.125&pi;n) + sin(2&pi;n) - sin(1.5&pi;n) ) = 

= **1/(&pi;n) * ( sin(0.875&pi;n) - sin(0.125&pi;n) + sin(2&pi;n) - sin(1.5&pi;n) )** 

</var>

---

<var>

c = (2/T) ( &int;<sub>T/16</sub><sup>7/16</sup>dt + &int;<sub>12T/16</sub><sup>16T/16</sup>dt ) =

= (2/T) * ( t|<sub>T/16</sub><sup>7T/16</sup> + t|<sub>12T/16</sub><sup>16T/16</sup> ) =

= (2/T) * ( (1/16) * 7T - (1/16) * T + (1/16) * 16T - (1/16) * 12T ) =

= (2/T) * (1/16) * ( 7T - T + 16T - 12T ) =

= 2/(16T) * 10 * T = 1/8 * 10 = **1.25**

</var>

---

<var>

a<sub>n</sub> = 1/(&pi;n) * ( cos(0.125&pi;n) - cos(0.875&pi;n) + cos(1.5&pi;n) - cos(2&pi;n) )

b<sub>n</sub> =  1/(&pi;n) * ( sin(0.875&pi;n) - sin(0.125&pi;n) + sin(2&pi;n) - sin(1.5&pi;n) )

c = 1.25

</var>