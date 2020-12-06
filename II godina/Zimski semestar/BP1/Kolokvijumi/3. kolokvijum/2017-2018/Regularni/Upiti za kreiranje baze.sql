create database dakar10

go

use dakar10

/*
drop table prolazna_vremena
drop table etape
drop table vozaci
drop table vozila
drop table tip_vozila
*/

go

create table tip_vozila
(
	id_tipa int,
	naziv varchar(10),
	constraint pk_tip_vozila primary key (id_tipa)
)

go

insert into tip_vozila values (1, 'motor')
insert into tip_vozila values (2, 'automobil')

create table vozila
(
	id_vozila int,
	marka varchar(10),
	id_tipa int,
	constraint pk_vozila primary key (id_vozila),
	constraint fk_vozila foreign key (id_tipa) references tip_vozila(id_tipa)
)

go

insert into vozila values (1, 'BMW', 1)
insert into vozila values (2, 'Honda', 1)
insert into vozila values (3, 'KTM', 1)
insert into vozila values (4, 'Honda', 1)
insert into vozila values (5, 'Jamaha', 2)
insert into vozila values (6, 'Jamaha', 2)
insert into vozila values (7, 'KTM', 2)
insert into vozila values (8, 'Honda', 2)
insert into vozila values (9, 'Honda', 2)
insert into vozila values (9, 'Honda', 2)

create table vozaci
(
	id_vozaca int,
	ime varchar(20),
	id_vozila int,
	constraint pk_vozaci primary key (id_vozaca),
	constraint fk_vozaci foreign key (id_vozila) references vozila(id_vozila)
)

go

insert into vozaci values (1, 'Alan Kontre', 1)
insert into vozaci values (2, 'Alfan Pikar', 2)
insert into vozaci values (3, 'Sleser Mane', 3)
insert into vozaci values (4, 'Mark Koma', 4)
insert into vozaci values (5, 'Latrik Perin', 5)
insert into vozaci values (6, 'AVatenen Ziro', 6)
insert into vozaci values (7, 'Moro Moro', 7)
insert into vozaci values (8, 'Kotulinski Lufelman', 8)
insert into vozaci values (9, 'Marko Markovic', 9)
insert into vozaci values (10, 'Marko Markovic', 9)


create table etape 
(
	id_etape int,
	redni_broj_staze int,
	duzina_staze float,
	constraint pk_etape primary key (id_etape, redni_broj_staze)
)


go

insert into etape values (1, 1, 150)
insert into etape values (1, 2, 700)
insert into etape values (1, 3, 550)
insert into etape values (2, 1, 300)
insert into etape values (2, 2, 289)
insert into etape values (2, 3, 550)


create table prolazna_vremena
(
	id_vozaca int,
	id_etape int,
	redni_broj_staze int,
	vreme_starta datetime,
	vreme_prolaska_kroz_cilj datetime null,
	constraint pk_prolazna_vremena primary key (id_vozaca, id_etape, redni_broj_staze),
	constraint fk_prolazna_vremena_vozac foreign key (id_vozaca) references vozaci(id_vozaca),
	constraint fk_prolazna_vremena_staze foreign key (id_etape, redni_broj_staze) references etape(id_etape, redni_broj_staze)
)

go


-- Alan Kontre
insert into prolazna_vremena values (1, 1, 1, '2017-12-14 12:00:00.000', '2017-12-14 17:00:00.000') -- 490 - 5h - 2.
insert into prolazna_vremena values (1, 1, 2, '2017-12-15 12:00:00.000', '2017-12-15 20:00:00.000') -- 700 - 8h - 2.
insert into prolazna_vremena values (1, 1, 3, '2017-12-16 12:00:00.000', NULL) -- 550
insert into prolazna_vremena values (1, 2, 1, '2017-12-17 12:00:00.000', '2017-12-17 16:00:00.000') -- 300 - 4h - 2.
insert into prolazna_vremena values (1, 2, 2, '2017-12-18 12:00:00.000', NULL) -- 289
insert into prolazna_vremena values (1, 2, 3, '2017-12-19 12:00:00.000', '2017-12-19 18:30:00.000') -- 550 - 6.5h - 2.


-- Alfan Pikar - Apsolutni pobednik
insert into prolazna_vremena values (2, 1, 1, '2017-12-14 12:00:00.000', '2017-12-14 12:30:00.000') -- 0.5h - 1.
insert into prolazna_vremena values (2, 1, 2, '2017-12-15 12:00:00.000', '2017-12-15 19:00:00.000') -- 7h - 1.
insert into prolazna_vremena values (2, 1, 3, '2017-12-16 12:00:00.000', '2017-12-16 17:30:00.000') -- 5.5h - 1.
insert into prolazna_vremena values (2, 2, 1, '2017-12-17 12:00:00.000', '2017-12-17 15:00:00.000') -- 3h - 1.
insert into prolazna_vremena values (2, 2, 2, '2017-12-18 12:00:00.000', '2017-12-18 15:00:00.000') -- 3h - 1.
insert into prolazna_vremena values (2, 2, 3, '2017-12-19 12:00:00.000', '2017-12-19 17:30:00.000') -- 5.5h - 1.


-- Sleser Mane
insert into prolazna_vremena values (3, 1, 1, '2017-12-14 12:00:00.000', '2017-12-14 18:00:00.000') -- 6h - 3.
insert into prolazna_vremena values (3, 1, 2, '2017-12-15 12:00:00.000', '2017-12-15 20:30:00.000') -- 8.5h - 3.
insert into prolazna_vremena values (3, 1, 3, '2017-12-16 12:00:00.000', '2017-12-16 18:30:00.000') -- 6.5 - 2.
insert into prolazna_vremena values (3, 2, 1, '2017-12-17 12:00:00.000', '2017-12-17 16:30:00.000') -- 4.5h - 3.
insert into prolazna_vremena values (3, 2, 2, '2017-12-18 12:00:00.000', '2017-12-18 16:30:00.000') -- 4.5h - 2.
insert into prolazna_vremena values (3, 2, 3, '2017-12-19 12:00:00.000', '2017-12-19 19:00:00.000') -- 7h - 3.


-- Mark Koma
insert into prolazna_vremena values (4, 1, 1, '2017-12-14 12:00:00.000', '2017-12-14 19:00:00.000') -- 7h - 4.
insert into prolazna_vremena values (4, 1, 2, '2017-12-15 12:00:00.000', '2017-12-15 21:30:00.000') -- 9.5h - 4.
insert into prolazna_vremena values (4, 1, 3, '2017-12-16 12:00:00.000', '2017-12-16 19:30:00.000') -- 7.5 - 3.
insert into prolazna_vremena values (4, 2, 1, '2017-12-17 12:00:00.000', '2017-12-17 17:30:00.000') -- 5.5h - 4.
insert into prolazna_vremena values (4, 2, 2, '2017-12-18 12:00:00.000', '2017-12-18 17:30:00.000') -- 5.5h - 3.
insert into prolazna_vremena values (4, 2, 3, '2017-12-19 12:00:00.000', '2017-12-19 20:00:00.000') -- 8h - 4.

																		  
-- Latrik Perin	 - Apsolutni pobednik i bez pada u plasmanu													  
insert into prolazna_vremena values (5, 1, 1, '2017-12-14 12:00:00.000', '2017-12-14 19:30:00.000') -- 7.5h  - 1.
insert into prolazna_vremena values (5, 1, 2, '2017-12-15 12:00:00.000', '2017-12-15 22:00:00.000') -- 10h  - 1.
insert into prolazna_vremena values (5, 1, 3, '2017-12-16 12:00:00.000', '2017-12-16 20:00:00.000') -- 8  - 1.
insert into prolazna_vremena values (5, 2, 1, '2017-12-17 12:00:00.000', '2017-12-17 18:00:00.000') -- 6h  - 1.
insert into prolazna_vremena values (5, 2, 2, '2017-12-18 12:00:00.000', '2017-12-18 18:00:00.000') -- 6h  - 1.
insert into prolazna_vremena values (5, 2, 3, '2017-12-19 12:00:00.000', '2017-12-19 20:30:00.000') -- 8.5h  - 1.

																		  
-- AVatenen Ziro														  
insert into prolazna_vremena values (6, 1, 1, '2017-12-14 12:00:00.000', '2017-12-14 20:00:00.000') -- 8h  - 2.
insert into prolazna_vremena values (6, 1, 2, '2017-12-15 12:00:00.000', '2017-12-15 23:00:00.000') -- 11h - 3.
insert into prolazna_vremena values (6, 1, 3, '2017-12-16 12:00:00.000', '2017-12-16 20:30:00.000') -- 8.5  - 2.
insert into prolazna_vremena values (6, 2, 1, '2017-12-17 12:00:00.000', '2017-12-17 18:30:00.000') -- 6.5h  - 2.
insert into prolazna_vremena values (6, 2, 2, '2017-12-18 12:00:00.000', '2017-12-18 18:30:00.000') -- 6.5h  - 2.
insert into prolazna_vremena values (6, 2, 3, '2017-12-19 12:00:00.000', '2017-12-19 21:30:00.000') -- 9h  - 2.

																		  
-- Moro Moro															  
insert into prolazna_vremena values (7, 1, 1, '2017-12-14 12:00:00.000', '2017-12-14 20:30:00.000') -- 8.5h - 3.
insert into prolazna_vremena values (7, 1, 2, '2017-12-15 12:00:00.000', '2017-12-15 22:30:00.000') -- 10.5h - 2.
insert into prolazna_vremena values (7, 1, 3, '2017-12-16 12:00:00.000', '2017-12-16 21:00:00.000') -- 9  - 3.
insert into prolazna_vremena values (7, 2, 1, '2017-12-17 12:00:00.000', '2017-12-17 19:00:00.000') -- 7h - 3.
insert into prolazna_vremena values (7, 2, 2, '2017-12-18 12:00:00.000', '2017-12-18 19:00:00.000') -- 7h - 3.
insert into prolazna_vremena values (7, 2, 3, '2017-12-19 12:00:00.000', '2017-12-19 22:30:00.000') -- 10.5h - 4.

																		  
-- Kotulinski Lufelman - bez pada u plasmanu												  
insert into prolazna_vremena values (8, 1, 1, '2017-12-14 12:00:00.000', '2017-12-14 21:00:00.000') -- 9h  - 4.
insert into prolazna_vremena values (8, 1, 2, '2017-12-15 12:00:00.000', '2017-12-15 23:30:00.000') -- 11.5h - 4.
insert into prolazna_vremena values (8, 1, 3, '2017-12-16 12:00:00.000', '2017-12-16 21:30:00.000') -- 9.5 - 4.
insert into prolazna_vremena values (8, 2, 1, '2017-12-17 12:00:00.000', '2017-12-17 19:30:00.000') -- 7.5h - 4.
insert into prolazna_vremena values (8, 2, 2, '2017-12-18 12:00:00.000', '2017-12-18 19:30:00.000') -- 7.5h - 4.
insert into prolazna_vremena values (8, 2, 3, '2017-12-19 12:00:00.000', '2017-12-19 22:00:00.000') -- 10h - 3.