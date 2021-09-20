#include <stdio.h>

void printArray( int *arr, int n ) {
	int i;
	printf("Values: \n");
	for( i=0; i<n; i++) 
		printf("%d ", arr[i]);
	
	printf("\n");
}

void selection_rec( int last, int n, int *arr) {
	
	/* retun to the caller if arr is sorted or if args are invalid */
	if( !last  || last >= n )
		return;
	
	int i, max, indexMax, temp;

	/* find element with highest value */
	indexMax = 0;
	max = arr[indexMax];
	for( i=1; i<last+1; i++) 
		if( max < arr[i] ) {
			indexMax = i;
			max = arr[indexMax];
		}
	/* swap last and max value */
	temp = arr[last];
	arr[last] = max;
	arr[indexMax] = temp;
		
/* debug printArray(arr, n); */
/* debug printf("Max=%d; last=%d\n\n", max, last); */

	/* sort unsorted part of the array */	
	selection_rec( last-1, n, arr );
}

int main() {
	int arr[] = {3,4,3,6,1,9,2,3,1};
	int n = sizeof arr / sizeof(*arr);
	selection_rec( n-1, n, arr);
	printArray(arr, n);
}
