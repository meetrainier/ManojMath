# Even Set
# 1. A policy researcher aims to group US states based on crime rates (murder, assault, urban population, and rape) to uncover crime patterns nationwide. Apply Naïve Bayes to the USArrests dataset (an in-built dataset).
# 2. Apply Linear and Polynomial Regression on Social dataset. Use plots to see how well each model fits the data, and we predict salaries for a given age using both models. Write the R code to visualize the actual data points along with the polynomial regression curve.
# 3. Load and prepare the data (Boston dataset inbuilt). Normalize the data to make all features comparable. Split the data into training and testing sets. Build a neural network model with two hidden layers. Make predictions using the test data. Evaluate how good the predictions are by checking the correlation. (Install MASS package for dataset)

# ans1 
install.packages("e1071")
library(e1071)
x=data("USArrests")
str(x)
View(x)
scaled_data = scale(USArrests)
total_crime = rowSums(scaled_data)
crime_category=ifelse(total_crime > median(total_crime), "High", "Low")
data_with_category=data.frame(scaled_data, CrimeCategory = crime_category)


set.seed(123)
index = sample(1:nrow(data_with_category), 0.7*nrow(data_with_category))
train_data = data_with_category[index, ]
test_data = data_with_category[-index, ]

model =naiveBayes(CrimeCategory~., data=train_data)
predictions= predict(model, test_data)
summary(predictions)

#ans2
social <- read.csv(file.choose(), stringsasfactors = false)
social
view(social)
summary(social)

social = social[3:4]
social

#fitting linear regression to the dataset
lin_reg = lm(formula =  EstimatedSalary ~ .,
             data = social)
summary(lin_reg)

#fitting polynomial regression to the dataset
social$Age2 = social$Age^2
social$Age3 = social$Age^3
social$Age4 = social$Age^4
social

poly_reg = lm(formula = EstimatedSalary ~.,
              data = social)
summary(poly_reg)

social$Age2
social$Age3
social$Age4

#visualising the linear regression results
library(ggplot2)
ggplot() + 
  geom_point(aes(x = social$Age, y = social$EstimatedSalary),
             colour = 'red') +
  geom_line(aes(x = social$Age, y = predict(lin_reg, newdata = social)),
            colour = 'blue') +
  ggtitle('Truth or Bluff (Linear Regression') +
  xlab('Age') +
  ylab('EstimaetdSalary')

#visualising the Polynomial regression results
ggplot() + 
  geom_point(aes(x = social$Age, y = social$EstimatedSalary),
             colour = 'red') +
  geom_line(aes(x = social$Age, y = predict(poly_reg, newdata = social)),
            colour = 'blue') +
  ggtitle('Truth or Bluff (Polynomial Regression') +
  xlab('Age') +
  ylab('EstimaetdSalary')

#ans3
install.packages("MASS")
library(MASS)
install.packages("neuralnet")
library(neuralnet)
c=data("Boston")
library(caTools)

data("Boston")
View(data)
normalize =function(x) {
  return ((x - min(x)) / (max(x) - min(x)))
}

boston_normalized= as.data.frame(lapply(Boston, normalize))

# Split data training 70 and testing 30 
set.seed(123)
split=sample.split(boston_normalized$medv, SplitRatio = 0.7)
train_data = subset(boston_normalized, split == TRUE)
test_data=subset(boston_normalized, split == FALSE)
set.seed(123)
nn_model=neuralnet(medv ~ ., data = train_data, hidden = c(5, 5), linear.output = TRUE)
plot(nn_model)
predictions=compute(nn_model, test_data[,-14])$net.result
# Since we normalized the data, we need to back-transform the predictions
# Reversing the normalization for comparison with the actual values
predictions_denormalized =predictions * (max(Boston$medv) - min(Boston$medv)) + min(Boston$medv)
actual_denormalized=test_data$medv * (max(Boston$medv) - min(Boston$medv)) + min(Boston$medv)
correlation=cor(predictions_denormalized, actual_denormalized)
cat("Correlation between predicted and actual values:", correlation, "\n")



#1)
install.packages("e1071")
install.packages("caTools")
library(e1071)
library(caTools)
data("Titanic")
y <- as.data.frame(Titanic)
y<- y[rep(row.names(y), y$Freq),]
y$Freq <- NULL
y$Survived <- as.factor(y$Survived)
set.seed(123)
split <- sample.split(y$Survived, SplitRatio = 0.7)
train <- subset(y, split == TRUE)
test <- subset(y, split == FALSE)
train
test
model <- naiveBayes(Survived ~ ., data = train)
predictions <- predict(model, test)
matrix <- table(predictions, test$Survived)
print(matrix)


#2)
install.packages("MASS")
install.packages("neuralnet")
install.packages("caret")
library(MASS)
library(neuralnet)
library(caret)
data("Boston")
normalize <- function(x) {
  return((x - min(x)) / (max(x) - min(x)))
}
boston_norm <- as.data.frame(lapply(Boston, normalize))
set.seed(123)
trainIndex <- createDataPartition(boston_norm$medv, p = 0.7, list = FALSE)
trainData <- boston_norm[trainIndex, ]
testData <- boston_norm[-trainIndex, ]
nn_model <- neuralnet(medv ~ ., data = trainData, hidden = c(5, 5, 5), linear.output = TRUE)
plot(nn_model)
nn_predictions <- compute(nn_model, testData[, -14])$net.result
correlation <- cor(nn_predictions, testData$medv)
print(paste("Correlation between predicted and actual values: ", correlation))


#3)

install.packages("ggplot2")
library(ggplot2)
data(mtcars)
model <- lm(mpg ~ poly(hp, 2, raw = TRUE), data = mtcars)
mtcars$mpg_pred <- predict(model, mtcars)
ggplot(mtcars, aes(x = hp, y = mpg)) +
  geom_point() +
  stat_smooth(method = "lm", formula = y ~ poly(x, 2, raw = TRUE), col = "red") +
  labs(title = "Polynomial Regression", x = "Horsepower", y = "Miles Per Gallon")