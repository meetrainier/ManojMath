install.packages("randomForest")
# Load necessary libraries
library(randomForest)
library(datasets)  # for the iris dataset

# Load the Iris dataset
data(iris)

# Set seed for reproducibility
set.seed(42)

# Split the data into training and testing sets
sample_index <- sample(1:nrow(iris), 0.7 * nrow(iris))
train_data <- iris[sample_index, ]
test_data <- iris[-sample_index, ]

# Train the Random Forest model
rf_model <- randomForest(Species ~ ., data=train_data, ntree=100)

# Print the model
print(rf_model)

# Predict on the test data
predictions <- predict(rf_model, newdata=test_data)

# Evaluate the model
confusion_matrix <- table(test_data$Species, predictions)
print(confusion_matrix)

# Calculate accuracy
accuracy <- sum(diag(confusion_matrix)) / sum(confusion_matrix)
print(paste("Accuracy:", accuracy))
