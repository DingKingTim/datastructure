>
> [1、选择排序](#1)
>
> [2、插入排序](#2)
>
> [3、冒泡排序](#3)
>


<h3 id=1> 1、选择排序 </h3>

<h4 id=1.1> 复杂度 </h4>

  - 时间： 内外两层循环，因此是 O(n^2)
  - 内存空间：有限的范围内，没有多余开辟内存，内存 = 元素个数 * 元素大小

<h4 id=1.2> 算法原理 </h4>

- 两层循环，外层循环的搜索范围 【0，size-1），索引为 `i`
- 内层循环在 【i+1, size) 的范围内找出比当前外层`i`位置处要小的元素，且找出元素是该区间内最小的

![select_sort](https://github.com/DingKingTim/datastructure/blob/master/tree/media/select_sort.png)


<h3 id=2> 2、插入排序 </h3>

<h4 id=2.1> 复杂度 </h4>

  - 时间： 内外两层循环，因此是 O(n^2)
  - 内存空间：有限的范围内，额外开辟了一个空间用来存储临时比较key，内存 ≈ 元素个数 * 元素大小

<h4 id=2.2> 算法原理 </h4>

算法原理同纸牌，每次借一张牌，然后从后往前依次比较，找到合适位置插入

![insert sort](https://github.com/DingKingTim/datastructure/blob/master/tree/media/insert_sort.png)


<h3 id=3> 3、冒泡排序 </h3>

<h4 id=3.1> 复杂度 </h4>

  - 时间： 内外两层循环，因此是 O(n^2)
  - 内存空间：内存 ≈ 元素个数 * 元素大小
  
<h4 id=3.2> 算法原理 </h4>

自底向上循环比较，每扫描一次，就在扫描范围内产生一个最大值，并存储到顶部，这样保证扫描n-1次之后顶部的元素是排好序的

- 第一次循环

![bubble sort](https://github.com/DingKingTim/datastructure/blob/master/tree/media/bubble-1.png)

- 第二次循环

![bubble sort](https://github.com/DingKingTim/datastructure/blob/master/tree/media/bubble-2.png)
