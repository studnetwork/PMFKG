# Zadaci za vežbi
* [Vežbe 1][v1]
* [Vežbe 2][v2]
* [Vežbe 3][v3]

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
select distinct mesto, null       --as 'null vrednosti'
from studenti
```
Moguće je dodati alias i kolonama sa fiksnim vrednostima
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

11. Prikazati Studente koji NISU iz Kragujevca ili Kraljeva sortirane po imenu ( opadajuci poredak )
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

## Vežbe 2

1. spisak nastavnika koji nisu angažovani.
<details>
 <summary>Rešenje</summary>

```tsql
select *
from nastavnici
where Snast not in (select snast from Angazovanje)
```
</details>

***

2. svi studenti koji dolaze iz gradova iz kojih je doslo vise od 2 studenta
<details>
 <summary>Rešenje</summary>

```tsql
select *
from nastavnici
where Snast not in (select snast from Angazovanje)
```
</details>

***

3. Broj indeksa, godina upisa, ocena studenata cije su ocene manje od svih ocena koje je dao nastavnik sa "s" u imenu. (ALL, ANY)
<details>
 <summary>Rešenje: prvi način</summary>

```tsql
select indeks, upisan, ocena
from prijave
where ocena < all (
			select ocena 
			from prijave where 
			Snast = ANY (
					select snast 
					from Nastavnici 
					where Imen like '%s%' 
				    )
		  )
```
</details>

<details>
 <summary>Rešenje: drugi način</summary>

```tsql
select indeks, upisan, ocena
from prijave
where ocena < all (
			select ocena 
			from prijave where 
			Snast in (
					select snast 
					from Nastavnici 
					where Imen like '%s%' 
				 )
		   )
```
</details>

***

4. spisak nastavnika i predmeta (samo sifre) koji dele predmet sa jos nekim
<details>
 <summary>Rešenje: prvi način</summary>

```tsql
select Snast, Spred
from Angazovanje a1
where Spred in (
		select Spred
		from Angazovanje a2
		where a1.Snast <> a2.Snast
	       )
```
</details>

<details>
 <summary>Rešenje: drugi način</summary>

```tsql
select a1.Snast, a1.Spred from Angazovanje a1
where exists ( 
		select * 
		from Angazovanje a2 
		where a1.Snast <> a2.Snast and a1.Spred = a2.Spred
	     )
```
</details>

***

5. spisak nastavnika koji nisu angažovani
<details>
 <summary>Rešenje</summary>

```tsql
select * from Nastavnici n
where not exists (
			select * f
			rom Angazovanje a 
			where a.Snast = n.Snast
		 )
```
</details>

***

6. Spisak studenata koji imaju bar jedan polozen ispit
<details>
 <summary>Rešenje</summary>

```tsql
select * from Studenti s
where exists (
		select * 
		from Prijave p 
		where ocena > 5 and s.Indeks = p.Indeks and p.Upisan = s.Upisan
	     )
```
</details>

***

7. Spisak studenata koji imaju prosek veci od 7.5
<details>
 <summary>Rešenje</summary>

```tsql
select * from Studenti s
where exists (
		select Indeks, Upisan 
		from prijave
		where ocena > 5 and s.Indeks = Indeks and s.Upisan = Upisan
		group by Indeks, Upisan -- da li grupisanje moze da se izbaci ?!
		having avg(ocena * 1.0) > 7.5
	     )
```
</details>

***

# Vežbe 3

1. Izlistati imena nastavnika i sifre predmeta koje predaju
<details>
 <summary>Rešenje: prvi način</summary>

```tsql
/*
	Dekartov filtrirani
*/

select Nastavnici.Imen, Angazovanje.Spred
from Nastavnici, Angazovanje
where Nastavnici.Snast = Angazovanje.Snast
```
</details>

<details>
 <summary>Rešenje: drugi način</summary>

```tsql
/*
	INNER JOIN
*/

select n.Imen, a.Spred
from Nastavnici n join Angazovanje a on n.Snast = a.Snast

/*
	LEFT JOIN
*/
```
</details>

***

2. Izlistati imena nastavnika i sifre predmeta koje predaju (u skupu trebaju da se nadju i nastavnici koji nisu angazovani)
<details>
 <summary>Rešenje</summary>

```tsql
select n.Imen, a.Spred
from Nastavnici n LEFT join Angazovanje a on n.Snast = a.Snast
```
</details>

***

3. spisak nastavnika koji nisu angazovani.
<details>
 <summary>Rešenje</summary>

```tsql
select n.Snast 
from Nastavnici n left join Angazovanje a on n.Snast = a.Snast
where a.Snast is null
```
</details>

***

4. spisak nastavnika i predmeta (samo sifre) koji dele predmet sa jos nekim
<details>
 <summary>Rešenje</summary>

```tsql
select a1.Snast, a1.Spred
from Angazovanje a1 join Angazovanje a2 on a1.Spred = a2.Spred and a1.Snast <> a2.Snast
```
</details>

***

5. Izlistati imena nastavnika i NAZIVE predmeta koje predaju
<details>
 <summary>Rešenje</summary>

```tsql
select n.Imen, p.NAZIVP
from Nastavnici n join Angazovanje a on n.Snast = a.Snast
				      join PREDMETI p on a.Spred = p.SPRED
```
</details>

***

6. Spisak brucosa koji imaju druga na fakultetu

<details>
 <summary>Rešenje</summary>

```tsql
select s1.Imes, s2.Imes
from Studenti s1 join Studenti s2 on 
	(s1.Upisan = s2.Upisan and s1.Mesto = s2.Mesto and s1.Indeks != s2.Indeks)
```
</details>

***

7. Spisak studenata (indeks, upisan, ime studenta) koji imaju bar jedan polozen ispit
<details>
 <summary>Rešenje</summary>

```tsql
select distinct s.Indeks, s.Upisan, s.Imes
from Studenti s join Prijave p on s.Indeks = p.Indeks and s.Upisan = p.Upisan
where p.Ocena > 5 
```
</details>

***

8. Spisak studenata koji imaju prosek veci od 7.5
<details>
 <summary>Rešenje</summary>

```tsql
select s.Indeks, s.Upisan, avg(p.Ocena * 1.0)
from Studenti s join Prijave p on s.Indeks = p.Indeks and s.Upisan = p.Upisan
where p.Ocena > 5 
group by s.Indeks, s.Upisan
having avg(p.Ocena * 1.0) > 7.5
```
</details>

***

9. Maksimalna ocena za svaki predmet
<details>
 <summary>Rešenje</summary>

```tsql
select p2.Spred, p2.NAZIVP, max(ocena) 
from prijave p1 join PREDMETI p2 on p1.Spred = p2.SPRED
group by p2.NAZIVP, p2.Spred
```
</details>

***



[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[v1]: ./Zadaci_sa_vežbi.md#Vežbe-1
[v2]: ./Zadaci_sa_vežbi.md#Vežbe-2
[v3]: ./Zadaci_sa_vežbi.md#Vežbe-3