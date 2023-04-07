use isporuke_indeksi
go

create procedure sp_klijenti_potroseno
as
begin
	select kl.ime, sum(cena)
	from klijenti kl join porudzbine por
	on kl.id = por.idKlijenta
	join proizvodi pro
	on por.idProizvoda = pro.id
	group by kl.id, kl.ime 
	order by sum(cena) desc
end
go

exec sp_klijenti_potroseno
go

create procedure sp_top_ten_proizvodi
as
begin
	select top 10 pro.naziv, count(*)
	from porudzbine por join proizvodi pro
	on por.idProizvoda = pro.id
	group by pro.id, pro.naziv
	order by count(*) desc
end
go

exec sp_top_ten_proizvodi
go


create procedure sp_stanje_porudzbina
as
begin
	select kl.ime, kl.adresa, pro.naziv,
	case  
		when por.idKamiona is null then 'naruceno'
		else 'utovareno'
	end as status
	from porudzbine por
	join klijenti kl on por.idKlijenta=kl.id
	join proizvodi pro on por.idProizvoda=pro.id
	where por.datumIsporuke is null
end
go

exec sp_stanje_porudzbina
go


create procedure sp_odaberi_kamion
(
	@zapreminaProizvoda decimal(10,2)
)
as
begin
	select  top 1  id
	from kamioni
	where status='utovar' and slobodno>=@zapreminaProizvoda
	order by slobodno
end
go

exec sp_odaberi_kamion 30
go


create procedure sp_nova_porudzbina
(
	@idKlijenta int, @idProizvoda int
)
as
begin
insert into porudzbine(idKlijenta, idProizvoda)
values(@idKlijenta, @idProizvoda)
end
go

exec sp_nova_porudzbina 30, 400
go


create procedure sp_broj_klijenata
as
begin
	select count(*) from klijenti
end
go

exec sp_broj_klijenata



