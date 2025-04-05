a=read.csv(file.choose())
View(a)
a=a[-1]
a$Purchased=factor(a$Purchased,levels =c(0,1))
library(caTools)
set.seed(123)
split=sample.split(a$Purchased,SplitRatio = 0.7)
training_set=subset(a,split==TRUE)
test_set=subset(a,split==FALSE)
training_set[-3]=scale(training_set[-3])
test_set[-3]=scale(test_set[-3])
library(class)
b=knn(train=training_set[,-3],test=test_set[,-3],cl=training_set[,3],k=20)
b
conf_m=table(b,test_set[,3])
conf_m
acc=sum(diag(conf_m)) / sum(conf_m) * 100
acc

a=read.csv(file.choose())
View(a)
str(a)
help(a)
summary(a)
a=a[-1]
a$Purchased = factor(a$Purchased, levels=c(0,1))
library(caTools)
set.seed(123)
split=sample.split(a$Purchased,SplitRatio=0.7)
training_set=subset(a,split==TRUE)
test_set=subset(a,split==FALSE)
training_set[-3]=scale(training_set[-3])
test_set[-3]=scale(test_set[-3])
library(class)
b=knn(train=training_set[,-3],test=test_set[,-3],cl=training_set[,3],k=20)
b
conf_m=table(b,test_set[,3])
conf_m
accuracy=sum(diag(conf_m))/sum(conf_m)*100
accuracy

#library(rpart)
#d=rpart(formula = diagnosis~.,data=a)
#da=predict(d,newdata=test_set[-1],type='class')
#da


#library(e1071)
#nb=naiveBayes(x=training_set[-1],y=training_set$diagnosis)
#nbpredict=predict(nb,newdata=test_set[-1])
#nbpredict


#conf_m=table(nbpredict,test_set[,1])
#conf_m




reg=lm(formula=Salary~.,data=training_set)
preg=predict(reg,newdata=test_set)



#library(ggplot2)

#ggplot()+ geom_point(aes(x=training_set$Salary,y=training_set$YearsExperience,colour='red')) + geom_line(aes(x=training_set$Salary,y=predict(reg,newdata=training_set),colour='blue'))+xlab('abcs')+ylab('pqrs')


