Dati login sistemi su studentska improvizacija, isprobavanje i testiranje, nisu potkrepljeni najboljim praksama i ne pokazuju kako bi u praksi zaista trebalo da se realizuje login sistem.

Login sistem - Session pristup
Realizacija login sistema koriscenjem PHP Sesija.

Login sistem - Token pristup
Realizacija login sistema koriscenjem Cookie-ja i cuvanjem podatka o sesiji u bazi.

* Kod ova dva pristupa je skoro isti, razlikuju se jedino u Auth.php i DB.php fajlovima (za Session pristup iz DB.php fajla su izbacene nepotrebne metode, koje su potrebne postoje kod Token pristupa)
