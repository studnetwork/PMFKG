/*
	16.6818     -> 6.29865
	14.6598     -> 3.63554
	 2.5325		-> 2.23177
	 0.401578	-> 0.0032864
	 0.0100023	-> 0.0100023
	 0.287542	-> 0.133468
  = 34.2856803  -> 12.1022217
*/
-- 16.6818
-- sa PK klijenti i PK prizvodi = 7.70503
-- sa clust. idx na ceni = 6.37568
-- sa nclu. idx sa imenom klijenta = 6.26235
exec sp_klijenti_potroseno

alter table klijenti 
add constraint pk_klijenti_id
primary key (id)

alter table proizvodi 
add constraint pk_proizvodi_id
primary key nonclustered(id)

create clustered index idx_clu_por_pro_kli 
on porudzbine(idProizvoda, idKlijenta)

create clustered index idx_clu_pro_cena
on proizvodi(cena, id)

create nonclustered index idx_nclu_kli_ime 
on klijenti(ime)
---------------------------------------------------
-- 14.6598
-- sa dosadasnjim indeksima 3.63602
exec sp_top_ten_proizvodi

-- 2.5325
-- 2.21399
exec sp_stanje_porudzbina

-- 0.0032864
exec sp_odaberi_kamion 30

create clustered index idx_clu_kam_slo
on kamioni(slobodno)
-- 0.0100023
exec sp_nova_porudzbina 30, 400

-- 0.210505
-- sa ncli_idx klijent id = 0.133468
exec sp_broj_klijenata

create nonclustered index idx_nclu_kli_id
on klijenti(id)
