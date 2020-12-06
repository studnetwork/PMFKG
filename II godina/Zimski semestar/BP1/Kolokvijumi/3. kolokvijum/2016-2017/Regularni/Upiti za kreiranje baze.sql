create database LICITACIJA

use LICITACIJA


create table Clanovi
(
	id int primary key not null,
	ime nvarchar(20) not null,
	datumUclanjenja datetime not null
)


create table tip_proizvoda
(
	id int primary key not null,
	naziv nvarchar(20) not null
)

create table Proizvodi
(
	id int primary key not null,
	idClana int not null,
	idTipa int not null,
	nazivProizvoda nvarchar(20) not null,
	opis nvarchar(100) null,
	pocetakLicitacije datetime not null,
	krajLicitacije datetime not null,
	constraint FK_ProizvodiClan foreign key (idClana) references Clanovi(id),
	constraint FK_ProizvodiTip foreign key (idTipa) references tip_proizvoda(id)
)


create table Ponude 
(
	id int not null primary key,
	idProizvoda int not null foreign key references Proizvodi(id),
	idClanaPonudjaca int not null foreign key references Clanovi(id),
	novcaniIznos float not null,
	datumponude datetime not null
)


create table Ocene
(
	idClana1 int not null foreign key references Clanovi(id),
	idClana2 int not null foreign key references Clanovi(id),
	ocena int not null,
	komentar nvarchar(50) not null
)



insert into Clanovi (id, ime, datumUclanjenja) values (1, 'Marko', '2015-10-1')
insert into Clanovi (id, ime, datumUclanjenja) values (2, 'Marija', '2015-10-2')
insert into Clanovi (id, ime, datumUclanjenja) values (3, 'Una', '2015-10-3')
insert into Clanovi (id, ime, datumUclanjenja) values (4, 'Lazar', '2015-10-4')



insert into tip_proizvoda (id, naziv) values (1, 'Obuca')
insert into tip_proizvoda (id, naziv) values (2, 'Tehnika')
insert into tip_proizvoda (id, naziv) values (3, 'Knjige')
insert into tip_proizvoda (id, naziv) values (4, 'Racunari i oprema')


insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (1, 1, 1, 'NIKE FLYKNIT MAX 1', 'Patike su u odlicnom stanju.', '2016-12-2', '2016-12-6')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (2, 1, 2, 'AJ fon 6 S', 'Telefon je u solidnom stanju', '2016-12-3', '2016-12-7')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (3, 1, 1, 'NIKE FLYKNIT MAX 2', NULL, '2016-12-1', '2016-12-5')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (4, 1, 2, 'DELL Monitor', 'LCD monitor 24"', '2016-12-4', '2016-12-8')


insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (5, 2, 3, 'MSSQL za 7 dana :)', '', '2016-11-10', '2016-11-16')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (6, 2, 4, 'Graficka kartica', 'Ne znam koja je, ne razumem se', '2016-11-12', '2016-11-17')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (7, 2, 4, 'CPU i5 2.8 GHz', '', '2016-11-13', '2016-11-18')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (8, 2, 4, 'RAM memorija 4GB', '', '2016-11-14', '2016-11-20')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (9, 2, 3, 'Na Drini cuprija', '', '2016-11-15', '2016-11-19')

insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (10, 1, 4, 'RAM memorija 8GB', '', '2016-12-13', '2016-12-19')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (11, 1, 1, 'NIKE FLYKNIT MAX 3', '', '2016-12-14', '2016-12-20')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (12, 2, 3, 'AJ fon 7', '', '2016-12-15', '2016-12-21')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (13, 3, 4, 'C za 21 dan', '', '2016-12-14', '2016-12-22')
insert into Proizvodi (id, idClana, idTipa, nazivProizvoda, opis, pocetakLicitacije, krajLicitacije) values (14, 4, 1, 'Mis LG', '', '2016-12-10', '2016-12-24')


insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (1, 1, 2, 2500, '2016-12-2 4:0:0')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (2, 1, 3, 2700, '2016-12-2 5:0:0')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (3, 1, 2, 2800, '2016-12-3')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (4, 1, 4, 3000, '2016-12-4')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (5, 1, 3, 3100, '2016-12-5 1:0:0')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (6, 1, 2, 3200, '2016-12-5 2:0:0') 

insert into ocene (idClana1, idClana2, ocena, komentar) values ( 1, 2, 5, 'Sve preporuke!')
insert into ocene (idClana1, idClana2, ocena, komentar) values ( 2, 3, 5, '')
insert into ocene (idClana1, idClana2, ocena, komentar) values ( 1, 3, 4, 'Solidno')
insert into ocene (idClana1, idClana2, ocena, komentar) values ( 4, 3, 5, '')
insert into ocene (idClana1, idClana2, ocena, komentar) values ( 2, 4, 5, '')
insert into ocene (idClana1, idClana2, ocena, komentar) values ( 3, 4, 5, 'Sve preporuke!')
insert into ocene (idClana1, idClana2, ocena, komentar) values ( 3, 1, 3, '')
insert into ocene (idClana1, idClana2, ocena, komentar) values ( 4, 1, 5, 'Sve preporuke!')
insert into ocene (idClana1, idClana2, ocena, komentar) values ( 4, 2, 1, 'Lose!')
insert into ocene (idClana1, idClana2, ocena, komentar) values ( 4, 2, 1, 'Lose!')



insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (7, 2, 4, 20000, '2016-12-4 4:0:0')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (8, 2, 3, 21000, '2016-12-5 5:0:0')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (9, 2, 4, 25000, '2016-12-6') 

insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (10, 3, 4, 1000, '2016-12-2 4:0:0')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (11, 3, 3, 1500, '2016-12-3 5:0:0')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (12, 3, 2, 2000, '2016-12-4')  

insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (13, 4, 4, 9000, '2016-12-5 4:0:0')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (14, 4, 3, 1500, '2016-12-6 5:0:0')
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (15, 4, 4, 2000, '2016-12-7')  


insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (16, 5, 2, 1000, '2016-12-11 4:0:0') 
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (17, 5, 3, 1500, '2016-12-14 5:0:0') 

insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (18, 6, 4, 9000, '2016-12-13 4:0:0') 
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (19, 6, 3, 10000, '2016-12-14 5:0:0')

insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (20, 7, 2, 9000, '2016-12-14 4:0:0') 
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (21, 7, 3, 15000, '2016-12-15 5:0:0')

insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (22, 8, 4, 9000, '2016-12-14 4:0:0') 
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (23, 8, 3, 20000, '2016-12-15 5:0:0')

insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (24, 9, 2, 1500, '2016-12-15 4:0:0') 
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (25, 9, 3, 2000, '2016-12-17 5:0:0') 



insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (26, 14, 3, 2000, '2016-12-11') 
insert into Ponude (id, idProizvoda, idClanaPonudjaca, novcaniIznos, datumPonude) values (27, 14, 4, 2100, '2016-12-12')



