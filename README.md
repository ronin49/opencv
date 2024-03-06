# opencv

https://opencv.org/releases/

oleg@oleg-MS-7918:~$ cd /usr/local/include/opencv4/
oleg@oleg-MS-7918:/usr/local/include/opencv4$ ls
opencv2
oleg@oleg-MS-7918:/usr/local/include/opencv4$ cp -r opencv2/ ..
cp: cannot create directory '../opencv2': Permission denied


g++ main.cpp -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio



LD_LIBRARY_PATH=/usr/local/lib ./a.out
