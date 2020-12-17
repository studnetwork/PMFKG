# Vodič
U ovom fajlu se nalaze linkovi ka resursima koji su vezani za vežbe i predavanja

## Vežbe
Linkovi do resursa koji se odnose na vežbe  

[Rešenja zadatke sa prvih vežbi i njihova objašnjenja][fajl1]

### Lekcije
Linkovi ka snimcima lekcija:  
1. [Lekcija 1][v-lekcija-1] `Relaciona algebra`  
2. [Lekcija 2][v-lekcija-2] `Relaciona algebra`  
3. [Lekcija 3][v-lekcija-3] `Relaciona algebra`  
4. [Lekcija 4][v-lekcija-4] `Relaciona algebra - priprema za kolokvijum`  
5. [Lekcija 5][v-lekcija-5] `SQL - uvod`  
6. [Lekcija 6][v-lekcija-6] `SQL - podupiti`  
7. [Lekcija 7][v-lekcija-7] `SQL - spajanje`  
8. [Lekcija 8][v-lekcija-8] `SQL - rešavanje prethodnih kolokvijuma`  
9. [Lekcija 9][v-lekcija-9] `SQL - rešavanje prethodnih kolokvijuma`  
10. [Lekcija 10][v-lekcija-10] `SQL - DDL, DML, funkcije, procedure`  
11. [Lekcija 11][v-lekcija-11] `SQL - DDL, DML, procedure, trigeri`  


### Konsultacije
Linkovi ka snimcima konsultacija:  
1. [Konsultacije 1][v-konsultacije-1] `Relaciona algebra - regularni kolokvijum 2018/2019`  
2. [Konsultacije 2][v-konsultacije-2] `Relaciona algebra - kolokvijuma 2017/2018, 5. 2015/2016`  
3. [Konsultacije 3][v-konsultacije-3] `Relaciona algebra - redovni kolokvijum 2019/2020`  
4. [Konsultacije 4][v-konsultacije-4] `Relaciona algebra - redovni kolokvijum 2018/2019, 3. sa redovnog 2015/2016`  


### Napomene
Ukoliko imate problem sa povezivanjem sqllocaldb-a i SSMS-a, probajte da instalirate neku od [starijih vezija][ssms-prev] SSMS-a.  
[SSMS 16.5.3][ssms-16] je testiran i radi bez problema.
***
[Zadatak sa 2. vežbi iz SQL-a (32:56)][v-lekcija-6] je moguće uraditi i sa funkcijom `DATENAME`.  

**Postavka zadatka**:  
	Za svaki ispitni rok ispisati koliko se u njemu polozilo ispita do sada.  
	
**Rešenje sa korišćenjem funkcije `DATENAME`**:  
```sql  
SELECT DATENAME( MONTH, Datump ) AS 'Ispitni rok', COUNT(*) AS 'Broj polozenih ispita'  
FROM prijave  
WHERE ocena > 5 
GROUP BY DATENAME( MONTH, Datump )  
```

## Predavanja
Linkovi do resursa koji se odnose na predavanja  

### Lekcije
Linkovi ka snimcima lekcija:  
1. [Predavanje 1][p-lekcija-1] `Uvod`  
2. [Predavanje 2][p-lekcija-2] `Modeli podataka`  
3. [Predavanje 3][p-lekcija-3] `Modeli podataka`  
4. [Predavanje 4][p-lekcija-4] `Modeli podataka`  
5. [Predavanje 5-1][p-lekcija-5-1deo] `SQL`  
   [Predavanje 5-2][p-lekcija-5-2deo] `SQL`  
6. [Predavanje 6-1][p-lekcija-6-1deo] `SQL`  
   [Predavanje 6-2][p-lekcija-6-2deo] `SQL`  
7. [Predavanje 7][p-lekcija-7] `SQL`  
8. [Predavanje 8][p-lekcija-8] `SQL - pogledi, procedure, funkcije, ...`  
9. [Predavanje 9][p-lekcija-9] `SQL - normalizacija`

### Konsultacije

### Napomene

## Ostalo
[Moodle stranica predmeta][stranica predmeta]


# Napomena
Ukoliko primetite neku grešku, uradite jednu od slećih stvari:
* [napravite "issue"][new issue] sa opisom problema
* kontaktirajte nekog od administratora: Srđan Todorović, Dragor Draganović, Mihajlo Janković  
* ukoliko želite da dodate ili izmenite nešto, [pošaljite "pull request"][pull request]



[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[//]: # ( Vezbe reference )


[//]: # ( linkovi na fajlovima )

[fajl1]: https://github.com/Produktivna-grupa/PMFKG/blob/master/II%20godina/Zimski%20semestar/BP1/Ve%C5%BEbe%20i%20predavanja/Vezbe_1.md#ve%C5%BEbe

[//]: # ( Relaciona algebra, lekcija, 1-4 )

[v-lekcija-1]: https://drive.google.com/file/d/1-YLFmPyby3KBFNJzi4C0mWatFr8spgWy/view?usp=sharing

[v-lekcija-2]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1603199524673

[v-lekcija-3]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1603808042264

[v-lekcija-4]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1603808042264


[//]: # ( SQL, lekcija, 5-8 )

[v-lekcija-5]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1605017608891 "10. Novembar 2020."

[v-lekcija-6]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1605622411838 "17. Novembar 2020."

[v-lekcija-7]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1606831464559 "24. Novembar 2020."

[v-lekcija-8]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1606227128524 "1. Decembar 2020."

[v-lekcija-9]: https://drive.google.com/file/d/13oMg6FVLrjG_BTDNbG6sl68aHJq-V6ME/view?usp=sharing "8. Decembar 2020."

[v-lekcija-10]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1607954763195 "14. Decembar 2020."

[v-lekcija-11]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1608043244227 "15. Decembar 2020."


[//]: # ( Relaciona algebra, konsultacije, 1-4 )

[v-konsultacije-1]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1605268869834 "13. Novembar 2020"

[v-konsultacije-2]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1605524529205 "16. Novembar 2020."

[v-konsultacije-3]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1605533452567 "16. Novembar 2020."

[v-konsultacije-4]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=7725d1ed6e451a3c61c78a15f041b5c3b8234128-1605693649917 "18. Novembar 2020."



[//]: # ( Vezbe napomena reference )

[ssms-prev]: https://docs.microsoft.com/en-us/sql/ssms/release-notes-ssms?view=sql-server-ver15#previous-ssms-releases
[ssms-16]: https://docs.microsoft.com/en-us/sql/ssms/release-notes-ssms?view=sql-server-ver15#1653


[//]: # ( Predavanje reference )

[//]: # ( Relaciona algebra, lekcija, 1-4 )

[p-lekcija-1]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1602508184316 "12. Oktobar 2020."

[p-lekcija-2]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1603113550682 "19. Oktobar 2020."

[p-lekcija-3]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1603721323923 "26. Oktobar 2020."

[//]: # ( SQL, lekcija, 5-6 )

[p-lekcija-4]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1604325690729 "2. Novembar 2020."

[p-lekcija-5-1deo]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1604933625785 "9. Novembar 2020."

[p-lekcija-5-2deo]: https://imi.pmf.kg.ac.rs/imicloud/index.php/s/xhBf0OSk5rYFGnz "9. Novembar 2020."

[p-lekcija-6-1deo]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1606140059438 "23. Novembar 2020."

[p-lekcija-6-2deo]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1606143774271 "23. Novembar 2020."

[p-lekcija-7]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1606744257707 "30. Novembar 2020."

[p-lekcija-8]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1607350405616 "7. Decembar 2020."

[p-lekcija-9]: https://bbb.pmf.kg.ac.rs/playback/presentation/2.0/playback.html?meetingId=938c50b6b05309503772ecb3cd16492b1c875665-1607689063875 "11. Decembar 2020."

[//]: # ( Ostalo reference )

[stranica predmeta]: https://imi.pmf.kg.ac.rs/moodle/course/view.php?id=27



[//]: # ( Napomena reference )

[new issue]: https://github.com/Produktivna-grupa/PMFKG/issues/new
[pull request]: https://github.com/Produktivna-grupa/PMFKG/compare
[vežbe i predavanja]: https://github.com/Produktivna-grupa/PMFKG/tree/master/II%20godina/Zimski%20semestar/BP1/Ve%C5%BEbe%20i%20predavanja
