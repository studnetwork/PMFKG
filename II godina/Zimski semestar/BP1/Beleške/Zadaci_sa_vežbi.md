# Zadaci za vežbi
* [Vežbe 1][v1]
* [Vežbe 2][v2]
* [Vežbe 3][v3]
* [Vežbe 4][v4]

## Vežbe 1

1. Prikazati spisak svih studenata
<details>
 <summary>Rešenje</summary>

```tsql
select *
from studenti
```
</details>

***

2. Prikazati Imes, indeks, upisan, mesto iz tabele STUDENTI
<details>
 <summary>Rešenje</summary>

```tsql
select Imes, indeks, upisan, mesto
from studenti
```
</details>

***

3. Prikazati Imes, Indeks, Upisan, Datr iz tabele studenti, gde je Datr naslovljena kao 'Datum rodjenja'
<details>
 <summary>Rešenje</summary>

```tsql
select Imes, indeks, upisan, mesto, Datr as 'Datum rodjenja'
from studenti
```
</details>

***

4. Selektovati različita mesta iz tabele Studenti, i dopisati kolonu sa NULL vrednostima
<details>
 <summary>Rešenje</summary>

```tsql
select distinct mesto
from studenti
```
</details>

***

5. Prikazati podatke o studentima koji su upisani 2000 godine
<details>
 <summary>Rešenje</summary>

```tsql
select *
from studenti
where upisan = 2000
```
</details>

***

6. Prikazati sve studente koji su upisani izmedju 2000 i 2005
<details>
 <summary>Rešenje</summary>

```tsql
select *
from studenti
where upisan between 2000 and 2005
```
</details>

***

7. Prikazati Studente koji su iz Kragujevca ili Kraljeva
<details>
 <summary>Rešenje</summary>

```tsql
select *
from studenti
where mesto in ('Kragujevac', 'Kraljevo')
```
</details>

***

8. Prikazati Studente koji NISU iz Kragujevca ili Kraljeva
<details>
 <summary>Rešenje</summary>

```tsql
select *
from studenti
where mesto not in ('Kragujevac', 'Kraljevo')
```
</details>

***

9. Prikazati sve studente koji dolaze iz grada čije ime počinje na "K"
<details>
 <summary>Rešenje</summary>

```tsql
select *
from studenti
where mesto like 'K%'
```
</details>

***

10. Prikazati studente za koje je nepoznat datum rodjenja
<details>
 <summary>Rešenje</summary>

```tsql
select *
from studenti
where datr is null
```
</details>

***

11. Prikazati Studente koji NISU iz Kragujevca ili Kraljeva sortirane po imenu (od najmanjeg ka najvećem)
<details>
 <summary>Rešenje</summary>

```tsql
select *
from studenti
where mesto not in ('Kragujevac', 'Kraljevo')
order by Imes desc
```
</details>

***

12. Za svako ime studenta kreirati kolonu u kojoj će pisati njegov Indeks kao "br_indeksa/godina" (CONCAT i CAST)
<details>
 <summary>Rešenje: prvi način</summary>

```tsql
select Imes, CONCAT(Indeks, '/', Upisan) as Indeks
from Studenti
```
</details>

<details>
 <summary>Rešenje: drugi način</summary>

```tsql
select Imes, CAST(Indeks as varchar(5)) + '/' + CAST(Upisan as varchar(5))
from Studenti
```
</details>

***

13. Pronađi smeštaj - Prikazati sve studente i dodati kolonu u kojoj za studente koji nisu iz Kragujevca piše vrednost "Potraban smestaj", u suprotnom piše "Lokalno"
<details>
 <summary>Rešenje</summary>

```tsql
select Imes, 
case Mesto
	when 'Kragujevac' then 'LOKALNO'
	else 'POTREBAN SMESTAJ'
end as 'Smestaj'
from Studenti
```
</details>

***

14. Selektovati sve ocene iz prijava, i dodati kolonu koja za svaku ocenu ispisuje da li je ocena  
--		"Ispod proseka" (5.6),  
--		"Prosek" (7,8),  
--		"Odlicna" (9)  
--		"Izuzetna" (10)  
<details>
 <summary>Rešenje</summary>

```tsql
select Indeks, Upisan, Spred, 
	case 
		when Ocena > 5 and Ocena < 7 then 'Ispod proseka'
		when Ocena >= 7 and Ocena < 9 then 'Proseck'
		when Ocena = 9 then 'Odlicana'
		else 'Izuzetana' 
	end as Status
from Prijave
```
</details>

***

15. Prikazati godišta i starost, svih studenata koji imaju više od 25 godina
<details>
 <summary>Rešenje</summary>

```tsql
select Imes, Indeks, Upisan, DATEPART(year, datr) as 'Godina', DATEDIFF(year, datr, GETDATE()) as Starost
from Studenti
where DATEDIFF(year, datr, GETDATE()) > 25
```
</details>

***

16. Prikazati broj studenata koji su upisani na PMF-u
<details>
 <summary>Rešenje</summary>

```tsql
select COUNT(*)
from Studenti
```
</details>

***

17. Prikazati broj studenata koji su upisani na PMF-u, a imaju poznat datum rodjenja
<details>
 <summary>Rešenje</summary>

```tsql
select COUNT(datr)
from Studenti
```
</details>

***

18. Prikazati prosečnu, minimalnu i maksimalnu ocenu na predmetu sa šifrom 23
<details>
 <summary>Rešenje: prvi način</summary>

```tsql
select MAX(ocena) as minimalna, MIN(ocena) as maksimalna, AVG(cast(ocena as real)) as prosecna
from Prijave
where Spred = 23
```
</details>

<details>
 <summary>Rešenje: drugi način</summary>

```tsql
select MAX(ocena) as minimalna, MIN(ocena) as maksimalna, AVG(ocena * 1.0) as prosecna
from Prijave
where Spred = 23
```
</details>

***

19. Za svako mesto ispisati koliko studenata dolazi iz njega.
<details>
 <summary>Rešenje</summary>

```tsql
select Mesto,count(*) as 'broj studenata'
from Studenti
group by Mesto
```
</details>

***

20. Za svako godište studenata koje se pojavljuje u tabeli Studenti, ispisati broj studenata koji su rođeni te godine.
<details>
 <summary>Rešenje</summary>

```tsql
select datepart(year, Datr) godiste, COUNT(*) as 'broj studenata'
from studenti
group by datepart(year, Datr)
```
</details>

***

21. Sa svakog studenta (indeks, upisan) ispisati koliko ispita je polozio i njegovu prosečnu ocenu
<details>
 <summary>Rešenje</summary>

```tsql
select Indeks, Upisan, count(*) 'broj polozenih', Avg(cast(Ocena as real)) as Prosek
from Prijave
group by Indeks, Upisan
```
</details>

***

22. Prikazati sve studente koji imaju prosek veći od 6
<details>
 <summary>Rešenje</summary>

```tsql
select Indeks, Upisan, Avg(cast(Ocena as real)) as Prosek
from Prijave
group by Indeks, Upisan
having Avg(cast(Ocena as real)) > 6.0
```
</details>

***

23. Koji predmeti se drže na više različitih smerova (group by + having)
<details>
 <summary>Rešenje</summary>

```tsql
select Spred, count(*)
from Planst
group by Spred
having count(Ssmer) > 1
```
</details>

***

24. Koliko ima predmeta na svakoj godini?
<details>
 <summary>Rešenje</summary>

```tsql
select (semestar + 1) / 2 as Godina, count(*) as Br
from Planst
group by (semestar + 1) / 2
```
</details>

***

25. Za svaki predmet ispisati kada je poslednji put polagan?
<details>
 <summary>Rešenje</summary>

```tsql
select spred, max(datump)
from Prijave
group by spred
```
</details>

***

26. Poslednji polozen predmet za svakog studenta?
<details>
 <summary>Rešenje</summary>

```tsql
select indeks, upisan, max(datump)
from Prijave
where ocena > 5
group by Indeks, Upisan
```
</details>

***

27. Za svaki ispitni rok ispisati koliko se u njemu položilo ispita do sada?  

		    rbr_meseca, rok  
			1, Jan  
			2, Feb  
			6, Jun  
		    8, Avg  
		    9, Sept  
		    10 Okt  
<details>
 <summary>Rešenje</summary>

```tsql
select DATEPART(m, datump) as mesec, count(*) as Broj, 
	case datepart(m, datump)
		when 1 then 'Januarski'
		when 2 then 'Feb'
		when 6 then 'Jun'
		when 8 then 'Avg'
		when 9 then 'Sept'
		when 10 then 'Okt'
	end as Rok
from Prijave
where ocena > 5
group by datepart(m, datump)
```
</details>

***

28. Prikazati uspeh (prosečnu ocenu) svake generacije
<details>
 <summary>Rešenje</summary>

```tsql
select upisan generacija, avg(ocena * 1.0)
from prijave
where ocena > 5
group by upisan
```
</details>



[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[v1]: ./Zadaci_sa_vežbi.md#Vežbe-1
[v2]: ./Zadaci_sa_vežbi.md#Vežbe-2
[v3]: ./Zadaci_sa_vežbi.md#Vežbe-3
[v4]: ./Zadaci_sa_vežbi.md#Vežbe-4