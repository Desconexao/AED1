int compare( char *a, char *b )
{
    char ab[22];
    char ba[22];

    strcpy( ab, a );
    strcat( ab, b );

    strcpy( ba, b );
    strcat( ba, a );

    return strcmp( ab, ba );
}

void quickSort( char **array, int iLeft, int iRight )
{
    int     left;
    int     right;
    char    *pivot;

    left  = iLeft;
    right = iRight;
    pivot = array[( left + right ) / 2];

    while ( left <= right )
    {
        while ( compare( array[left], pivot ) > 0 )
        {
            left++;
        }

        while ( compare( array[right], pivot ) < 0 )
        {
            right--;
        }

        if ( left <= right )
        {
            char *temp;

            temp         = array[left];
            array[left]  = array[right];
            array[right] = temp;

            left++;
            right--;
        }
    }

    if ( iLeft < right )
    {
        quickSort( array, iLeft, right );
    }

    if ( left < iRight )
    {
        quickSort( array, left, iRight );
    }
}

char *largestNumber( int *nums, int numsSize )
{
    char    **array;
    char    *result;
    int     totalLen;
    int     i;

    array = malloc( numsSize * sizeof( char * ) );

    for ( i = 0; i < numsSize; i++ )
    {
        array[i] = malloc( 11 );
        sprintf( array[i], "%d", nums[i] );
    }

    quickSort( array, 0, nums
