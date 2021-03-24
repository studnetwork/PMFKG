# -- Zadatak 3 --

# - U fajlu „stanovnistvo.csv“ dati su podaci o kretanju stanovništva u Kragujevcu
#   u prethodnih 50-ak godina. Za svaku godinu dati su podaci o broju rođenih, 
#   umrlih i ukupnom broju stanovnika.
# - Na osnovu ovih podataka nacrtati grafik na kom je prikazan odnos rođenih i 
#   umrlih u Kragujevcu, zajedno sa odgovarajućim naslovom i legendom
# - Na osnovu dostupnih podataka na zasebnom grafiku prikazati kretanje 
#   stanovništva u Kragujevcu

podaci = read.csv("stanovnistvo.csv", header = TRUE)
rodjeni = podaci$rodjeni
umrli = podaci$umrli
mn = min(c(min(rodjeni), min(umrli)))
mx = max(c(max(rodjeni), max(umrli)))

# definisanje plot-a
plot(c(), xlim = c(1,length(rodjeni)), ylim = c(mn, mx), ann = FALSE, axes = FALSE)

# izgled osa i okvir
axis(1, at = 1:length(podaci$godina), labels = podaci$godina)
axis(2)
box()

# crtanje grafika za rodjene i umrle
lines(rodjeni, col = "blue")
lines(umrli, col = "red", lty = 2)

# naslov i legenda
title("Kretanje broja rodjenih i umrlih u Kragujevcu")
legend("bottomright", legend = c("br. rodjenih", "br. umrlih"), col = c("blue", "red"), lty = c(1,2), title = "Legenda")

# kretanje stanovnistva
plot(podaci$broj_stanovnika, type = "l", col = "blue", ann = FALSE, axes = FALSE)
axis(1, at = 1:length(podaci$broj_stanovnika), labels = podaci$godina)
axis(2)
box()
title("Kretanje broja stanovnika u Kragujevcu")
legend("bottomright", legend = "br. stanovnika", col = "blue", lty = 1)



# -- Zadatak 4 --

# Napisati funkciju koja za prosleđen realan broj x i ceo broj n bez korišćenja petlje računa
# suma: 1->n :(x^i / i)

# 1. deo
funkcija1 = function(x, n)
{
  return(sum(x^(1:n) / (1:n)))
}

funkcija1(2,10)

# 2. deo
funkcija2 = function(a, d, n)
{
  return(sum(seq(from = a, by = d, length.out = n)))
}

funkcija2(2, 2, 10)


