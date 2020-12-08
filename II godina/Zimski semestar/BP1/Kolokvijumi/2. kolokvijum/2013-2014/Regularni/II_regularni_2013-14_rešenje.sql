USE KATASTAR 

/*
Zadatak 1. (ime, prezime)
Napisati SQL upit kojim se ispisuju imena i prezimena vlasnika koji u trenutku izvršenja upita imaju manje
od 23 godinu starosti (23 i manje).
*/

SELECT ime, prezime, DATEDIFF(YEAR, datumRodjenja, GETDATE()) AS godina
FROM Vlasnik
WHERE DATEDIFF(YEAR, datumRodjenja, GETDATE()) <= 23

/*
Zadatak 2. (šifra, naziv)
Napisati SQL upit koji ispisuje šifre i nazive parcela koje su tipa “Građevinsko zemljište” i koje na datum
24.05.2013. imaju najviše 2 vlasnika
*/

SELECT pa.sifra, pa.naziv, COUNT(po.sifraVlasnika) AS kolikoVlasnika
FROM parcela pa JOIN tip t
				ON pa.sifratipa = t.sifra AND t.naziv = 'Gradjevinsko zemljiste'
				JOIN posed po
				ON po.sifraParcele = pa.sifra
WHERE (po.datumPocetka <= '2013-05-24' OR po.datumPocetka IS NULL) AND (po.datumZavrsetka >= '2013-05-24' OR po.datumZavrsetka IS NULL) 
GROUP BY pa.sifra, pa.naziv
HAVING COUNT(po.sifraVlasnika) <= 2

/*
Zadatak 3. (šifra, naziv, meseci)
Napisati SQL upit kojim se za svaku parcelu ispisuje njena šifra i naziv kao i najduži vremenski period (u
mesecima) tokom kojeg je parcela bila ili još uvek jeste u nečijem vlasništvu (bilo kog vlasnika). Za parcele
gde je datum završetka vlasništva NULL, vreme posmatrati od datuma početka vlasništva do vremena
izvršavanja upita.
*/

SELECT p.sifraParcele, pa.naziv, MAX(CASE
			WHEN p.datumZavrsetka IS NULL THEN DATEDIFF(MONTH, p.datumPocetka, GETDATE())
			ELSE DATEDIFF(MONTH, p.datumPocetka, p.datumZavrsetka)
		  END) AS meseci
FROM posed p JOIN parcela pa
				ON p.sifraParcele = pa.sifra
GROUP BY p.sifraParcele, pa.naziv

/*
Zadatak 4. (šifraParcele)
Napisati SQL upit koji ispisuje šifre parcela koje nijednom nisu menjale svog vlasnika. ž
U upitu je OBAVEZNO koristiti UGNJEŽDENE upite, a nije dozvoljeno koristiti JOIN mehanizam i poglede.
*/


INSERT INTO parcela (sifra, naziv, povrsina, sifraTipa) VALUES (1991, 'Zvezda', 55851, 1);
INSERT INTO parcela (sifra, naziv, povrsina, sifraTipa) VALUES (2017, 'Zvezda', 55851, 2);
INSERT INTO parcela (sifra, naziv, povrsina, sifraTipa) VALUES (2018, 'Test', 357, 2);
INSERT INTO parcela (sifra, naziv, povrsina, sifraTipa) VALUES (2019, 'Test2', 1545, 3);

INSERT INTO posed (sifraParcele, sifraVlasnika, datumPocetka, datumZavrsetka) VALUES (1991, 1, '1991-05-29', '2017-12-08');
INSERT INTO posed (sifraParcele, sifraVlasnika, datumPocetka, datumZavrsetka) VALUES (2017, 2, '1991-05-29', '2017-12-08');
INSERT INTO posed (sifraParcele, sifraVlasnika, datumPocetka, datumZavrsetka) VALUES (2018, 2, '1991-05-29', '2017-12-08');
INSERT INTO posed (sifraParcele, sifraVlasnika, datumPocetka, datumZavrsetka) VALUES (2019, 3, '1991-05-29', '2017-12-08');

SELECT *
FROM posed p1
WHERE NOT EXISTS
(
	SELECT *
	FROM posed p2
	WHERE p1.sifraVlasnika != p2.sifraVlasnika AND p1.sifraParcele = p2.sifraParcele
)

/*
Zadatak 5. (šifra, ime, prezime)
Napisati SQL upit kojim se ispisuje šifra, ime i prezime vlasnika koji trenutno poseduje najvecu ukupnu
površinu svih svojih parcela (ne deli vlasništvo ni sa kim). U obzir se uzimaju samo parcele koje poseduje
samostalno.
*/

CREATE VIEW sviVlasniciIPovrsina AS
SELECT v.sifra, v.ime, SUM(pa.povrsina) AS ukupnaPovrsina
FROM posed p1 LEFT JOIN posed p2 
				ON p1.sifraParcele = p2.sifraParcele AND p1.sifraVlasnika != p2.sifraVlasnika
			  JOIN parcela pa 
			    ON p1.sifraParcele = pa.sifra
			  JOIN vlasnik v
			    ON p1.sifraVlasnika = v.sifra
WHERE p2.datumPocetka IS NULL
GROUP BY v.sifra, v.ime

SELECT s1.*
FROM sviVlasniciIPovrsina s1 LEFT JOIN sviVlasniciIPovrsina s2
							 ON s1.ime != s2.ime AND s1.sifra != s2.sifra AND s1.ukupnaPovrsina < s2.ukupnaPovrsina
WHERE s2.ime IS NULL

/*
Zatatak 6. (šifraParcele)
Napisati SQL upit kojim se ispisuju šifre parcela koje su imale ili imaju “rupe” u vlasništvu tj. kod kojih
postoji bar 1 vremenski period (makar 1 dan) u kome nisu imale nijednog vlasnika.
*/

SELECT pa.sifra
FROM parcela pa LEFT JOIN posed po1
				ON pa.sifra = po1.sifraParcele
				LEFT JOIN posed po2
				ON po1.sifraVlasnika != po2.sifraVlasnika AND po1.sifraParcele = po2.sifraParcele
WHERE po1.sifraParcele IS NULL OR po1.datumZavrsetka < po2.datumPocetka
