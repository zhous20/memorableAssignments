package sort;

public class Heap 
{
  /**
   * change the value at i and j
   * @param x - the input array containing jobs.
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
   * sink
   * @param x - the input array containing jobs.
   * @param n - the length of jobs
   * @param i - the index of jobs
   */
  private static void sink(Comparable[] x, int n, int i)
  {
    while(i*2 < n)
    {
      int j = i*2;
      if(j < n && x[j].compareTo(x[j+1]) < 0)
      {
        ++j;
      }
      if(x[i].compareTo(x[j]) >= 0)
      {
        break;
      }
      exchange(x,i,j);
      i = j;
    }
  }

	/**
	 * heap sort using Comparable
	 * @param x - the input array containing jobs that need to be sorted.
	 * @param n - the size of the input array
	 */
	public static void sortHeap ( Comparable[] x, int n ) 
  {
    Comparable[] a = new Comparable[x.length + 1];
    for(int i = 1; i < a.length; ++i)
    {
      a[i] = x[i - 1];
    }
	  for(int m = n/2; m >=1; --m)
    {
      sink(a,n,m);
    }
    int temp = n;
    while(temp > 1)
    {
      exchange(a,1,temp);
      --temp;
      sink(a,temp,1);
    }
    for(int i = 1; i < a.length; ++i)
    {
      x[i - 1] = a[i];
    }
  }
}
