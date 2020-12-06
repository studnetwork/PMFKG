create database festivali

go

use festivali

----------------------------------------------------------------------------------------
create table tip_instrumenta 
(
	idTipa int IDENTITY(1,1) primary key,
	naziv varchar(20) not null
)

INSERT INTO [dbo].[tip_instrumenta] VALUES ('Gitara')
INSERT INTO [dbo].[tip_instrumenta] VALUES ('Bas gitara')
INSERT INTO [dbo].[tip_instrumenta] VALUES ('Bubnjevi')
INSERT INTO [dbo].[tip_instrumenta] VALUES ('Klavir')
INSERT INTO [dbo].[tip_instrumenta] VALUES ('Kontrabas')

----------------------------------------------------------------------------------------
create table muzicari 
(
	idMuzicara int IDENTITY(1,1) primary key,
	idTipaInstrumenta int foreign key references tip_instrumenta(idTipa) ON DELETE CASCADE,
	ime varchar(20) not null,
	prezime varchar(20) not null
)

INSERT INTO [dbo].[muzicari] VALUES (1, 'Milan','Mladenovic')
INSERT INTO [dbo].[muzicari] VALUES (4, 'Margita','Stefanovic')
INSERT INTO [dbo].[muzicari] VALUES (2, 'Bojan','Pecar')
INSERT INTO [dbo].[muzicari] VALUES (3, 'Srdjan','Zika Todorovic')
INSERT INTO [dbo].[muzicari] VALUES (3, 'Ivan','Firci')

INSERT INTO [dbo].[muzicari] VALUES (2, 'Vedran','Pehar')
INSERT INTO [dbo].[muzicari] VALUES (2, 'Emir','Hot')

INSERT INTO [dbo].[muzicari] VALUES (1, 'Zoran','Kostic')
INSERT INTO [dbo].[muzicari] VALUES (2, 'Nebojsa','Antonijevic')

INSERT INTO [dbo].[muzicari] VALUES (3, 'Radomir','Mihajlovic')
INSERT INTO [dbo].[muzicari] VALUES (3, 'Slobodan','Stojanovic')

INSERT INTO [dbo].[muzicari] VALUES (3, 'Marko','Selic')
INSERT INTO [dbo].[muzicari] VALUES (5, 'Nevena','Glibetic')

INSERT INTO [dbo].[muzicari] VALUES (2, 'Skaj','Vikler')
INSERT INTO [dbo].[muzicari] VALUES (1, 'Ajs','Nigrutin')
INSERT INTO [dbo].[muzicari] VALUES (2, 'Tim','Be')

----------------------------------------------------------------------------------------
create table bendovi  
(
	idBenda int IDENTITY(1,1) primary key,
	naziv varchar(20) not null
)

insert into bendovi values ('EKV')
insert into bendovi values ('Brkovi')
insert into bendovi values ('Partibrejkersi')
insert into bendovi values ('SMAK')
insert into bendovi values ('Marcelo')
insert into bendovi values ('Bad Copy')

----------------------------------------------------------------------------------------
create table sastav_benda   
(
	idMuzicara int foreign key references muzicari(idMuzicara) ON DELETE CASCADE,
	idBenda int foreign key references bendovi(idBenda) ON DELETE CASCADE,
	datum1 datetime not null,
	datum2 datetime null,
	primary key (idMuzicara, idBenda, datum1)
)

insert into sastav_benda values (1,1,'1986-01-01','1988-01-01')
insert into sastav_benda values (2,1,'1987-01-01','1989-01-01')
insert into sastav_benda values (3,1,'1991-01-01','1993-01-01')
insert into sastav_benda values (4,1,'1992-01-01','1995-01-01')
insert into sastav_benda values (5,1,'1994-01-01',NULL)
insert into sastav_benda values (6,2,'2008-01-01','2010-01-01')
insert into sastav_benda values (7,2,'2012-01-01',NULL)
insert into sastav_benda values (8,3,'2004-01-01','2008-01-01')
insert into sastav_benda values (9,3,'2002-01-01',NULL)
insert into sastav_benda values (10,4,'1983-01-01','2005-01-01')
insert into sastav_benda values (11,4,'2005-01-01',NULL)
insert into sastav_benda values (12,5,'2010-01-01','2012-01-01')
insert into sastav_benda values (13,5,'2011-01-01',NULL)
insert into sastav_benda values (14,6,'2008-01-01','2010-01-01')
insert into sastav_benda values (15,6,'2009-01-01','2011-01-01')
insert into sastav_benda values (16,6,'2012-01-01',NULL)

----------------------------------------------------------------------------------------
create table festivali  
(
	idFestivala int IDENTITY(1,1) primary key,
	naziv varchar(20) not null
)

insert into festivali values('Arsenal')
insert into festivali values('Exit')
insert into festivali values('Love fest')

----------------------------------------------------------------------------------------
create table lineup_festivala 
(
	idFestivala int foreign key references festivali(idFestivala) ON DELETE CASCADE,
	godina int,
	idBenda int foreign key references bendovi(idBenda) ON DELETE CASCADE,
	dan int,
	primary key (idFestivala, godina, idBenda, dan)
)


/*
	1988
*/

-- Arsenal
-- I dan
insert into lineup_festivala values (1,1988,1,1)

--II dan
insert into lineup_festivala values (1,1988,4,2)

/*
	2004
*/

-- Arsenal
insert into lineup_festivala values (1,2004,1,1)
insert into lineup_festivala values (1,2004,2,2)
insert into lineup_festivala values (1,2004,4,3)

-- Exit
insert into lineup_festivala values (2,2004,5,1)
insert into lineup_festivala values (2,2004,6,2)

-- Love fest
insert into lineup_festivala values (3,2004,3,1)


/*
	2008
*/

insert into lineup_festivala values (2,2008,4,1)
insert into lineup_festivala values (2,2008,5,2)

insert into lineup_festivala values (3,2008,1,1)
insert into lineup_festivala values (3,2008,2,2)

----------------------------------------------------------------------------------------
create table posetioci   
(
	idPosetioca int IDENTITY(1,1) primary key,
	ime varchar(20) not null
)

insert into posetioci (ime) values ('Janene');
insert into posetioci (ime) values ('Durand');
insert into posetioci (ime) values ('Tomaso');
insert into posetioci (ime) values ('Dwain');
insert into posetioci (ime) values ('Amalita');
insert into posetioci (ime) values ('Devland');
insert into posetioci (ime) values ('Daron');
insert into posetioci (ime) values ('Lyndsey');
insert into posetioci (ime) values ('Ruddie');
insert into posetioci (ime) values ('Kelcey');
insert into posetioci (ime) values ('Bill');
insert into posetioci (ime) values ('Lesya');
insert into posetioci (ime) values ('Kiri');
insert into posetioci (ime) values ('Jennine');
insert into posetioci (ime) values ('Rafaela');

----------------------------------------------------------------------------------------
create table karte 
(
	idFestivala int foreign key references festivali(idFestivala) ON DELETE CASCADE,
	godina int,
	dan int,
	idPosetioca int foreign key references posetioci(idPosetioca) ON DELETE CASCADE,
	cena float,
	primary key (idFestivala,godina, dan, idPosetioca)
)
delete from karte where 1 = 1

insert into karte values (1, 1988, 1, 7, 862)
insert into karte values (3, 2004, 1, 12, 539)
insert into karte values (2, 2008, 1, 1, 1438)
insert into karte values (2, 2008, 2, 7, 1341)
insert into karte values (1, 2004, 2, 6, 712)
insert into karte values (1, 2004, 2, 13, 712)
insert into karte values (2, 2008, 1, 6, 1438)
insert into karte values (2, 2008, 1, 7, 1438)
insert into karte values (2, 2008, 1, 13, 1438)
insert into karte values (2, 2004, 2, 10, 1610)
insert into karte values (1, 1988, 1, 6, 862)
insert into karte values (1, 2004, 1, 4, 1163)
insert into karte values (2, 2004, 2, 14, 1610)
insert into karte values (2, 2004, 1, 6, 1315)
insert into karte values (1, 2004, 2, 5, 712)
insert into karte values (3, 2008, 2, 12, 1133)
insert into karte values (1, 2004, 2, 12, 712)
insert into karte values (1, 1988, 2, 11, 533)
insert into karte values (1, 2004, 1, 10, 1163)
insert into karte values (1, 2004, 2, 11, 712)
insert into karte values (1, 1988, 2, 12, 533)
insert into karte values (2, 2008, 1, 8, 1438)
insert into karte values (1, 1988, 1, 2, 862)
insert into karte values (1, 2004, 3, 4, 1670)
insert into karte values (3, 2004, 1, 8, 539)
insert into karte values (2, 2004, 2, 13, 1610)
insert into karte values (3, 2008, 2, 14, 1133)
insert into karte values (1, 1988, 2, 1, 533)
insert into karte values (3, 2008, 2, 13, 1133)
insert into karte values (1, 1988, 2, 13, 533)
insert into karte values (1, 2004, 3, 14, 1670)
insert into karte values (3, 2004, 1, 13, 539)
insert into karte values (1, 2004, 3, 9, 1670)
insert into karte values (2, 2008, 2, 3, 1341)
insert into karte values (3, 2004, 1, 11, 539)
insert into karte values (2, 2008, 2, 2, 1341)
insert into karte values (1, 1988, 2, 4, 533)
insert into karte values (1, 1988, 1, 8, 862)
insert into karte values (2, 2008, 1, 2, 1438)
insert into karte values (1, 2004, 3, 13, 1670)
insert into karte values (1, 1988, 2, 6, 533)
insert into karte values (2, 2008, 1, 3, 1438)
insert into karte values (2, 2008, 1, 11, 1438)
insert into karte values (2, 2004, 2, 9, 1610)
insert into karte values (1, 2004, 1, 14, 1163)
insert into karte values (3, 2008, 1, 6, 1664)
insert into karte values (1, 1988, 2, 3, 533)
insert into karte values (1, 2004, 3, 3, 1670)
insert into karte values (2, 2008, 2, 11, 1341)
insert into karte values (2, 2008, 1, 14, 1438)
insert into karte values (2, 2004, 1, 13, 1315)
insert into karte values (1, 2004, 1, 3, 1163)
insert into karte values (3, 2008, 1, 3, 1664)
insert into karte values (1, 2004, 3, 10, 1670)
insert into karte values (2, 2004, 1, 2, 1315)
insert into karte values (2, 2008, 1, 4, 1438)
insert into karte values (1, 2004, 2, 4, 712)
insert into karte values (3, 2008, 2, 10, 1133)
insert into karte values (3, 2004, 1, 14, 539)
insert into karte values (1, 2004, 2, 3, 712)
insert into karte values (3, 2008, 2, 6, 1133)
insert into karte values (2, 2004, 1, 3, 1315)
insert into karte values (2, 2004, 2, 2, 1610)
insert into karte values (2, 2004, 1, 11, 1315)
insert into karte values (2, 2008, 1, 10, 1438)
insert into karte values (1, 1988, 1, 10, 862)
insert into karte values (1, 1988, 1, 13, 862)
insert into karte values (1, 1988, 2, 9, 533)
insert into karte values (3, 2008, 2, 1, 1133)
insert into karte values (3, 2008, 2, 11, 1133)
insert into karte values (1, 1988, 2, 5, 533)
insert into karte values (3, 2004, 1, 6, 539)
insert into karte values (2, 2004, 1, 8, 5031)
