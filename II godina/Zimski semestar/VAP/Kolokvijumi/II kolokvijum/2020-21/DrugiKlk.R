#REDOVNI KOLOKVIJUM - 2020/21.
#zadatak 1
p=31:60
A=matrix(data=p,nrow=5,ncol=6)
B=matrix(data=p,nrow=5,ncol=6,byrow=TRUE)
#a.
k=colMeans(A)
D=rbind(A,matrix(data=k,nrow=1,byrow=T))
#b.
d=matrix(data=colSums(B),ncol=1)
det(D)
  #posto je determinanta matrice D=0 ne mozemo odrediti inverznu matricu i resiti sistem

#zadatak 2
summary(ChickWeight)

b=boxplot(ChickWeight$weight~ChickWeight$Diet,xlab="Ishrana",ylab="Tezina",main="Prikaz tezine pilica na osnovu vrste ishrane")
  #sa grafika mozemo zakljuciti da grupa 1 ima 4 a grupa 2 ima 2 netipicne vrednosti, dok ostale dve nemaju

ma=mi=1
maIQR=miIQR=IQR(b$stats[,1])
for(i in 2:4){
  iq=IQR(b$stats[,i])
  if(maIQR<iq){
    ma=i
    maIQR=iq
  }else if(miIQR>iq){
    mi=i
    miIQR=iq
  }
}
mi
ma
#sa grafika se moze videti da najveci IQR ima 3 a najmanji 1 grupa
#rezlutat izvrsavanja skripte potvrdjuje zakljucak

#zadatak 3
summary(airquality)
novaBaza=subset(airquality[airquality$Month==9,],select=c(-5))

mean(novaBaza[novaBaza$Day>=1 & novaBaza$Day<=15,]$Wind)

temp=cut(novaBaza$Temp,breaks = c(min(novaBaza$Temp),quantile(novaBaza$Temp,0.25)-0.1^2,quantile(novaBaza$Temp,0.75),max(novaBaza$Temp)))
levels(temp)=c("Prva","Druga","Treca")
tabele=table(temp)
tabele[1]=tabele[1]-1
tabele[2]=tabele[2]+1
barplot(table(temp),col=c("red","green","blue"),beside=T,legend.text = c("Prva","Druga","Treca"))

#zadatak 4
#a)
pritisak=read.csv(file="C:/Users/User/Desktop/R Scripts/Vezbe/Pritisak.csv",header=T,sep=",")
cor(pritisak$dijastolni_pritisak,pritisak$sistolni_pritisak)#smer je pozitivan tj. k>0
plot(pritisak$dijastolni_pritisak,pritisak$sistolni_pritisak)
model=lm(pritisak$sistolni_pritisak~pritisak$dijastolni_pritisak)
abline(model)
title(main="Veza izmedju dijastolnog i sistolnog pritiska")
koeficijenti=unname(coef(model))
#b)
80*koeficijenti[2]+koeficijenti[1]
#c)
cor(pritisak$starost,pritisak$sistolni_pritisak)#ovo je donekle ok
plot(pritisak$starost,pritisak$sistolni_pritisak)
cor(pritisak$starost,pritisak$dijastolni_pritisak)#ovo je donekle ok
plot(pritisak$starost,pritisak$dijastolni_pritisak)
cor(pritisak$starost,pritisak$puls)#za ove promenljive nema smisla kreirati linearni model jer je koeficijent korelacije veoma mali
plot(pritisak$puls,pritisak$starost)



#POPRAVNI KOLOKVIJUM - 2020/21.

#zadatak1
x=scan(nmax=16)
M=matrix(data=x,nrow = 4,ncol=4)
T=c(M)
ind=which(T>mean(T))
print(ind)
T2=T[ind]
T2[min(T2)==T2]=median(T2)
D=c(3,4,-5,1,2,2,2,-1,1,-1,5,-1,5,0,0,1)
D=matrix(data=D,nrow=4,byrow=T)
d=c(10,5,7,4)
d=matrix(data=d,ncol=1)
det(D)#=-21; znaci da postoji resenje sistema
solve(D)%*%d

#zadatak2
pre=c(9.1,8.0,7.7,10.0,9.6,7.9,9.0,7.1,8.3,9.6,8.2,9.2,7.3,8.5,9.5)
posle=c(8.2,6.4,6.6,8.5,8.0,5.8,7.8,7.2,6.7,9.8,7.1,7.7,6.0,6.6,8.4)
#a.
abs(median(posle)-median(pre))
var(posle)-var(pre)
#b.
razlika=posle-pre
min(razlika)
max(razlika)
quantile(razlika,0.25)
quantile(razlika,0.75)
hist(razlika)
curve(dnorm(x,mean=mean(razlika),sd=sd(razlika)),col="red",add=T)
lines(density(razlika),col="blue")
b=boxplot(razlika,horizontal = T)
razlika
b$out #outliers

#zadatak 3
plot(pre,col="red",type="o",xlab="",ylab="",xlim =c(1,15),ylim=c(5.5,10))
title(main="Terapija",xlab="Pacijent",ylab="Holesterol")
lines(posle,lty="dashed",type="o",col="green")
axis(side=1,at=1:15) #1 je x a 2 y osa
legend(locator(1),col=c("red","green"),lty=c(1,2),legend=c("Pre","Posle"),box.lty = 0,bg="transparent")

#zadatak 4
#a)
zaposleni=read.csv(file="C:/Users/User/Desktop/R Scripts/Vezbe/Employee data.csv",header=T,sep=",")
attach(zaposleni)
cor(rank(salbegin),rank(salary))
plot(salbegin,salary)
model=lm(salary~salbegin)
abline(model)
title(main="f(pocetna plata)=plata")
#b)
koef=unname(coef(model))
70000*koef[2]+koef[1]
#c)
pocetna.plata=salbegin[gender=="f"]
iskustvo=prevexp[gender=="f"]
cor(iskustvo,pocetna.plata)#nema smisla kreirati linearni model

a=paste(1:10,1:10)
b=outer(1:10,1:10,paste)
length(a)
length(b)
