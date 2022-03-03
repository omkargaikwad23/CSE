import time
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import norm

# Reading the dataset
print("\n# Reading the dataset")
d = pd.read_csv("CarPrice_Assignment.csv")
df = pd.DataFrame(d)

# Check if a column has any missing values
print("\n# Check if a column has any missing values")
for i in df:
    print(f"{i}: {any(df[i].isna())}")


# the entire column has just one value 'front'
df.drop(columns=["enginelocation"],inplace=True)

# Change categorical to quantitative
print("\n# Change categorical to quantitative")
numWords={
    "one":1,
    "two":2,
    "three":3,
    "four":4,
    "five":5,
    "six":6,
    "eight":8,
    "twelve":12,

    "gas":0,
    "diesel":1,

    "std":0,
    "turbo":1
}
for i in numWords:
    df.replace(to_replace=i,value=numWords[i],inplace=True)
print(df)

# Boxplot the numerical values to find outliers
print("\n# Boxplot the numerical values to find outliers")
x=[
    "wheelbase",
    "carlength",
    "carwidth",
    "carheight"
]
df.boxplot(column=x)
plt.savefig("boxplot.png")
plt.close()


# Handling the outliers
'''
An Outlier is an observation in a given dataset that lies far from the rest of the observations. 
That means an outlier is vastly larger or smaller than the remaining values in the set.
An outlier may occur due to the variability in the data, or due to experimental error/human error.
They may indicate an experimental error or heavy skewness in the data(heavy-tailed distribution).
Mean is the accurate measure to describe the data when we do not have any outliers present.
Median is used if there is an outlier in the dataset.
Mode is used if there is an outlier AND about ½ or more of the data is the same.
‘Mean’ is the only measure of central tendency that is affected by the outliers which in turn impacts Standard deviation.

Below are some of the techniques of detecting outliers
Boxplots
Z-score
Inter Quantile Range(IQR)

Below are some of the methods of treating the outliers
Trimming/removing the outlier : Although it is not a good practice
Quantile based flooring and capping : at a certain value above the 90th percentile value or floored at a factor below the 10th percentile value.
Mean/Median imputation : As the mean value is highly influenced by the outliers, it is advised to replace the outliers with the median value.
'''


df2=df[x]
dfzscore=df[x]
for i in x:
    for j in range(len(df2[i])):
        dfzscore.loc[j,i] = (df2[i][j] - df2[i].mean()) / df2[i].std()
dfzscore.hist(bins=20)
range2 = np.arange(-4, 4, 0.001)
plt.plot(range2, norm.pdf(range2,0,0.3))
plt.savefig("hist_before.png")
plt.close()

print("\n# Handling the outliers")
for i in x:
    q1 = df[i].quantile(0.25)
    q3 = df[i].quantile(0.75)

    iqr = q3 - q1

    lower_limit = q1 - 1.5 * iqr
    upper_limit = q3 + 1.5 * iqr

    for j in range(len(df[i])):
        if df[i][j]<lower_limit:
            df.loc[j,i]=lower_limit
        if df[i][j]>upper_limit:
            df.loc[j,i]=upper_limit

print("Outliers were removed")
df.boxplot(column=x)
plt.savefig("boxplot_outlier_removed.png")
plt.close()

df2=df[x]
dfzscore=df[x]
for i in x:
    for j in range(len(df2[i])):
        dfzscore.loc[j,i] = (df2[i][j] - df2[i].mean()) / df2[i].std()
dfzscore.hist(bins=20)
range2 = np.arange(-4, 4, 0.001)
plt.plot(range2, norm.pdf(range2,0,0.3))
plt.savefig("hist_after.png")
plt.close()
# Performing normalization
'''
Normalization is a technique often applied as part of data preparation for machine learning.
The goal of normalization is to change the values of numeric columns in the
dataset to use a common scale, without distorting differences in the ranges
of values or losing information.

Z-score is a variation of scaling that represents the number of standard deviations away
from the mean. You would use z-score to ensure your feature distributions
have mean = 0 and std = 1. It's useful when there are a few outliers, but
not so extreme that you need clipping.

Another way to normalize the input features/variables (apart from the
standardization that scales the features so that they have μ=0and σ=1)
is the Min-Max scaler. By doing so, all features will be transformed
into the range [0,1] meaning that the minimum and maximum value of a
feature/variable is going to be 0 and 1, respectively.

'''
df2 = df[x]
print("\nBefore normalization")
print(df2.describe())

print("\nNormalization by z score")
dfzscore=df[x]
for i in x:
    for j in range(len(df2[i])):
        dfzscore.loc[j,i] = (df2[i][j] - df2[i].mean()) / df2[i].std()
print(dfzscore.describe())

dfzscore.boxplot()
plt.savefig("boxplot_zscore.png")
plt.close()

print("\nNormalization by min-max")
dfminmax=df[x]
for i in x:
    for j in range(len(df2[i])):
        dfminmax.loc[j,i] = (df2[i][j] - df2[i].min()) / (df2[i].max() - df2[i].min())
print(dfminmax.describe())

dfminmax.boxplot()
plt.savefig("boxplot_minmax.png")
plt.close()

df.to_csv("output.csv", index=False)

