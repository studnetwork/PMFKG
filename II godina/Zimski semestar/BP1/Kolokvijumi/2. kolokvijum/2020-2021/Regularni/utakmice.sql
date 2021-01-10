go
drop database UTAKMICE
go
create database UTAKMICE
GO
USE UTAKMICE
GO

IF OBJECT_ID('dbo.golovi', 'U') IS NOT NULL
drop table golovi
IF OBJECT_ID('dbo.utakmice', 'U') IS NOT NULL
drop table utakmice
IF OBJECT_ID('dbo.sezona', 'U') IS NOT NULL
drop table sezona
IF OBJECT_ID('dbo.ugovori', 'U') IS NOT NULL
drop table ugovori
IF OBJECT_ID('dbo.timovi', 'U') IS NOT NULL
drop table timovi
IF OBJECT_ID('dbo.igraci', 'U') IS NOT NULL
drop table igraci

create table igraci
(
	id int primary key identity(1,1),
	ime varchar(20)
)

insert into igraci values ('Nemanja Matic')
insert into igraci values ('Aleksandar Mitrovic')
insert into igraci values ('Darko Lazovic')
insert into igraci values ('Zlatan Ibrahimovic')
insert into igraci values ('Luka Jovic')
insert into igraci values ('Dusan Tadic')
insert into igraci values ('Adem Ljajic')
insert into igraci values ('Filip Kostic')
insert into igraci values ('Marko Dmitrovic')
insert into igraci values ('Marko Grujic')
insert into igraci values ('Dijego A. Maradona')


create table timovi
(
	id int primary key identity(1,1),
	naziv varchar(20)
)

insert into timovi values ('Crvena zvezda')
insert into timovi values ('Radnicki KG')
insert into timovi values ('Vojvodina')
insert into timovi values ('Partizan')

create table ugovori
(
	id int primary key identity(1,1),
	id_tima int foreign key references timovi(id),
	id_igraca int foreign key references igraci(id),
	datum1 datetime,
	datum2 datetime
)

insert into ugovori values (1, 100, '2010-1-1', '2020-1-1')
insert into ugovori values (1, 2, '2016-1-1', '2019-1-1')
insert into ugovori values (1, 3, '2013-1-1', '2020-1-1')
insert into ugovori values (2, 4, '2014-1-1', '2019-1-1')
insert into ugovori values (2, 5, '2016-1-1', '2020-1-1')
insert into ugovori values (2, 6, '2011-1-1', '2019-1-1')
insert into ugovori values (3, 7, '2014-1-1', '2020-1-1')
insert into ugovori values (3, 8, '2013-1-1', '2019-1-1')
insert into ugovori values (4, 9, '2009-1-1', '2020-1-1')
insert into ugovori values (4, 11, '2016-1-1', '2019-1-1')

select * from igraci
select * from ugovori where id_igraca = 11


create table sezona
(
	id int primary key identity(1,1),
	godina int
)

insert into sezona values(2018)
insert into sezona values(2019)

create table utakmice
(
	id int primary key identity(1,1),
	id_sezone int foreign key references sezona(id),
	id_domacina int foreign key references timovi(id),
	id_gosta int foreign key references timovi(id)
)

insert into utakmice values (1, 1, 2)
insert into utakmice values (1, 1, 3)
insert into utakmice values (1, 1, 4)
insert into utakmice values (1, 2, 1)
insert into utakmice values (2, 2, 4)
insert into utakmice values (2, 3, 2)

insert into utakmice values (2, 4, 2)
insert into utakmice values (2, 3, 4)
insert into utakmice values (2, 4, 3)


create table golovi
(
	id int primary key identity(1,1),
	id_utakmice int foreign key references utakmice(id),
	id_tima int foreign key references timovi(id),
	id_igraca int foreign key references igraci(id)
)

insert into golovi values (1, 1, 1)
insert into golovi values (1, 1, 2)
insert into golovi values (1, 2, 5)
insert into golovi values (2, 1, 7)
insert into golovi values (2, 1, 7)
insert into golovi values (2, 3, 1)









