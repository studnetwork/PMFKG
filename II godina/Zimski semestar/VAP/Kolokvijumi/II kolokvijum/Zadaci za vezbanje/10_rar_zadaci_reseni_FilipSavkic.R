# Zadaci za vezbanje; materijal sa vezbi

#ZADATAK 1
kolicina=c(0.1, 0.6, 33.8, 1.9, 9.6, 4.3, 33.7, 0.3, 0.0, 0.1)
srednja_vred=median(kolicina)
stand_devijacija=sd(kolicina)
dan_kise=which(kolicina==max(kolicina))
visa_od_dvadeset=which(kolicina>0.2)
najmanje_cetiri=which(kolicina>=0.04)
mean(kolicina[najmanje_cetiri])
#ZADATAK 2
data=read.csv(file="C:/Users/Filip/Desktop/II godina peredmeti/VAP1/Kolokvijum 2 vezbanje/cereal.csv")
data$totalcarb<-data$Carbs+data$Sugars
paste(data$Carbs," + ",data$Sugars," + ",data$totalcarb)
length(which(data$Display.Shelf==1))
length(unique(data$Manufacturer))
podskup1=data[which(str_detect(data$Manufacturer,"Kelloggs")==T),]
podskup1
podskup2=data[which(data$Sugars>=3),c('Cereal.Name','Calories','Vitamins.and.Minerals')]
podskup2
#ZADATAK 3
data=lynx#Predstavlja broj ulovljenih riseva godisnje od 1821-1934 godine u Kanadi
length(data)
v=data[which(data<500)]
boxplot(v,horizontal = T)
summary(v)
hist(data,breaks = 7,col=c("red","blue"),main = "Godisnje uhvaceni risevi",xlab="Kolicina riseva")
#ZADATAK 4
cor(iris$Sepal.Length,iris$Sepal.Width)
cor(rank(iris$Sepal.Length),rank(iris$Sepal.Width))
plot(iris$Sepal.Length,iris$Sepal.Width)
#Regresiona veza je slaba!!!
