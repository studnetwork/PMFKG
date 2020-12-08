USE Praksa

/*
1. Ispisati nazive firmi i tehnologija koje koriste, sortiran prema nazivima
tehologija rastuće, a nazivima firmi opadajuće. U spisku treba da se nadju
samo firme sa sedištem u Kragujevcu ili Kraljevu, i samo tehnologije koje u
svom nazivu sadrže JavaScript, Css ili Php.
*/

SELECT f.Naziv, t.naziv
FROM Firma f JOIN ProfilFirme p
				ON p.IDFirme = f.IDFirme AND (f.Sediste = 'Kragujevac' OR f.Sediste = 'Kraljevo')
			 JOIN Tehnologije t
			    ON p.TehID = t.TehID AND (t.naziv = 'JavaScript' OR t.naziv = 'Css' OR t.naziv = 'Php')
ORDER BY t.naziv ASC, f.Naziv DESC

/*
2. Ispisati imena studenata koji su i vlasnici bar jedne firme. (ugnježdeni) 
*/

SELECT o.ime, o.Prezime, o.jmbg
FROM osoba o
WHERE o.JMBG IN
(
	SELECT s.JMBG
	FROM student s
	WHERE EXISTS
	(
		SELECT f.JMBGVlasnika
		FROM Firma f
		WHERE s.jmbg = f.JMBGVlasnika
	)
)

/* 
3. Ispisati:
a) ID
b) naziv
Najčešće navođene firme od strane studenata u anketi vezanoj za praksu (ne
uzimajući u obzir poziciju u listi želja).
*/

SELECT a.IDFirme, f.Naziv, COUNT(*) AS koliko
FROM AnketaStudent a JOIN Firma f
					 ON a.IDFirme = f.IDFirme
GROUP BY a.IDFirme, f.Naziv

/*
4. Naći win-win parove. Jedan win-win par čine firma i student gde je firma prva
na listi želja tog studenta, a student najbolji od onih koji datu firmu
traže. (studenti se porede po prosecima, pa po godinama)
*/

INSERT INTO osoba VALUES ('1312996720027', 'Test', 'Testovic', 'Testa Testovica 22', 'Kragujevac');
INSERT INTO student VALUES (11, 2010, '1312996720027', 9.9);

INSERT INTO osoba VALUES ('1234567891234', 'Pohovana', 'Veverica', 'Letece Lopte 2', 'Kragujevac');
INSERT INTO student VALUES (93, 2015, '1234567891234', 8.6);
INSERT INTO AnketaStudent VALUES (93, 2015, 2, 1);

CREATE VIEW zaSvakogStudentaWinFirma AS
SELECT s.*, a.IDFirme, a.rbr
FROM student s JOIN anketaStudent a
				ON s.indeks = a.indeks AND s.upisan = a.upisan AND a.rbr = 1

CREATE VIEW winProsek AS
SELECT z1.*
FROM zaSvakogStudentaWinFirma z1 LEFT JOIN zaSvakogStudentaWinFirma z2
									ON z1.IDFirme = z2.IDFirme AND z1.prosek < z2.prosek
WHERE z2.Indeks IS NULL

SELECT w1.indeks, w1.upisan, o.ime, o.prezime, w1.prosek, f.naziv, f.Sediste
FROM winProsek w1 LEFT JOIN winProsek w2
					ON w1.upisan < w2.upisan AND w1.IDFirme = w2.IDFirme
				  JOIN osoba o
					ON o.JMBG = w1.JMBG
				  JOIN firma f
					ON f.IDFirme = w1.IDFirme
WHERE w2.IDFirme IS NULL

/*
5. Naći firmu koja dobija najviše najboljih studenata – firma koja je najčešće
navedena u prve tri želje najboljeg studenta iz svake generacije.
*/

CREATE VIEW najboljiStudenti AS
SELECT s1.*
FROM student s1 LEFT JOIN student s2 
				ON s1.upisan = s2.upisan AND s1.prosek < s2.prosek
WHERE s2.Indeks IS NULL
--ORDER BY s1.upisan, s1.indeks

SELECT a.idfirme, f.naziv, COUNT(*) AS koliko
FROM najboljiStudenti n JOIN AnketaStudent a
						ON n.indeks = a.indeks AND n.upisan = a.upisan AND a.rbr <= 3
						JOIN firma f
						ON f.IDFirme = a.IDFirme
GROUP BY a.IDFirme, f.naziv
