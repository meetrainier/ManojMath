View(mtcars)
help(mtcars)
str(mtcars)
set.seed(123)
index<-sample(1:nrow(mtcars),0.7*nrow(mtcars))
train_data=mtcars[index, ]
test_data=mtcars[-index,]
library(e1071)
classifier = svm(
  formula = mpg~.,
  data=train_data,
  type='eps-regression',
  kernel='linear'
)
y_pred <- predict(classifier, newdata = test_data)
y_pred

