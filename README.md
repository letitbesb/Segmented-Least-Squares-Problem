# Segmented-Least-Sqaures-Problem
C++ program to solve the Segmented Least Squares Problem. Visualization using Python , Matplotlib


## A General Discussion of the Algorithm : 

  The Segmented Least Squares (SLS) algorithm is a powerful technique used to model data points by dividing them into segments and fitting a linear regression model to each segment. This approach is particularly useful when dealing with non-linear data or data with multiple trends. The main goal of the SLS algorithm is to minimize the overall error while maintaining a balance between the goodness of fit and the number of segments.

  Problem Formulation:
  Given a set of data points (x1, y1), (x2, y2), ..., (xn, yn), the objective of the Segmented Least Squares problem is to partition the data into segments and fit a linear model to each segment such that the total error is minimized. The error is defined as the sum of squared differences between the actual data points and the predicted values from the linear models.


The problem can be formulated as an optimization problem:
Minimize: ∑(∑(yi - (ai + bi * xi))^2) + C * L
where: i ranges from 1 to n (number of data points)
L is the number of segments
C is a constant penalty term for each additional segment
ai and bi are the coefficients of the linear model for each segment
  
  
## Approach :
   **Dynamic Programming Solution:**
   
  The Segmented Least Squares problem can be efficiently solved using dynamic programming. The key idea is to compute the optimal solution for smaller subproblems and use these solutions to construct the optimal solution for the original problem. The dynamic programming approach involves the following steps:
  Precompute the error for all possible segments.
  Define a recurrence relation for the optimal solution.
  Implement a bottom-up approach to compute the optimal solution.
  Reconstruct the optimal segmentation and linear models.

**Time Complexity:**

  - The time complexity of the dynamic programming solution for the Segmented Least Squares problem is O(n^2), where n is the number of data points. This is because the algorithm needs to compute the error for all possible segments, which takes O(n^2) time, and then fill the dynamic programming table, which also takes O(n^2) time.

**Applications:**

  - The Segmented Least Squares algorithm has numerous applications in various fields, including: Time series analysis: Identifying trends and changes in time series data. Image processing: Detecting edges and boundaries in images. Bioinformatics: Analyzing DNA sequences and gene expression data. Finance: Modeling stock prices and market trends.

**Conclusion:**

  - The Segmented Least Squares algorithm is an effective technique for modeling complex data with multiple trends. By dividing the data into segments and fitting a linear model to each segment, the algorithm can accurately capture the underlying patterns in the data. The dynamic programming approach ensures an efficient solution, making the algorithm suitable for a wide range of applications.


![image](https://user-images.githubusercontent.com/29221347/235538823-04e351ce-64de-4861-8914-d07f5cbbe176.png)



**The algorithm for final solution** :

```
Find-Segment(j)
	If j== 0 then 
		Output nothing
	Else
		Find an i that minimizes ei,j + C + M[i-1]
		Output the segment {pi, …,pj} and the   
     result of Find-Segment(i-1)
   Endif

 ```
      
     
## **Results :**  


* **1st Testcase :**

  ![image](https://user-images.githubusercontent.com/29221347/235539417-3e515759-2c43-4ff1-aebd-8a3b18f043f8.png)

  
  
* **2nd Testcase :**


  ![image](https://user-images.githubusercontent.com/29221347/235539454-232f0a2c-594e-41dc-96a0-bfbebe18cec7.png)


* **3rd Testcase :**


  ![image](https://user-images.githubusercontent.com/29221347/235539515-9d11a2ad-12b6-4381-b82a-980d24c03cef.png)


* **Timing Analysis on Size of Testcase :**


  ![image](https://user-images.githubusercontent.com/29221347/235539541-80410007-21ee-4761-a7ae-34ff1c51dc0e.png)




