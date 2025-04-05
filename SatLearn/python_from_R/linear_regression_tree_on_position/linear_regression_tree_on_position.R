x <- read.csv(file.choose(),stringAsFactors =FALSE)
view(x)
selectcolumn<-x[,2:3]
selectcolumn

#package used for splitting data to test and train

install.packages("caTools")
library(caTools)
set.seed(123)
split <- sample.split(selectcolumn$Salary, SplitRatio = 0.65)
split
training_set <- subset(selectcolumn, split == TRUE)
training_set
test_set <- subset(selectcolumn, split == FALSE)
test_set

#Fitting decision tree regression to the dataset

install.packages("rpart")
library(rpart)

regressor = rpart(Salary~ .,
                  data = training_set,
                  control = rpart.control(minsplit=2, cp=0.01))
regressor


# visualizing the decision tree structure
install.packages("rpart.plot")
library(rpart.plot)
par(mar = rep(2, 4))  #Adjusting margins
rpart.plot(regressor)

library(ggplot2)
x_grid <- seq(min(dataset$level), max(x$Level),0.01)
ggplot()+
  geom_point(aes(x = dataset$Level, y = dataset$salary),
             colour = 'red')
  geom_line()









