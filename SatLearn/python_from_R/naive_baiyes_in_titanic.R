
data("Titanic")
abc<-as.data.frame(Titanic)
View(abc)
abc=abc[-5]
abc$Class=factor(abc$Class,levels = c("1st","2nd","3rd","Crew"),labels=c(1,2,3,4))
abc$Sex=factor(abc$Sex,levels = c("Male","Female"),labels=c(1,2))
abc$Age=factor(abc$Age,levels = c("Child","Adult"),labels=c(1,2))
abc$Survived=factor(abc$Survived,levels = c("N0","Yes"))
library(caTools)
set.seed(123)
split=sample.split(abc$Survived,SplitRatio = 0.7)
training_set=subset(abc,split==TRUE)
test_set=subset(abc,split==FALSE)
library(e1071)
nbpredict=naiveBayes(x=training_set[-4],y=training_set$Survived)
anbpredict=predict(nbpredict,newdata=test_set[-4])
anbpredict
conf_m=table(anbpredict,test_set[,4])
conf_m
accrcay=sum(diag(conf_m)) / sum(conf_m) * 100
accrcay


#library(sqldf)
#install.packages("sqldf")
#library(neuralnet)


data("Titanic")
abc=as.data.frame(Titanic)
View(abc)
str(abc)
help(abc)
summary(abc)
abc$Class = factor(abc$Class,levels=c("1st","2nd","3rd","crew"),labels=c(1,2,3,4))
abc$Sex = factor(abc$Sex, levels=c("Male","Female"),labels=c(1,2))
abc$Age = factor(abc$Age, levels=c("Child","Adult"),labels=c(1,2))
abc$Survived = factor(abc$Survived, levels=c("Yes","No"))
library(caTools)
set.seed(123)
split=sample.split(abc$Survived,SplitRatio=0.7)
training_set=subset(abc,split==TRUE)
test_set=subset(abc,split==FALSE)
library(e1071)
nbpredict=naiveBayes(x=training_set[-4],y=training_set$Survived)
anbpredict=predict(nbpredict,newdata=test_set[-4])
anbpredict
conf_m=table(anbpredict,test_set[,4])
conf_m
accuracy=sum(diag(conf_m))/sum(conf_m)*100
accuracy
