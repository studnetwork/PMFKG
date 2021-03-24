#####################
# Zadatak 1
############


kol_padavina = c(0.1, 0.6, 33.8, 1.9, 9.6, 4.3, 33.7, 0.3, 0.0, 0.1 )


srednja = mean( kol_padavina )


stan_devijacija = sd( kol_padavina )


naj_padavina = kol_padavina[ which( kol_padavina == max(kol_padavina) ) ]


vecaOd20 = which( kol_padavina > 20.0 )


srednja_za_najmanje_4 = mean( kol_padavina[ which(kol_padavina >= 4 ) ] )




#####################
# Zadatak 2
############


data = read.csv( "cereal.csv", header = T )
totalcarb = data$Carbs + data$Sugars
data = cbind( data, totalcarb )




temp_df = data[ which( data["Display.Shelf"] == 1 ), ]
razlicitih_vrsta = length( table(temp_df$Type) )
# drugi nacin: razlicitih_vrsta = length( unique(temp_df$Type) )




ukupno_proizvodjaca = length( unique(data$Manufacturer) )




# podskup samo sa podacima o proizvodjacu "Kelloggs"
podskupMnf = c[ which( c$Manufacturer == "Kelloggs" ), ]




# podskup koji sadrzi zitarice koje sadrze najmanje 3g secera i ???

podskupZit = c[ which( c$Sugars >= 3 ), ]

df = data.frame(
                  podskupZit$Cereal.Name, 
                  podskupZit$Calories, 
                  podskupZit$Vitamins.and.Minerals
              )
# ...










#####################
# Zadatak 3
############


data = lynx


broj = length( data )

manjeOd500 = data[ which( data < 500 ) ]


boxplot( manjeOd500,
         horizontal = T
      )

mediana = median( manjeOd500 )

minimum = min( manjeOd500 )
maksimum = max( manjeOd500 )



hist( data,
      breaks = 7,
      col = rainbow(2),
      main = "Broj ulovljenih"
    )





#####################
# Zadatak 4
############


attach(iris)

jk = cor(Sepal.Length, Sepal.Width)
paste("Ne postoji korelacija, jacina korelacije: ", jk )

plot(Sepal.Length, Sepal.Width)


