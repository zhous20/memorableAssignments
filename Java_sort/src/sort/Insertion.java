package sort;

public class Insertion 
{
  /**
   * change the value at i and j
   * @param x - the jobs' array
   * @param i - the position of left value
   * @param j - the position of right value
   */
  private static void exchange(Comparable[] x, int i, int j)
  {
    Comparable temp = x[i];
    x[i] = x[j];
    x[j] = temp;
  }

	/**
	 * regular insertion sort
	 * @param x - the input array containing jobs that need to be sorted.
	 */
	public static void sortInsert ( Job[] x ) 
  {
		for(int i = 1; i < x.length; ++i)
    {
      for(int j = i; j > 0; --j)
      {
        if(x[j].compareTo(x[j-1]) < 0)
        {
          exchange(x,j,j-1);
        }
        else
        {
          break;
        }
      }
    }
	}

	/**
	 * insertion sort using Comparable
	 * @param x - the input array containing jobs that need to be sorted.
	 * @param n - the size of the input array
	 */
	public static void sortComparable ( Comparable[] x, int n ) 
  {
		for(int i = 1; i < n; ++i)
    {
      for(int j = i; j > 0; --j)
      {
        if(x[j].compareTo(x[j-1]) < 0)
        {
          exchange(x,j,j-1);
        }
        else
        {
          break;
        }
      }
    }
	}

  /**
   * binary search
   * @param x - the input array containing jobs.
   * @param low - the start of jobs
   * @param high - the end of jobs
   * @param value - the value need to be found
   * @return the found position
   */
  private static int binarySearch(Comparable[] x, int low, int high, Comparable value)
  {
    while(low <= high)
    {
      int mid = low + (high - low) / 2;
      if(x[mid].compareTo(value) > 0)
      {
        high = mid - 1;
      }
      else
      {
        low = mid + 1;
      }
    }
    return low;
  }

	/**
	 * optimized insertion sort
	 * @param x - the input array containing jobs that need to be sorted.
	 * @param n - the size of the input array
	 */
	public static void sortBinary ( Comparable[] x, int n ) 
  {
    for(int i = 1; i < n; ++i)
    {
      if(x[i].compareTo(x[i-1]) < 0)
      {
        Comparable temp = x[i];
        int index = binarySearch(x,0,i,x[i]);
        for(int j = i - 1; j >= index; --j)
        {
          x[j + 1] = x[j];
        }
        x[index] = temp;
      }
    }
	}
}
