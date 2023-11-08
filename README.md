# PerceptronRemembersPicture
Simple multilayer perceptron remembers the pictures.

The task is to teach a multi-layered perceptron to draw one specific picture.
The perceptron code is taken from my other [repository](https://github.com/VladislavWaza/SimpleMultilayerPerceptron) and slightly modified for this task.

I believe that the task has been successfully achieved.

## Examples of how the program works

The **original** is displayed on the **left**, the **image drawn by the neural network** is displayed on the **right**.

Information about the image size, neural network structure, activation function, permissible deviation, and operating time is displayed in the center.

The program saves the image closest to the original, and provides functionality for displaying it.

### The program successfully copes with a small image.
<img src="https://github.com/VladislavWaza/PerceptronRemembersPicture/assets/73028197/95005b26-f922-4c25-bead-976d1dc6e11e">

![2](https://github.com/VladislavWaza/PerceptronRemembersPicture/assets/73028197/5fda886a-2e6d-473d-9674-8dd00bb7bbfd)

### What about a bigger image?

![1](https://github.com/VladislavWaza/PerceptronRemembersPicture/assets/73028197/4da5eeff-aa61-4c54-b54e-ca593bb46087)
### In general, the neural network coped, but not without errors.
### What about a large and complex image?
![4](https://github.com/VladislavWaza/PerceptronRemembersPicture/assets/73028197/439189b6-b445-4358-8e8f-36c4a596da1f)

If you look closely, you will notice that the images are blurred, and strong distortions appear from the upper edge. 
Distortions from above appear due to the fact that pixels are fed sequentially to the input of the neural network (from top to bottom, from left to right), and not randomly.

You can also notice that the number of pixels that match the original is small, no more than 10 percent, and in some images no more than 2 percent, but our eye does not even see this difference.

## Bonus: training process

![ezgif-3-f61b4fb5fe](https://github.com/VladislavWaza/PerceptronRemembersPicture/assets/73028197/f4b33977-ec69-4817-ae80-280e541d00cc)
