# antiPixel
👾 Convert BMPs and text files to proper x8086 assembly arrays
Author: Saad Bazaz

Basic image reading and manipulation in C++, in Visual Studio 2019. Converts 24-bit BMP and properly 
formatted txt files into MASM code.

Note:
Currently works on white background and black object (see the cactus_example if you need help drawing)


<<<<<    USE cactus_example.bmp OR cactus_example.txt AS DEMO RUNS     >>>>>

HOW TO USE METHOD 1:
1. Create a pixel drawing in mspaint on 25x25 canvas
2. Save As => BMP Picture => (24-bit Bitmap)
3. Go to https://www.text-image.com/convert/pic2ascii.cgi, convert the BMP to text
4. Save the text in a txt file, place it in the program's solution folder
5. Compile the program and feed it the text file



HOW TO USE METHOD 2:
1. Don't.



HOW TO USE METHOD 3:
1. Create a pixel drawing in mspaint on 25x25 canvas
2. Save As => BMP Picture => (24-bit Bitmap)
3. Place the image in the program's solution folder
4. Compile the program and feed it the bmp file


![Colors](Color Assignments.PNG)


TROUBLESHOOTING:
- if you can't find the User_Results folder, make it yourself or download the latest build
a) STRUCTURE
User_Results =>
-     BMPColorASM
-     BMPMonoASM
-     TextToASM
  
- Sometimes the arrays may be terminated by an extra comma so remove that before running the arrays.
- Further, the program has NOT been tested on images larger than 25x25 PIXELS. Avoid using bigger pictures.
- The program has not been tested with images generated from different programs, like GIMP or Photoshop. In those cases, 
you would have to look up the HEADER SIZE and change it in the Advanced Configurations
