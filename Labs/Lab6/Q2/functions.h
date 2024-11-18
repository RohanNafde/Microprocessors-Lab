void bubbleSort(int arr[]);
int search(int arr[], int x);

int i, j, t;

void bubbleSort(int arr[])
{
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4 - i ; j++)
		if (arr[j] > arr[j + 1])
		{
			t = arr[j];
			arr[j] = arr[j+1];
			arr[j+1] = t;
		}
	}
}

int search(int arr[], int x)
{
	int i;
	for (i = 0; i < 5; i++)
		if (arr[i] == x)
			return i;
	return -1;
}