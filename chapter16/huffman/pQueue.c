#include "pQueue.h"
#include <stdlib.h>
#include <stdio.h>

void initPQueue(pQueue **queue)
{
	//We allocate memory for the priority queue type
	//and we initialize the values of the fields
    /* 为优先队列分配内存并初始化其变量 */
	(*queue) = (pQueue *) malloc(sizeof(pQueue));
	(*queue)->first = NULL;
	(*queue)->size = 0;
	return;
}
void addPQueue(pQueue **queue, TYPE val, unsigned int priority)
{
	//If the queue is full we don't have to add the specified value.
	//We output an error message to the console and return.
    /* 如果队列已满，输出错误信息然后返回 */
	if((*queue)->size == MAX_SZ)
	{
		printf("\nQueue is full.\n");
		return;
	}

	pQueueNode *aux = (pQueueNode *)malloc(sizeof(pQueueNode));
	aux->priority = priority;
	aux->val = val;

	//If the queue is empty we add the first value.
	//We validate twice in case the structure was modified abnormally at runtime (rarely happens).
    /* 如果队列是空的就添加第一个值，我们验证两次以防数据结构在运行的时候被不正常的修改(很少发生) */
	if((*queue)->size == 0 || (*queue)->first == NULL)
	{
		aux->next = NULL;
		(*queue)->first = aux;
		(*queue)->size = 1;
		return;
	}
	else
	{
		//If there are already elements in the queue and the priority of the element
		//that we want to add is greater than the priority of the first element,
		//we'll add it in front of the first element.
        /*
         * 如果队列中已经有元素了并且我们要添加的元素的优先级比第一个元素的
         * 优先级还高，我们把它添加到第一个元素之前。
         */

		//Be careful, here we need the priorities to be in descending order
        /* 小心，在这里我们需要优先级按递减顺序排序 */
		if(priority<=(*queue)->first->priority)
		{
			aux->next = (*queue)->first;
			(*queue)->first = aux;
			(*queue)->size++;
			return;
		}
		else
		{
			//We're looking for a place to fit the element depending on it's priority
            /*
             * 根据元素的优先级找到一个合适的位置
             * iterator为迭代器的意思
             */
			pQueueNode * iterator = (*queue)->first;
			while(iterator->next!=NULL)
			{
				//Same as before, descending, we place the element at the begining of the
				//sequence with the same priority for efficiency even if
				//it defeats the idea of a queue.
				if(priority<=iterator->next->priority)
				{
					aux->next = iterator->next;
					iterator->next = aux;
					(*queue)->size++;
					return;
				}
				iterator = iterator->next;
			}
			//If we reached the end and we haven't added the element,
			//we'll add it at the end of the queue.
            /* 到达末尾都没有添加元素，所以直接加到队列的末尾 */
			if(iterator->next == NULL)
			{
					aux->next = NULL;
					iterator->next = aux;
					(*queue)->size++;
					return;
			}
		}
	}
}

TYPE getPQueue(pQueue **queue)
{
	TYPE returnValue;
	//We get elements from the queue as long as it isn't empty
    /* 只要队列不是空的就从中拿走元素 */
	if((*queue)->size>0)
	{
		returnValue = (*queue)->first->val;
		(*queue)->first = (*queue)->first->next;
		(*queue)->size--;
	}
	else
	{
		//If the queue is empty we show an error message.
		//The function will return whatever is in the memory at that time as returnValue.
		//Or you can define an error value depeding on what you choose to store in the queue.
        /*
         * 如果队列是空的就输出错误信息，
         * 但是这个函数无论returnValue这时在内存中是什么值都会将其返回，
         * 或者你可以根据存储在队列中的值来自己定义returnValue的值。
         */
		printf("\nQueue is empty.\n");
	}
	return returnValue;
}
