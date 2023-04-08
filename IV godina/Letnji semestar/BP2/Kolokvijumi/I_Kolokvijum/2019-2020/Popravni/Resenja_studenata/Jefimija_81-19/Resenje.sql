-------------------------------
-- 6.22981
exec sp_klijenti_potroseno

alter table klijenti 
add constraint pk_idKlijent 
primary key (id)

alter table porudzbine
add constraint pk_idPorudzbine
primary key (id)

alter table proizvodi 
add constraint pk_idProizvodi
primary key (id)

create nonclustered index idx_nclu_pro_cena 
on proizvodi(id)
include (cena)

create nonclustered index idx_klijent_id_naziv 
on klijenti(ime)
drop index klijenti.idx_klijent_id_naziv  

create nonclustered index idx_por_klijent_pro
on porudzbine(idProizvoda, idKlijenta)
-----------------------------------------------------------------------
-- 3.53
exec sp_top_ten_proizvodi
create nonclustered index idx_pro_naziv 
on proizvodi(naziv)

create nonclustered index idx_por_pro 
on porudzbine(idProizvoda)

drop index proizvodi.idx_pro_naziv
--------------------------------------------------------
exec sp_stanje_porudzbina

alter table kamioni 
add constraint pk_idKamioni
primary key (id)

create nonclustered index idx_nclu_por_kam
on porudzbine(idKamiona)

create clustered index idx_clu_por_dat
on porudzbine(datumIsporuke)

drop index porudzbine.idx_nclu_por_sta_dat
/*
	select kl.ime, kl.adresa, pro.naziv,
	case  
		when por.idKamiona is null then 'naruceno'
		else 'utovareno'
	end as status
	from porudzbine por
	join klijenti kl on por.idKlijenta=kl.id
	join proizvodi pro on por.idProizvoda=pro.id
	where por.datumIsporuke is null
*/
-- 0.0032832
alter table kamioni 
add constraint pk_kamioni_id
primary key(id)

create nonclustered index idx_kam_slo_sta
on kamioni(status, slobodno)

drop index kamioni.idx_kam_slo_sta
exec sp_odaberi_kamion 30

exec sp_nova_porudzbina 30, 400
exec sp_broj_klijenata

-- 0.210505
-- 0.133468
create nonclustered index idx_nclu_idKli
on klijenti(id)