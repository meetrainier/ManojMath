file<-read.csv(file.choose())
View(file)
summary(file$charges)
str(file)
hist(file$age)
table(file$age)
table(file$region)
cor(file[c("age","bmi","children","charges")])
pairs(file[c("age","bmi","children","charges")])

install.packages("psych")
library(psych)
pairs.panels(file[c("age","bmi","children","charges")])

filemodel <- lm(charges~age+bmi+children+sex+region+smoker,data=file)
filemodel
new_charges<-data.frame(age=24,bmi=34,children=5,sex='male',region='northeast',smoker='yes')
predict_charges<-predict(filemodel,new_charges)
predict_charges


