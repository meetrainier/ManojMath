library(ggplot2)
data("ToothGrowth")
a<-as.data.frame(ToothGrowth)
View(a)
ggplot(a, aes(x = dose, y = len, color = supp, group = supp)) +
  stat_summary(fun = mean, geom = "line", linewidth  = 1) + 
  stat_summary(fun = mean, geom = "point", size = 3) + 
  labs(
    title = "Average Tooth Length by Dose and Supp",
    x = "Dose",
    y = "Average Tooth Length"
  ) +
  theme_minimal()

ggplot(a, aes(x = as.factor(dose), y = len, fill = supp)) +
  geom_boxplot() +
  labs(
    title = "Tooth Length by Dose and Supp",
    x = "Dose",
    y = "Tooth Length"
  ) +
  theme_minimal()

