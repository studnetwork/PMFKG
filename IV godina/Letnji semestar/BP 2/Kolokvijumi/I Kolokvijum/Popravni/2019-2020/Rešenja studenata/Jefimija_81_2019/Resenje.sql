
/*
	16.6818			->		7.10964
	14.6598			->		4.45978
	 2.5325			->		2.0558
	 0.401578		->		0.0032853
	 0.0100023		->		0.100023
	 0.287542		->		0.210505
=   34.5732223		-> =	13.9390333
*/

/*
*/
alter table klijenti 
add constraint pk_idKlijent 
primary key (id)

alter table proizvodi 
add constraint pk_idProizvod
primary key (id)

alter table kamioni
add constraint pk_idKamion
primary key (id)

alter table porudzbine
add constraint pk_idPoruzbine
primary key (id)

-- sa PK-ovima je smanjeno vreme na 7.70503
-- sa idx_nclu_pro_cena smanjeno vreme na 7.23614
-- sa idx_nclu_kli_ime smanjeno vreme na 7.15916
-- sa idx_clu_por_kli_pro smanjeno vreme na 7.10964
exec sp_klijenti_potroseno

create nonclustered index idx_nclu_pro_cena 
on proizvodi(cena)

create nonclustered index idx_nclu_kli_ime
on klijenti(ime)

create clustered index idx_clu_por_kli_pro
on porudzbine(idKlijenta, idProizvoda)

-- na samom pocetku : 14.6598 (bez indeksa iz prethodne proc)
-- sa dosadasnjim indeksima : 4.45978
exec sp_top_ten_proizvodi

-- na samom pocetku : 2.5325 (bez indeksa iz prethodne proc) 
-- sa dosadasnjim indeksima 2.0558
exec sp_stanje_porudzbina

-- na samom pocetku : 0.401578 (bez indeksa iz prethodne proc) 
-- sa dosadasnjim indeksima 0.411134
-- sa dodatim indeksom idx_nclu_kam_slo_sta 0.0032853
exec sp_odaberi_kamion 30

create nonclustered index idx_clu_kam_slo_sta
on kamioni(slobodno, status)

create nonclustered index idx_nclu_kam_id
on kamioni(id)
-- na samom pocetku : 0.0100023 (bez indeksa iz prethodne proc) 
-- sa dosadasnjim indeksima 0.100023
exec sp_nova_porudzbina 30, 400

-- na samom pocetku : 0.287542 (bez indeksa iz prethodne proc) 
-- sa dosadasnjim indeksima 0.210505
exec sp_broj_klijenata
