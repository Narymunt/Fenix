
template <class T> T clamp (T n, T min, T max)
{   
   if (n <= min)
	{
		return min;
	}
	else if (n >= max)
	{
		return max;
	}
	else
	{
		return n;
	}


}

    