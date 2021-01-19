package sort;

public class Job implements Comparable<Job>
{
  private String id;
  private int t;

  /**
   * constructor the job with id and time
   * @param id - job's id
   * @param t - job's time
   */
  public Job(String id,int t)
  {
    this.id = id;
    this.t = t;
  }

  /**
   * get the job's id
   * @return job's id
   */
  public String getId()
  {
    return id;
  }

  /**
   * get the job's time
   * @return job's time
   */
  public int getTime()
  {
    return t;
  }

  /**
   * set the job's time
   * @param t - job's time
   */
  public void setTime(int t)
  {
    this.t = t;
  }

  /**
   * get the job as string
   * @return the job as string
   */
  public String toString()
  {
    return id + t;
  }

  /**
   * compare with another job
   * @param j - another job
   * @return 1 if larger than another, -1 if less,0 if equal
   */
	@Override
	public int compareTo(Job j)
	{
		if(t < j.t)
    {
      return -1;
    }
    else if(t > j.t)
    {
      return 1;
    }
    else
    {
      return id.compareTo(j.id);
    }
	}
}
