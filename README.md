# MarchingSquare
Find Contours in a picture by Marching Square Algorithm

## 概述 Summary
设计了一个类，类中的函数可根据图片数据，通过Marching Square算法，找出图片中的等高线，并将所有等高线存入一个链表表格(ListTable)中。<br>
>关于链表表格(ListTable)：<br>
>- 链表表格(ListTable)实际上为链表(LinkedList)的链表，每个ListTable的结点下连接了不定数量的链表(LinkedList)。<br>
>- 链表表格(ListTable)中的项数和所设定的等高线条数相同，即每一项代表了一个高度下的数条等高线。<br>
>- 链表表格(ListTable)中每一项之下的所有链表(LinkedList)的等高线高度相同，每个链表(LinkedList)代表一条等高线。<br>
>- 链表(LinkedList)中的各项为点的坐标(x,y)。<br>
>- 链表(LinkedList)中的首项为一条等高线的一端，末项为另一端。若等高线为闭合曲线，则首项与末项在图中为相邻的两点。<br>
>- 无论等高线是否为闭合曲线，对应的链表(LinkedList)末项的next指针都指向了首项。<br>

