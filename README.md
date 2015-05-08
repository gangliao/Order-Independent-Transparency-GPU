##Order Independent Transparency via Linked List Sorting on GPU

###Motivation

Transparency is a difficult effect to render accurately in pipeline architectures 
like OpenGL. Opaque objects can just cover the background. 
But for translucent objects, they must render by blending with the “background”.
Translucent objects must be rendered from far to near. It’s very complex 
and complicated to render pixels from far to near. A possible solution to this 
issue is Order Independent Transparency technique.

###Linked List Sorting

Order Independent Transparency is drawing objects in any order that can get 
accurate results. In fragment shader, depth sorting can be done so that the 
programmer need not sort objects before rendering. There are a variety of 
techniques for doing this. The most common one is to keep a list of colors 
for each pixel, sort them by depth, and then blend them together in the fragment 
shader.

###Algorithm Phase

The algorithm can be expressed as three phases:

1. Render opaque scene objects.
2. Render transparent scene objects.
    1. All fragments are stored using per-pixel linked lists.
    2. Store fragments: color, alpha, & depth.
3. Screen quad resolves and composites fragment lists.
    1. each pixel in fragment shader sorts associated linked list.
    2. blending fragments in sorted order with background.
    3. output final fragments.

###Result
In fragment shader, some classical sort algorithms are implemented. 

For instance, 

```
Insert Sort
Select Sort
Bubble Sort
Merge Sort
Shell Sort
```
The effect of OIT via merge sort is shown as the following figure.

<img src=”/result/oit.git” width=”60%”/> 



###COPYRIGHT
Gang Liao, liao.gang@kaust.edu.sa 

