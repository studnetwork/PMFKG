
create database vozila

go

use vozila

create table tip_vozila 
(
	idTipaVozila int primary key identity(1, 1),
	naziv varchar(20) not null
)

insert into tip_vozila values ('Putnicko vozilo')
insert into tip_vozila values ('Motocikl')
insert into tip_vozila values ('Transportno vozilo')

create table marka_vozila 
(
	idMarkeVozila int primary key identity(1, 1),
	naziv varchar(20) not null
)

insert into marka_vozila values ('Audi')
insert into marka_vozila values ('BMW')
insert into marka_vozila values ('Nissan')
insert into marka_vozila values ('Volkswagen')
insert into marka_vozila values ('Suzuki')
insert into marka_vozila values ('Volvo')

create table modeli_vozila 
(
	idModela int primary key identity(1, 1),
	idTipaVozila int foreign key references tip_vozila(idTipaVozila),
	idMarkeVozila int foreign key references marka_vozila(idMarkeVozila),
	nazivModela varchar(20) not null
)

insert into modeli_vozila values (1, 1, 'A4')
insert into modeli_vozila values (1, 2, 'X3')
insert into modeli_vozila values (1, 3, 'Qashqai')
insert into modeli_vozila values (1, 4, 'Golf 7')
insert into modeli_vozila values (1, 5, 'Swift')
insert into modeli_vozila values (1, 6, 'V90')

insert into modeli_vozila values (2, 2, 'C 600')
insert into modeli_vozila values (2, 5, 'GSX R')

insert into modeli_vozila values (3, 6, 'FE 280')
insert into modeli_vozila values (3, 6, 'FH 480')
insert into modeli_vozila values (3, 6, 'FM9')


create table osobe
(
	idOsobe int primary key identity(1, 1),
	ime varchar(20) not null
)

insert into osobe values ('Marko')
insert into osobe values ('Andreja')
insert into osobe values ('Gavra')
insert into osobe values ('Milan')
insert into osobe values ('Ana')
insert into osobe values ('Milica')
insert into osobe values ('Marijana')
insert into osobe values ('Mileva')


create table vozila  
(
	idVozila int primary key identity(1, 1),
	idModela int foreign key references modeli_vozila(idModela),
	kubikaza int not null,
	snaga int not null,
	tipGoriva varchar(20) not null,
	godinaProizvodnje int not null,
	idVlasnika int foreign key references osobe(idOsobe)
)

insert into vozila values (1,1200, 100, 'dizel', 2012, 1)
insert into vozila values (1,1400, 110, 'benzin', 2014, 2)
insert into vozila values (1,1600, 120, 'dizel', 2012, 3)
									    
insert into vozila values (2,1000, 110, 'benzin', 2015, 1)
insert into vozila values (2,1200, 100, 'dizel', 2012, 2)
insert into vozila values (2,1100, 120, 'benzin', 2015, 1)
insert into vozila values (2,1300, 100, 'dizel', 2012, 3)
									    
insert into vozila values (3,1200, 100, 'benzin', 2013, 1)
insert into vozila values (3,1400, 130, 'dizel', 2011, 2)
insert into vozila values (3,1300, 100, 'benzin', 2014, 1)
insert into vozila values (3,1500, 110, 'dizel', 2013, 3)
									    
insert into vozila values (4,1300, 100, 'benzin', 2014, 1)
insert into vozila values (4,1200, 140, 'dizel', 2013, 3)
insert into vozila values (4,1500, 100, 'benzin', 2012, 1)
insert into vozila values (4,1600, 120, 'benzin', 2011, 2)
									    
insert into vozila values (5,1900, 110, 'dizel', 2011, 3)
insert into vozila values (5,2000, 100, 'benzin', 2009, 1)
insert into vozila values (5,1400, 140, 'dizel', 2013, 2)
insert into vozila values (5,1300, 100, 'benzin', 2012, 1)
									    
insert into vozila values (6,1500, 120, 'dizel', 2011, 2)
insert into vozila values (6,1400, 100, 'benzin', 2015, 1)
insert into vozila values (6,1300, 110, 'benzin', 2012, 3)
									    
insert into vozila values (7,1300, 100, 'dizel', 2015, 3)
insert into vozila values (7,1200, 120, 'benzin', 2012, 1)
insert into vozila values (7,1400, 100, 'dizel', 2011, 2)
insert into vozila values (7,1600, 130, 'benzin', 2014, 1)
insert into vozila values (7,1900, 100, 'dizel', 2009, 3)
									    
insert into vozila values (8,1500, 100, 'dizel', 2012, 2)
insert into vozila values (8,1600, 110, 'benzin', 2014, 1)
insert into vozila values (8,1400, 100, 'dizel', 2012, 3)
insert into vozila values (8,1200, 120, 'benzin', 2015, 1)
insert into vozila values (8,1300, 100, 'dizel', 2012, 3)
insert into vozila values (8,1400, 110, 'benzin', 2011, 1)
									    
insert into vozila values (9,1400, 100, 'benzin', 2009, 2)
insert into vozila values (9,1600, 110, 'dizel', 2012, 1)
insert into vozila values (9,1900, 100, 'benzin', 2013, 3)

insert into vozila values (10,1500, 110, 'benzin', 2013, 1)
insert into vozila values (10,1200, 100, 'dizel', 2015, 2)
insert into vozila values (10,1300, 120, 'benzin', 2015, 3)
insert into vozila values (10,1300, 120, 'benzin', 2000, 3)
							 			 
insert into vozila values (11,1800, 100, 'benzin', 2014, 1)
insert into vozila values (11,2100, 110, 'dizel', 2013, 2)
insert into vozila values (11,1500, 100, 'benzin', 2012, 1)
insert into vozila values (11,1600, 120, 'dizel', 2014, 3)
insert into vozila values (11,1600, 120, 'dizel', 2001, 3)


create table oglasi  
(
	idOglasa int primary key identity(1, 1),
	idVozila int foreign key references vozila(idVozila),
	datumPostavljanja date not null,
	datumZavrsetka date not null,
	pocetnaCena int not null
)

insert into oglasi values(1, '2019-12-09', '2020-01-09', 2500)
insert into oglasi values(2, '2019-01-09', '2020-02-09', 2500)
insert into oglasi values(3, '2019-02-09', '2020-03-09', 3500)
insert into oglasi values(4, '2019-03-09', '2020-04-09', 1500)
insert into oglasi values(5, '2019-01-09', '2020-02-09', 2560)
insert into oglasi values(6, '2019-11-09', '2020-12-09', 2890)
insert into oglasi values(7, '2019-07-09', '2020-08-09', 11500)
insert into oglasi values(8, '2019-06-09', '2020-07-09', 2300)
insert into oglasi values(9, '2019-01-09', '2020-02-09', 5300)
insert into oglasi values(10, '2019-04-09', '2020-05-09', 5300)
insert into oglasi values(11, '2019-07-09', '2020-08-09', 1000)
insert into oglasi values(12, '2019-11-09', '2020-12-09', 2400)
insert into oglasi values(13, '2019-11-09', '2020-12-09', 2400)
insert into oglasi values(14, '2019-01-09', '2020-02-09', 2400)
insert into oglasi values(15, '2019-03-09', '2020-04-09', 1800)


create table ponude  
(
	idPonude int primary key identity(1, 1),
	idOglasa int foreign key references oglasi(idOglasa),
	datumPonude date not null,
	ponudjenaCena int not null,
	idPonudjaca int foreign key references osobe(idOsobe)
)


insert into ponude values(1, '2019-12-09', 2300, 4)
insert into ponude values(1, '2019-12-10', 2400, 6)
insert into ponude values(1, '2019-12-11', 2500, 8)

insert into ponude values(2, '2019-01-09', 1800, 8)
insert into ponude values(2, '2019-01-09', 2400, 7)

insert into ponude values(3, '2019-02-09', 2799, 5)
insert into ponude values(3, '2019-02-10', 3000, 5)

insert into ponude values(4, '2019-03-09', 1500, 6)

insert into ponude values(5, '2019-01-09', 2540, 4)
insert into ponude values(5, '2019-01-09', 2550, 5)
insert into ponude values(5, '2019-01-15', 2560, 6)

insert into ponude values(6, '2019-11-09', 2890, 8)

insert into ponude values(7, '2019-07-09', 11100, 8)

insert into ponude values(8, '2019-06-09', 2300, 4)
insert into ponude values(8, '2019-06-09', 2300, 5)
insert into ponude values(8, '2019-06-12', 2400, 4)
insert into ponude values(8, '2019-06-13', 2400, 5)

insert into ponude values(9, '2019-01-09', 5200, 7)
insert into ponude values(9, '2019-01-11', 5200, 8)

insert into ponude values(10, '2019-04-09', 5000, 4)

insert into ponude values(11, '2019-07-09', 700, 4)
insert into ponude values(11, '2019-07-09', 800, 5)
insert into ponude values(11, '2019-07-09', 800, 6)

insert into ponude values(12, '2019-11-09', 2300, 7)

insert into ponude values(13, '2019-11-09', 2400, 8)

insert into ponude values(14, '2019-01-09', 2100, 8)
insert into ponude values(14, '2019-01-10', 2300, 8)

insert into ponude values(15, '2019-03-09', 1600, 4)
insert into ponude values(15, '2019-03-09', 1700, 5)
insert into ponude values(15, '2019-03-10', 1700, 6)


update ponude set datumPonude = '2019-01-09' where idPonude = 29
update ponude set datumPonude = '2019-01-08' where idPonude = 22
update ponude set datumPonude = '2019-01-10' where idPonude = 5
update ponude set datumPonude = '2019-01-11' where idPonude = 18
update ponude set datumPonude = '2019-01-09' where idPonude = 24


select * from tip_vozila
select * from marka_vozila
select * from modeli_vozila
select * from osobe
select * from vozila
select * from oglasi
select * from ponude

