# median-image-filtering
CSC382 Analysis of Algorithms Final Project

# median-image-filtering
Analysis of Algorithms Final Project

**Part I: Implement the order statistic algorithm.**

Generate n random numbers in the range of [1..N], which are unordered. 
Implement the order statistic algorithm we studied in the class and run the order statistic experiment to find the ith smallest number. Note that you can vary the population size N and the sample size n where N=5000, 8000, 10000 and n= 100, 300, 500, 1000, 2000, 4000. Pick i as the random number in 1..n five times.

Note: 
- You may have to repeat the algorithm many times, each time you need to initialize the array. 
- Your running time should exclude the time for initialization.  (3) All measurement should be done in a single run, i.e. you do not need to run once for n=100, another time for n=200, etc

What to turn in:
- Well documented source code in C++
-	Report the CPU running time in a table for all combinations of n, N and order i; report average CPU running time on order i in a table for all combinations of n and N.
- Plot the running time of the algorithm results for all combination of n and N.

**Part II. Apply your algorithm to median filtering of an image** 

Apply your algorithm to median filtering of an image, which is a technique for smoothing a "noisy" image. For each pixel of an image, the filtering procedure considers an (n x n) window centered on that pixel, computes the median of gray-level values in the window, and replaces the original pixel with the median value. The median is defined as the middle value in a sorted sequence. For example, consider the following (3 x 3) window of pixels:
 11	 90	 74
 71	 14	 92
 20	 87	 68
The sorted sequence of these pixels is <11, 14, 20, 68, 71, 74, 87, 90, 92>, and the middle of the sequence is 71, which is the median of the window; thus, the filtering procedure will replace the center pixel with 71.
The result of replacing all pixels with median values is a smoothed image, with almost no background noise, which improves the effectiveness of image-recognition algorithms. On the negative side, the new image is blurrier than the original, that is, it looks like an unfocussed monitor.
Note:
- The window size, N, is one input. That is, if user inputs N=5, then the window is 5*5.
- The other input is the original image that you will convert. 
- The output is the converted image.
---
