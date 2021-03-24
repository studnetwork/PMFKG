# II kolokvijum, 24. decembar 2019.

#ZADATAK 1 -----------------------------------------------------------
#a
lista=scan(nmax=20)
q=quantile(lista)
print(which(lista>q[4]))
#b
b=which(lista<q[4])
mean(b)
var(b)
#ZADATAK 2 -----------------------------------------------------------
#a
A=matrix(data=c(1,2,3,4,7,8,9,10,11,12,9,4,6,8,3,12),ncol=4)
B=matrix(data=c(2,3,4,5,6,4,8,9,6,2,3,4,5,11,12,7),ncol=4)
C=cbind(A,B)
r=rowMeans(C)
r
#b
r=replace(C,which(C>10),100)
C
r
#c
transponovana=t(r)
transponovana
print("Sume po kolonama:")
colSums(transponovana)
#ZADATAK 3 -----------------------------------------------------------
attach(iris)
v1=iris[which(iris$Species=="setosa"),]
v2=iris[which(iris$Species=="versicolor"),]
v3=iris[which(iris$Species=="virginica"),]
plot(v1$Sepal.Length,type="l",col="blue",ylim=c(4.5,8.0),xaxt="n",ylab="",xlab="")
axis(1,at=seq(1,50,by=1),las=2)
lines(v2$Sepal.Length,type="l",lty=2,col="red")
lines(v3$Sepal.Length,type="l",lty=2,col="green")
title(main="Velicine casicnih listica po vrstama cveta",xlab="Index",ylab="Duzina casicnog lista")
legend("topright",legend=c("setosa","versicolor","virginica"),col=c("blue","red","green"),lty=1:2,cex=0.8)
detach(iris)
#ZADATAK 4 -----------------------------------------------------------
podaci=read.csv(file="C:/Users/Filip/Desktop/II godina peredmeti/VAP1/Kolokvijum 2 vezbanje/apartmani.csv")
#a
cor(podaci$udaljenost..m.,podaci$cena..eur.)
#b
plot(podaci$udaljenost..m.,podaci$cena..eur)
identify(podaci$udaljenost..m.,podaci$cena..eur,n=1)
sa_netipicnim=lm(podaci$cena..eur.~podaci$udaljenost..m.)
bez_netipicnih=lm(podaci$cena..eur.[-101]~podaci$udaljenost..m.[-101])
plot(podaci$udaljenost..m.,podaci$cena..eur)
abline(sa_netipicnim,col="blue",lty=1)
abline(bez_netipicnih,col="red",lty=2)
legend("bottomright",legend=c("sa_netipicnim","bez_netipicnih"),col=c("blue","red"),lty = c(1,2))
#c
cor(podaci$udaljenost..m.,podaci$cena..eur.)
cor(podaci$udaljenost..m.[-101],podaci$cena..eur.[-101])
beznetip = podaci[-101,]
koef = coef(bez_netipicnih)
predvidjene = koef[2] + beznetip$udaljenost..m.*koef[1]
predvidjene
