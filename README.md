----
# Colorize_ratios Project

** Deprecated/ancient school project.

An image colorization project/algorithm attempt
that uses a memory and CPU-intensive "color-by-example"
approach to image colorization.

This project attempts to color a greyscale input image
by taking an array of input color images of the same subject,
identifying and recording "similar" areas (rather, swatches
and textures created from a a->b->c->... set of comparisons)
and their greyscale->color correlation throughout all said 
examples, and using these correlations to determine the most
"likely" color for a given pixel and/or swatch within the original 
greyscale image.

**AT THIS MOMENT**:
The algorithm uses far too much resources to complete on a consumer
machine within reasonable time, and a few switches were toggled to low 
amounts when trying to mitigate this. As such, the algorithms do not
work, but you can review this instance of this project to see the 
approach that I was taking.

----
## Requirements

make, NetPBM (present on most Linux distributions), G++

----
