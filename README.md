# HRI
Human Readable Image Format

The Human Readable Image Format is an image format that can be easily understood by a normal person.

The file must start with `#HRI` This tells the program that the file it's reading is in fact a HRI file.
After defining the filetype to the program you must tell the program if you're writing the pixels colours in rgb or hex, you can do this with `!rgb` or `!hex` respectively.
Next you must tell the program the size of the image, the size can go up to 300x300 and can technically be at any aspect ratio, however, currently the viewer doesn't play nicely
with very disproportionate aspect ratios, you can define the size with `!{width, height}` replacing width and height with their respective values. All three of these definitions
should be on seperate lines, they don't have to be but the program will likely crash if they're not.

Now you can get to defining the colour of the pixels, you do this by using the respective colour format in between a set of curly brackets, so a pixel should look like `{Pixel colour in format}`
so a full rgb pixel would be `{255, 0, 0, 255}` and that would produce a red pixel. Make sure you have the right number of pixels!

Once you finish defining the pixels you're all good to run the file!

# HRI FILES USE A DIFFERENT TYPE OF COLOUR THEN THE USUAL RGB AND 6-DIGIT HEX! INSTEAD IT USES A RGBA FORMAT WHERE THE ALPHA CHANNEL ALSO GOES UP TO 255! AN 8-DIGIT HEX IS ALSO USED OVER THE 6-DIGIT HEX WITH THE LAST TWO DIGITS BEING THE ALPHA CHANNEL!
