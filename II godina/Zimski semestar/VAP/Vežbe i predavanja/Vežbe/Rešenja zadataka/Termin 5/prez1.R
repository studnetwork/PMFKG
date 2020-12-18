# -- Zadatak 1 --

# Data je lista vremena putovanja do posla:
#     17 16 20 24 22 15 21 15 17 22
# Odrediti:
#   - najduže i najkraće vreme putovanja
#   - prosečno vreme putovanja
# Ispraviti podatak o putovanju od 24 minuta, i to tako da pokazuje 18 minuta
# Koliko puta je vreme putovanja bilo duže od 20 minuta


v = c(17, 16, 20, 24, 22, 15, 17, 22)
v[v == 24] = 18

vMin = min(v)
vMax = max(v)
vAvg = sum(v)/length(v)
vCnt20 = sum(v > 20)

paste("min:", vMin)
paste("max:", vMax)
paste("avg:", vAvg)
paste("> 20:", vCnt20)
