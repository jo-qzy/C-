struct __true_type
{
	static bool get()
	{
		return true;
	}
};

struct __false_type
{
	static bool get()
	{
		return false;
	}
};

template <class T>
struct __my__type_traits
{
	typedef __false_type is_POD_type;
};

//对int进行偏特化萃取
template <>
struct __my__type_traits<int>
{
	typedef __true_type is_POD_type;
};

//对double进行偏特化萃取
template <>
struct __my__type_traits<double>
{
	typedef __true_type is_POD_type;
};

//先调类型萃取然后进行判断
template<class T>
T* __my_copy(T* dst, const T* src, size_t size)
{
	if (dst == src || dst == nullptr || src == nullptr)
		return dst;
	if (__my_type_traits<T>::is_POD_type::get() == true)
	{
		memcpy(dst, src, sizeof(T) * size);
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			*(dst + i) = *(src + i);
		}
	}
	return dst;
}

template<class T>
T* __my_move(T* dst, const T* src, size_t size)
{
	if (dst == src || dst == nullptr || src == nullptr)
		return dst;
	if (__my_type_traits<T>::is_POD_type::get() == true)
	{
		memmove(dst, src, sizeof(T) * size);
	}
	else
	{
		if (src < dst && src + size > dst)
		{
			for (int i = 0; i < size; i++)
			{
				*(dst + size - i - 1) = *(src + size - i - 1);
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				*(dst + i) = *(src + i);
			}
		}
	}
	return dst;
}