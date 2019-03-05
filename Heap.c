#include <stdio.h>
#include <stdlib.h>

/*
	1. Heap is usually implemented by array.
	2. All elements form uppers layer must be grater than 
	   lower layers.
	3. If only one element doesn't follow rule 2 (rest
	   all follow rule 2), we can use 2 methods (swim 
	   and sink) to adjust the arry and rebuild heap stycture.
	4. Given a random array, if we use swim method, we should
	   start from second element since first element itself 
	   is heap structure, now we consider 1 and 2, and we 
	   assume 2nd element doesn't follow rule 2, so we run 
	   siwm and rebuild heap structure and 3, 4, 5... so on.
	5. Given a random array, if we want to use sink method,
	   we should start form last element of the second last 
	   layer since there is only 1 element doesn't followed 
	   rule 2 in the last 2 or 3 elements.
	6. If we has already known one array is heap, and want to
	   delete or add new element, time complecxity is O(lgn)
	   since we only need to run swim or sink once.
	7. For random array, time complexity to build heap is
	   O(nlgn) since we have to move each element fron its
	   position to top or bottom.
	8. I didn't use array[0] sicne it doesn't follow parent 
	   and child reation. 
*/


void sink(int *p, int index, int length);
void swim(int *p, int index, int length);
void exchange(int *p, int i, int j);
void buildHeapBySwim(int *p, int length);
void buildHeapBySink(int *p, int length);

int main()
{
	int p[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int length = sizeof(p) / sizeof(p[0]);
	buildHeapBySink(p, length);
	for (int i = 0; i < length; i++) printf("%d ", p[i]);
	return 0;
}

//Swim move elemets upward. 
void swim(int *p, int index, int length)
{
	if (index > length - 1) return;
	while (index/2 > 0)
	{
		if (p[index] > p[index / 2])
		{
			exchange(p, index, index/2);
			index = index / 2;
		}
		else break;
	}
}

//First element itself is heap. Then we build 2 element's
//heap, 3 element's heap...
void buildHeapBySwim(int *p, int length)
{
	for (int i = 1; i < length; i++)
		swim(p, i, length);
}

void sink(int *p, int index, int length)
{
	if (index > length - 1) return; //Out of range.
	//Last element itself is heap, doesn't need to check.
	while (index * 2 < length - 1) 
	{
		int largest = index;
		int left_child = index * 2;
		int right_child = index * 2 + 1;
		if (left_child < length && p[left_child] > p[largest]) largest = left_child;
		if (right_child < length && p[right_child] > p[largest]) largest = right_child;

		if (largest != index)
		{
			exchange(p, largest, index);
			index = largest;
		}
		else break;
	}
}

void buildHeapBySink(int *p, int length)
{
	for (int i = (length - 1) / 2; i > 0; i--)
		sink(p, i, length);
}

void exchange(int *p, int i, int j)
{
	int temp = p[i];
	p[i] = p[j];
	p[j] = temp;
}