import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Load the ToothGrowth dataset (manually entering data, as it's not in Python's standard datasets).
data = {
    'len': [4.2, 11.5, 7.3, 5.8, 6.4, 10.0, 11.2, 12.5, 15.2, 17.3, 15.2, 18.2, 10.0, 23.0, 22.5, 25.5, 26.4, 32.5],
    'supp': ['VC', 'VC', 'VC', 'VC', 'VC', 'VC', 'VC', 'VC', 'VC', 'VC', 'OJ', 'OJ', 'OJ', 'OJ', 'OJ', 'OJ', 'OJ', 'OJ'],
    'dose': [0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 2.0, 2.0, 0.5, 1.0, 2.0]
}
df = pd.DataFrame(data)

# Convert dose to a categorical variable for better visualization (for boxplots).
df['dose'] = df['dose'].astype('category')

# Plot 1: Line and point plot showing the average tooth length by dose and supplement type.
plt.figure(figsize=(8, 6))
sns.lineplot(
    data=df,
    x='dose',
    y='len',
    hue='supp',
    estimator='mean',
    marker='o',
    linewidth=2
)
plt.title('Average Tooth Length by Dose and Supp')
plt.xlabel('Dose')
plt.ylabel('Average Tooth Length')
plt.legend(title='Supplement Type')
plt.grid(True)
plt.show()

# Plot 2: Boxplot showing the distribution of tooth lengths by dose and supplement type.
plt.figure(figsize=(8, 6))
sns.boxplot(
    data=df,
    x='dose',
    y='len',
    hue='supp'
)
plt.title('Tooth Length by Dose and Supp')
plt.xlabel('Dose')
plt.ylabel('Tooth Length')
plt.legend(title='Supplement Type')
plt.grid(True, axis='y')
plt.show()
