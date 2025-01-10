#hierchial cluster

iris
iris1=iris
iris1
iris1$species=NULL
View(iris1)

d=dist(iris1, method = "euclidean")
d

hfit = hclust(d, method = "average")
plot(hfit)


grps = cutree(hfit,k=4)
grps

rect.hclust(hfit,k=2, border ="red")
rect.hclust(hfit, k=4, border = "orange")

