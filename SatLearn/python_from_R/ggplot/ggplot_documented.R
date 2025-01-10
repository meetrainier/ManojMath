# Load the ggplot2 library for data visualization.
library(ggplot2)

# Load the built-in ToothGrowth dataset, which contains information on tooth length.
data("ToothGrowth")

# Convert the dataset into a data frame for easier manipulation (optional in this case).
a <- as.data.frame(ToothGrowth)

# View the dataset in a spreadsheet-like format (only works in RStudio or similar environments).
View(a)

# Plot 1: Line and point plot showing the average tooth length by dose and supplement type.
ggplot(a, aes(x = dose, y = len, color = supp, group = supp)) +
  # Add lines connecting the mean values of tooth length for each dose, grouped by supplement type.
  stat_summary(fun = mean, geom = "line", linewidth = 1) + 
  # Add points representing the mean values of tooth length for each dose, grouped by supplement type.
  stat_summary(fun = mean, geom = "point", size = 3) + 
  # Add titles and axis labels to the plot.
  labs(
    title = "Average Tooth Length by Dose and Supp", # Main title of the plot.
    x = "Dose",                                    # Label for the x-axis.
    y = "Average Tooth Length"                     # Label for the y-axis.
  ) +
  # Apply a minimal theme to the plot for a clean and simple appearance.
  theme_minimal()

# Plot 2: Boxplot showing the distribution of tooth lengths by dose and supplement type.
ggplot(a, aes(x = as.factor(dose), y = len, fill = supp)) +
  # Add boxplots for tooth length grouped by dose (converted to a categorical variable) and supplement type.
  geom_boxplot() +
  # Add titles and axis labels to the plot.
  labs(
    title = "Tooth Length by Dose and Supp", # Main title of the plot.
    x = "Dose",                            # Label for the x-axis.
    y = "Tooth Length"                     # Label for the y-axis.
  ) +
  # Apply a minimal theme to the plot for a clean and simple appearance.
  theme_minimal()
