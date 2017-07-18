# MarchingSquare
Find Contours in a picture by Marching Square Algorithm

## 概述 Summary
设计了一个类，类中的函数可根据图片数据，通过Marching Square算法，找出图片中的等高线，并将所有等高线存入一个链表表格(ListTable)中。<br>

## 关于链表表格(ListTable)
- 链表表格(ListTable)实际上为链表(LinkedList)的链表，每个ListTable的结点下连接了不定数量的链表(LinkedList)。<br>
- 链表表格(ListTable)中的项数和所设定的等高线条数相同，即每一项代表了一个高度下的数条等高线。<br>
- 链表表格(ListTable)中每一项之下的所有链表(LinkedList)的等高线高度相同，每个链表(LinkedList)代表一条等高线。<br>
- 链表(LinkedList)中的各项为点的坐标(x,y)。<br>
- 链表(LinkedList)中的首项为一条等高线的一端，末项为另一端。若等高线为闭合曲线，则首项与末项在图中为相邻的两点。<br>
- 无论等高线是否为闭合曲线，对应的链表(LinkedList)末项的next指针都指向了首项。<br>

## 算法步骤
1. 在原图的上、下、左、右四个方向上拓展一条宽度为1的边缘，以白色(非所需区域颜色)填充。
2. 找出所需圈出的色块的边缘上某一点。
3. 从该点开始，按逆时针方向勾出该色块的边缘，存入一个链表中。
4. 从2中所找到的点开始，重复2.和3.的步骤。
5. 部分链表中可能包含大量1.中所拓展的边缘，需要对对应的链表进行调整，删除边缘上的点，有时还需要进行切割。
<br><br>
有关MarchingSquare算法的信息参考:<br>
[Marching Squares Wiki](https://en.wikipedia.org/wiki/Marching_squares)<br>
[利用marching square algorithm获取图形轮廓](http://blog.csdn.net/coolingcoding/article/details/17278959)<br>
