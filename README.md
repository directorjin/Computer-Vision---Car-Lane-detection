# Computer-Vision---traffic-Lane-detection
Computer Vision - traffic Lane detection


Description
===========
  
This is the code that detects traffic lanes when given a picture.
----------------------------------------------
Lane detection is performed using Hough_Transform technology.
---------------------------------------------
And remove the wrong lines in a heuristic way.
---------------------------------------------------------------
  
<hr/>    


Project Solution design
-------------

1. Canny Detector to make it easier to find lines in the Hough transform Implement
  <img width="700" src="https://user-images.githubusercontent.com/44941601/72230266-9159d800-35f7-11ea-9f3e-2ed5a73312b7.png">
  
2. We then implement a Hough transform to detect the lines that we think are Car lanes.
<img width="700" src="https://user-images.githubusercontent.com/44941601/72230368-307ecf80-35f8-11ea-86a8-7abf0df5304a.png">  

3. Then heuristically removes non-car-lane lines.
  
  
  
  
<hr/>  
  
Test Results1
-------------

<img width="700" src="https://user-images.githubusercontent.com/44941601/71886545-c097c180-317f-11ea-974c-0b313509b398.jpg">  
<img width="700" src="https://user-images.githubusercontent.com/44941601/71886553-c2fa1b80-317f-11ea-8d4b-7917258adedb.jpg">  

<hr/>  
<hr/>  

Test Results2
-------------

<img width="700" src="https://user-images.githubusercontent.com/44941601/71886610-de652680-317f-11ea-96ca-b8a5fee07f19.jpg">  
<img width="700" src="https://user-images.githubusercontent.com/44941601/71886617-e1f8ad80-317f-11ea-85ec-4d1715520bfa.jpg">  



<hr/>  
VS2017, OpenCV    

