# -- Zadatak 1 --

# Na jednom grafiku nacrtati sledeće funkcije:
# f1: 3x / x^2+1
# f2: x / x^2+1 - 7

# - f1 obojiti plavom, a f2 crvenom bojom, za naslov x ose staviti „x vrednosti“, 
#   za naslov y ose staviti „y vrednosti“. Obe funkcije iscrtati sa po 50 tačaka, 
#   a grafike predstaviti na intervalu od -100 do 100 po x osi

f1 = function(x)
{
  return(3*x / (x^2+1))
}

f2 = function(x)
{
  return(x / (x^2+1) - 0.7)
}

curve(f1, col = "blue", n = 50, xlim = c(-100, 100), ann = FALSE)
curve(f2, col = "red", n = 50, xlim = c(-100, 100), add = TRUE)
title(xlab = "x vrednosti", ylab = "y vrednosti")



# -- Zadatak 2 --

# - U listi cena_proizvodnjedat je pregled cene proizvodnje nekog proizvoda u 
#   periodu od 10 godina, dok je u listi procenat_poreza dato kretanje poreske 
#   stope za taj vremenski period. Na grafiku je potrebno predstaviti poredjenje
#   cena proizvodnje i cena proizvoda sa porezom u datom vremenskom periodu

# cena_proizvodnje = {100, 110, 115, 110, 105, 100, 100, 95, 95, 90}
# procenat_poreza = {8, 8, 8.5, 8.7, 11, 12, 12.5, 14, 14.5, 16}

#definisanje vektora sa potrebnim vrednostima
cena_proizvodnje = c(100, 110, 115, 110, 105, 100, 100, 95, 95, 90)
procenat_poreza = c(8, 8, 8.5, 8.7, 11, 12, 12.5, 14, 14.5, 16)
cena_sa_porezom = cena_proizvodnje * (1+procenat_poreza/100)

#ekstremne vrednosti za grafik (x i y)
y_up_limit = max(cena_sa_porezom)
y_down_limit = 80
x_up_limit = length(cena_proizvodnje)
x_down_limit = 1

#crtanje grafika
plot(c(), xlim = c(x_down_limit, x_up_limit), ylim = c(y_down_limit, y_up_limit), ann = FALSE)
lines(cena_proizvodnje, col = "blue")
lines(cena_sa_porezom, col = "red")

#naslovi i legenda
title(main = "Zadatak 2", xlab = "redni broj godine", ylab = "cena proizvoda")
legend("bottomleft", legend = c("bez PDV-a", "sa PDV-om"), col = c("blue", "red"), lty = 1)



