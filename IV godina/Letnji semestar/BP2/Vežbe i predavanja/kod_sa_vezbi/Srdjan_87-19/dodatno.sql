-- # pomocne procedure

exec sp_helpindex person;

exec sp_spaceused person;


-- # brisanje indeksa

alter table person drop constraint pk_businessEntityId;
drop index person.idx_ncl_businessEntityId;
drop index person.idx_ncl_first;
drop index person.idx_ncl_first_include_lastname;
drop index person.idx_ncl_first_last;
drop index person.idx_ncl_first_last_include_bizId;
drop index person.idx_cl_first_last_bizId;

-- ---------------------------------------------------------------

-- # kreiranje indeksa

-- pk_businessEntityId

alter table person
add constraint pk_businessEntityId
primary key (businessEntityId);



-- idx_ncl_businessEntityId

create nonclustered index idx_ncl_businessEntityId
on person(businessEntityId);



-- idx_ncl_first

create nonclustered index idx_ncl_first
on person(firstname);



-- idx_ncl_first_include_lastname

create nonclustered index idx_ncl_first_include_lastname
on person(firstname) include(lastname);



-- idx_ncl_first_last

create nonclustered index idx_ncl_first_last
on person(firstname, lastname);



-- idx_ncl_first_last_include_bizId

create nonclustered index idx_ncl_first_last_include_bizId
on person(firstname, lastname) include (businessEntityId);



-- idx_cl_first_last_bizId

create clustered index idx_cl_first_last_bizId
on person(firstname, lastname, businessEntityId);


-- ---------------------------------------------------------------