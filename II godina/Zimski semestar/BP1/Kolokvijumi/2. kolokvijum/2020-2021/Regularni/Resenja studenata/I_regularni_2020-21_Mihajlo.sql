﻿--Kolokvijum 2020/21
select ut.id, gl.id_tima, count(*) as broj_golova
from utakmice ut left join golovi gl on ut.id = gl.id_utakmice
group by ut.id, gl.id_tima

select id,
	   (select naziv from timovi where id = ut.id_domacina) nazivTimaDomacina,
	   (select naziv from timovi where id = ut.id_gosta) nazivTimaGosta,
	   concat( (select broj_golova from broj_golova where id = ut.id and id_tima = ut.id_domacina),
			   ':',
			   (select broj_golova from broj_golova where id = ut.id and id_tima = ut.id_gosta)) as rezultat
from utakmice ut