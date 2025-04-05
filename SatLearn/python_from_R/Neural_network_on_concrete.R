# polynomial regression

a<-read.csv(file.choose())
View(a)

model<- lm(Salary~Level,data=a)

ans<-predict(model,data.frame(Level=a$Level))
ans

predict(model,data.frame(Level=1))

m1<-lm(Salary~poly(Level,2),data=a)
predict(m1,data.frame(Level=1))
ans1<-predict(m1,data.frame(Level=a$Level))
ans1


m2<-lm(Salary~poly(Level,3),data=a)
ans2<-predict(m2,data.frame(Level=a$Level))
ans2


#polynomial regression
a[2:3]
a$Level2=a$Level^2
a$Level3=a$Level^3
a$Level4=a$Level^4
View(a)

poly_reg= lm(formula = Salary~ ., data = a)
summary(poly_reg)


library(ggplot2)# FOR higher resolutions

ggplot() +
  geom_point(aes(x = a$Level, y = a$Salary),
             colour = 'red') +
  geom_line(aes(x = a$Level, y = predict(poly_reg, newdata = a)),
            colour = 'blue') +
  ggtitle('Truth or Bluff (Decision Tree Regression)') +
  xlab('Level') +
  ylab('Salary')

# neural network

data<-read.csv(file.choose())
View(data)
str(data)
hist(data$strength)
hist(data$age)
normalize <- function(x) { return((x - min(x))/ (max(x)-min(x)))}
data_norm<-as.data.frame(lapply(data, normalize))
data_norm
View(data_norm)
summary(data_norm$strength)
summary(data$strength)
data_train <- data_norm[1:773, ]
data_test <- data_norm[774:1030, ]

install.packages("neuralnet")
library(neuralnet)
data_model1<-neuralnet(strength~ ., data=data_train)
data_model2<-neuralnet(strength~ ., data=data_train, hidden =3)
data_model3<-neuralnet(strength~ ., data=data_train, hidden =c(3,2))
plot(data_model1)
plot(data_model2)
plot(data_model3)
data_model <- neuralet(strength ~ cement + slag)

