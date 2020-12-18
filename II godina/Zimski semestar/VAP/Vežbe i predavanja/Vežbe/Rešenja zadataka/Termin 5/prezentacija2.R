# -- Zadatak 1 --

# Resiti sistem jednacina
# 4x + 2y - 3y = 54
# 2x + 3y = 18
# 10x + 3y - 2z = 12

A = matrix(data = c(4, 2, -3, 2, 0, 3, 10, 3, -2), ncol = 3, byrow = TRUE)
B = c(54, 18, 12)

solve(A, B)


# -- Zadatak 2 --

# - Za proizvoljnu matricu A izračunati sume po vrstama te matrice, 
#     a zatim svaku vrstu deli odgovarajućom sumom
# - Za proizvoljnu matricu B izračunati proseke za svaku od vrsta te matrice, 
#     a zatim kao rezultat vratiti listu koja u sebi sadrži 1/prosek_vrste za svaku vrstu matrice B

A = matrix(data = c(10, 20, 30, 10, 50, 60, 70, 80, 90), ncol = 3)
sumsA = rowSums(A)
resA = A / sumsA
print(resA)

B = matrix(data = c(40, 40, 30, 40, 50, 60, 80, 80, 90), ncol = 3)
avgsB = rowMeans(B)
resB = 1 / avgsB[]
print(resB)


# -- Zadatak 3 --

# Napraviti program kojirešava sistem linearnih jednačina u zavisnosti od parametra a 
# koji korisnik unosi sa tastature

a = scan(nmax = 1)
A = rbind(c(1, a, 1), c(1, 1, a), c(1, a^2, 1)) # rbind vraca matricu (3x3)
B = c(1, 1, a)

solve(A, B)

# napomena: u resenju sa prezentacije nedostaje "byrow = TRUE" kod kreiranja matrice A
