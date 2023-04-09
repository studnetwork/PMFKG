exec sp_klijenti_potroseno;
exec sp_top_ten_proizvodi;
exec sp_stanje_porudzbina;
exec sp_odaberi_kamion 30;
exec sp_nova_porudzbina 30, 400;
exec sp_broj_klijenata;

-- ----------------------------------------------

exec sp_helpindex klijenti;
exec sp_spaceused klijenti;

exec sp_helpindex porudzbine;
exec sp_spaceused porudzbine;

exec sp_helpindex proizvodi;
exec sp_spaceused proizvodi;

exec sp_helpindex kamioni;
exec sp_spaceused kamioni;

-- ----------------------------------------------

alter table klijenti
add constraint pk_id
primary key (id);
-- alter table klijenti drop constraint pk_id;

create clustered index idx_cl_idProizvoda
on porudzbine(idProizvoda);
-- drop index porudzbine.idx_cl_idProizvoda;

alter table proizvodi
add constraint pk_proizvodi_id 
primary key(id);
-- alter table proizvodi drop constraint pk_proizvodi_id;

create nonclustered index idx_ncl_idKlijenta
on porudzbine(idKlijenta);
-- drop index porudzbine.idx_ncl_idKlijenta;


alter table kamioni
add constraint pk_kamioni_id 
primary key(id);
-- alter table proizvodi drop constraint pk_kamioni_id;

create nonclustered index idx_ncl_status_slobodno
on kamioni(status, slobodno);
-- drop index kamioni.idx_ncl_status_slobodno;

create nonclustered index idx_ncl_id
on klijenti(id);
-- drop index klijenti.idx_ncl_id;
