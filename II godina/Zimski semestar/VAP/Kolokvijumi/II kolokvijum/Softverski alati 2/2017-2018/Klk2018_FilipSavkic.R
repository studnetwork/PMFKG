#ZADATAK 1 -----------------------------------------------------------
lista=scan(nmax=10)
b=which(lista<mean(lista))
lista[which(lista==max(lista))]=mean(min(lista),max(lista))
#ZADATAK 2 -----------------------------------------------------------
a=matrix(data=c(-1,5,3,0,2,4,5,-3,-8),nrow=3,byrow=TRUE)                          
b=matrix(data=c(2,-3,4,1,-5,8,9,3,1),nrow=3,byrow=TRUE)
c1=t(a%*%b)
c2=c(c1)
mean(c2)
c2[c2<0]=0
mean(c2)
#ZADATAK 3 -----------------------------------------------------------
a=scan(what=double())
b=scan(what=double())
c=scan(what=double())
curve(a*x*x+b*x+c,type="l",col="blue",xlim=c(-100,100),xlab="x osa",ylab="y osa")
curve((a^b)*x+c,add=TRUE,col="red")