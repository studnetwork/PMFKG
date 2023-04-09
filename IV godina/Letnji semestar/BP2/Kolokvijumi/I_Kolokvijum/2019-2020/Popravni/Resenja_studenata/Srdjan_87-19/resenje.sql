
-- # Stanje pre optimizacije

-- brzine izvrsenja
-- sp_klijenti_potroseno        # 16.68
-- sp_top_ten_proizvodi         # 14.66
-- sp_stanje_porudzbina         # 2.53
-- sp_odaberi_kamion 30         # 0.40
-- sp_nova_porudzbina 30, 400   # 0.01
-- sp_broj_klijenata            # 0.29

-- ------------------------------

-- # Optimizacija procedure sp_klijenti_potroseno

-- Mozemo da uocimo da su sortiranje i spajanje najsporije operacije.
-- Takodje, postoji dosta Table Scan-ova, a oni nisu brze operacije.

-- Zbog join-ovanja i grupisanja, a takodje i zbog uslova zadatka da postoji PK na atributu id,
-- ne bi mozda bilo lose da se definise klasterovani kljuc nad atributom id u tabeli klijenti

alter table klijenti
add constraint pk_id
primary key (id);

-- ovime smo poboljsali izvrsenje sa 16.68 na 7.70

-- brzine izvrsenja svih upita
-- sp_klijenti_potroseno        # 7.70
-- sp_top_ten_proizvodi         # 14.66
-- sp_stanje_porudzbina         # 2.53
-- sp_odaberi_kamion 30         # 0.40
-- sp_nova_porudzbina 30, 400   # 0.01
-- sp_broj_klijenata            # 0.29

-- --

-- U svim upitima datih procedura, osim kod sp_nova_porudzbina, tabela porudzbine 
-- se spaja sa drugim tabelama po atributu idProizvoda. Osim toga, u
-- proceduri sp_nova_porudzbina se vrsi insert u ovu tabelu sto znaci
-- da bi neklasterovani indeksi usporili izvrsenje spomenute procedure.
-- Imajuci u vidu ove 2 informacije mi mozemo da pretpostavimo da bi
-- pravo resenje za optimizaciju bio klasterovani indeks nad atributom idProizvoda

create clustered index idx_cl_idProizvoda
on porudzbine(idProizvoda);

-- dolazi do neznatnog poboljsanja: sa 7.70 na 7.42

-- brzine izvrsenja svih upita
-- sp_klijenti_potroseno        # 7.42
-- sp_top_ten_proizvodi         # 14.37
-- sp_stanje_porudzbina         # 2.25
-- sp_odaberi_kamion 30         # 0.40
-- sp_nova_porudzbina 30, 400   # 0.01
-- sp_broj_klijenata            # 0.29

-- Sada kada imamo sortiran jedan atribut po kojem se vrsi spajanje preostaje nam da sortiramo 
-- i drugi atribut, iz druge tabele, kako bi te 2 tabele mogle da se spoje Merge Join-om. Ovo
-- mozemo postici definisanjem primarnog kljuca nad atributom id, cime bi smo ujedno i ispunili
-- zahtev iz postavke i definisali klasterovani indeks koji uzrokuje sortiranje podataka po id.

alter table proizvodi
add constraint pk_proizvodi_id 
primary key(id);

-- brzine izvrsenja svih upita
-- sp_klijenti_potroseno        # 6.52
-- sp_top_ten_proizvodi         # 3.64
-- sp_stanje_porudzbina         # 1.87
-- sp_odaberi_kamion 30         # 0.40
-- sp_nova_porudzbina 30, 400   # 0.01
-- sp_broj_klijenata            # 0.29

-- Ovime ne ubrzavamo samo proceduru sp_klijenti_potroseno, koja je ubrzana sa
-- 7.42 na 6.52 vec i procedure sp_top_ten_proizvodi i sp_stanje_porudzbina.

-- Procedura sp_top_ten_proizvodi se znacajno ubrzava, sa 14.37 na 3.64. S obzirom da se dodavanjem
-- klasterovanog indeksa dolazi do uredjenja tabele query processor se odlucuje da ne vrsi prvo
-- joinovanje tabela i nakon toga grupisanje vec prvo izvrsi grupisanje u tabeli proizvodi i
-- sortiranje jer obe operacije ne zavise od tabele proizvodi, a nakon sto zavrsi sve to vrsti
-- spajanje sa tabelom proizvodi ali samo sa odgovarajucim zapisima

-- Procedura sp_stanje_porudzbina se takodje ubrzava jer se umesto Hash Join-a koristi Merge Join
-- zbog toga sto su sada atributi po kojima se vrsi spajanje sortirani.

-- # Optimizacija procedure sp_top_ten_proizvodi

-- Veliki deo posla koji se tice optimizacije brzine izvrsenja ove procedure je vec obavljen
-- u optimizaciji prethodne procedure

-- Najduza operacija jeste operacija sortiranja, ali s obzirom da je rec o agregaciji ne mozemo
-- nista da ucinimo kako bi smo ubrzali tu operaciju

-- # Optimizacija sp_odaberi_kamion 

-- Atributi status i slobodno figurisu u klauzuli WHERE pa mozemo
-- da definisemo kompozitni neklasterovani kljuc iz kojeg bi se
-- te vrednosti dobavljale. Takodje, atribut slobodno se javlja
-- u klauzuli ORDER BY pa je zbog toga takodje pogodno koristiti
-- neklasterovani kljuc. Zbog ORDER BY-a bilo bi pozeljno da se
-- sortiranje vrsi po atributu slobodno, dok je za WHERE pozeljno
-- da se sortiranje vrsi prvo po statusu pa tek onda po atributu 
-- slobodno, ali kako ce se WHERE-om filtrirati zapisi, a zatim taj
-- rezultat sortirati onda je WHERE bolja opcija. Redukovan skup
-- zapisa ce biti poslat na sortiranje, a kako je manji broj zapisa
-- onda je i manje vreme izvrsenja tog sortiranja.

-- Kako bi se izbeglo pristupanje memoriji, a i kako bi smo ispunili
-- zahtev iz postavke u kome se navodi da mora da postoji PK, definisemo
-- PK nad atributom id. Time ujedno i resavamo nedostatak tog atributa
-- pri radu sa neklasterovanim indeksom. Ovime ce se atribut id nacin
-- na mestu RID-a.


alter table kamioni
add constraint pk_kamioni_id 
primary key(id);

create nonclustered index idx_ncl_status_slobodno
on kamioni(status, slobodno);

-- brzine izvrsenja svih upita
-- sp_klijenti_potroseno        # 6.52
-- sp_top_ten_proizvodi         # 3.64
-- sp_stanje_porudzbina         # 1.87
-- sp_odaberi_kamion 30         # 0.003
-- sp_nova_porudzbina 30, 400   # 0.01
-- sp_broj_klijenata            # 0.29

-- # Optimizacija sp_nova_porudzbina 

-- Ovu proceduru ne mozemo da optimizujemo jer klasterovani indeksi
-- nemaju uticaja na izvrsenje, a neklasterovani ga samo usporavaju.

-- Time sto smo izbegli definisanje neklasterovanog indeksa smo ujedno
-- i omogucili da se ova procedura izvrsava optimalno

-- # Optimizacija sp_broj_klijenata

-- Upit u ovoj proceduri je jednostavan. Sadrzi samo agregaciju.
-- Mozemo da ga ubrzamo definisanjem neklasterovanog indeksa nad
-- nekim atributom. Zbog optimizacija koje MS SQL Server izvodi
-- pozeljni je da se to uradi nad id-jem.

-- Izvrsenje se ubrzava zato sto se izbegava pristup skladistu.
-- Svi potrebni podaci bi se nalazili u samom indeksu

create nonclustered index idx_ncl_id
on klijenti(id);

-- brzine izvrsenja svih upita
-- sp_klijenti_potroseno        # 6.52
-- sp_top_ten_proizvodi         # 3.64
-- sp_stanje_porudzbina         # 1.87
-- sp_odaberi_kamion 30         # 0.003
-- sp_nova_porudzbina 30, 400   # 0.01
-- sp_broj_klijenata            # 0.133

-- # Rezultat

-- brzine izvrsenja
-- sp_klijenti_potroseno        # 16.68 | 06.52
-- sp_top_ten_proizvodi         # 14.66 | 03.64
-- sp_stanje_porudzbina         # 02.53 | 01.87
-- sp_odaberi_kamion 30         # 00.40 | 00.003
-- sp_nova_porudzbina 30, 400   # 00.01 | 00.01
-- sp_broj_klijenata            # 00.29 | 00.133
--                              ----------------
--                                34.57 | 12.176 => ubrzanje ~22.394


-- # Spisak naredbi za kreiranje indeksa 

-- ## klijenti 

-- alter table klijenti
-- add constraint pk_id
-- primary key (id);


-- ## porudzbine

-- create clustered index idx_cl_idProizvoda
-- on porudzbine(idProizvoda);

-- ## proizvodi

-- alter table proizvodi
-- add constraint pk_proizvodi_id 
-- primary key(id);


-- ## kamioni 

-- alter table kamioni
-- add constraint pk_kamioni_id 
-- primary key(id);

-- create nonclustered index idx_ncl_status_slobodno
-- on kamioni(status, slobodno);
