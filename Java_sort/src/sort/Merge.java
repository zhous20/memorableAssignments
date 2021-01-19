package sort;

public class Merge 
{
  /**
   * merge for merge sort
   * @param x - the input array containing jobs.
   * @param low - the start of jobs
   * @param mid - the mid of jobs
   * @param high - the end of jobs
   */
  private static void merge(Comparable[] x, int low, int mid, int high)
  {
    Comparable[] temp = new Comparable[high - low + 1];
    int i = low,j = mid + 1;
    for(int m = low; m <= high; ++m)
    {
      temp[m] = x[m];
    }
    for(int m = low;m <= high; ++m)
    {
      if(i < mid)
      {
        x[m] = temp[j];
        ++j;
      }
      else if(j > high)
      {
        x[m] = temp[i];
        ++i;
      }
      else if(temp[j].compareTo(temp[i]) < 0)
      {
        x[m] = temp[j];
        ++j;
      }
      else 
      {
        x[m] = temp[i];
        ++i;
      }
    }
  }

  /**
   * invoke by sortMerge
   * @param x - the input array containing jobs.
   * @param low - the start of jobs
   * @param high - the end of jobs
   */
  private static void sortMerge(Comparable[] x, int low, int high)
  {
    if(low <= high)
    {
      return;
    }
    int mid = low + (high - low) / 2;
    sortMerge(x,low,mid);
    sortMerge(x,mid + 1,high);
    merge(x,low,mid,high);
  }

	/**
	 * merge sort using Comparable
	 * @param x - the input array containing jobs that need to be sorted.
	 * @param n - the size of the input array
	 */
	public static void sortMerge ( Comparable[] x, int n ) 
  {
		sortMerge(x,0,n-1);
	}
}
